#include <stdio.h>

#include "libraries.h"
#include "pictureOperations/picture_manipulation.h"
#include "structures/structures.h"
#include "rle/rle.h"
#include "helpers/helper.h"

#define THREADS 2
#define THRESHOLD 25

#define ALLOW_SINGLE_THREAD true
#define ALLOW_MULTI_THREAD true

// METHODS
void print_time(long st_time, long mt_time);    // prints times
long single_thread(); // returns time in milliseconds
long multi_thread(); // returns time in milliseconds
void *multi_thread_proxy_function(void *arg);// proxy for pthread


// VARIABLES
struct Picture* picture;    // data from c8.raw file

int main() {

    printf("Fetching scan bytes\n");

    // load
    picture = load_file("c8.raw", 1024, 1024, 314);

    // threshold
    // -- not time measured, because linearization and thresholding can be done in one cycle theoretically
    //      but are now done in two different cycles over whole data
    printf("Thresholding scan bytes\n");
    threshold_in_place(picture, THRESHOLD);

    long single_thread_millis, multi_thread_millis;

    if(ALLOW_SINGLE_THREAD){
        printf("Starting single thread\n");
        single_thread_millis = single_thread();
    }
    if(ALLOW_MULTI_THREAD){
        printf("Starting multi thread\n");
        multi_thread_millis = multi_thread();
    }

    print_time(single_thread_millis, multi_thread_millis);

    free_Picture(picture);

    return 0;
}

long single_thread(){

    struct PictureLinearized* pictureLinearized; // linearized version of picture
    struct timespec start_time, end_time;   // timing variables

    // main
    clock_gettime(CLOCK_REALTIME , &start_time);    // start timing
    pictureLinearized = linearize_Picture(picture);

    clock_gettime(CLOCK_REALTIME , &end_time);  // end timing

    // calculate duration
    long duration;
    duration = (end_time.tv_sec - start_time.tv_sec) * 1000;
    duration += (end_time.tv_nsec - start_time.tv_nsec) / 1000000;

    return duration;
}

long multi_thread(){

    struct RangeArray* rangeArray;  // array of ranges of RLE block bitsize - to distribute calculations across threads
    struct PictureLinearized* pictureLinearized;   // linearized version of picture
    struct timespec start_time, end_time;   // for timing
    struct ProxyArgument* argument;     // argument for

    // pthread
    pthread_t tid[THREADS];

    clock_gettime(CLOCK_REALTIME , &start_time);

    pictureLinearized = linearize_Picture(picture);
    rangeArray = getRanges(THREADS, MIN_RLE_BIT_SIZE, MAX_RLE_BIT_SIZE);

    // start threads
    for(int i = 0; i < THREADS; i++){

        argument->pictureLinearized = pictureLinearized;
        argument->range = rangeArray->ranges[i];
        pthread_create(&tid[i], NULL, multi_thread_proxy_function, argument);
    }

    // join threads
    for(int i = 0; i < THREADS; i++){
        pthread_join(tid[i], NULL);
    }

    // -- END TIMING
    clock_gettime(CLOCK_REALTIME , &end_time);

    long duration;
    duration = (end_time.tv_sec - start_time.tv_sec) * 1000;
    duration+= (end_time.tv_nsec - start_time.tv_nsec) / 1000000;

    return duration;
}

void *multi_thread_proxy_function(void *arg){
    struct ProxyArgument* argument = (struct ProxyArgument*) arg;

    int start = argument->range->from;
    int end  = argument->range->to;
    struct PictureLinearized* pictureLinearized = argument->pictureLinearized;

    for(int i = start; i < end; i++){
        total_bit_count_for_rle(pictureLinearized, i);
    }
}

void print_time(long st_time, long mt_time){
    printf("TIMING RESULTS:\n");
    if(ALLOW_SINGLE_THREAD){
        printf("Single thread time: %ld millis\n", st_time);
    }

    if(ALLOW_MULTI_THREAD){
        printf("Multi thread time (%d threads): %ld millis\n", THREADS, mt_time);
    }

    if(ALLOW_MULTI_THREAD && ALLOW_SINGLE_THREAD){
        printf("Multithreading with %d threads is %.3f times faster than singlethread\n", THREADS, ((double)st_time/(double)mt_time));
    }
}