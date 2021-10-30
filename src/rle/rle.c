//
// Created by dado1111 on 28/10/2021.
//

#include "rle.h"

unsigned int
total_bit_count_for_rle(struct PictureLinearized* threshheld_picture_linearized, int rle_block_bit_size) {


    if(
            rle_block_bit_size < MIN_RLE_BIT_SIZE ||
            rle_block_bit_size > MAX_RLE_BIT_SIZE ||
            threshheld_picture_linearized->size <= 0)
    {
        return -1;
    }

    // how many block counts of rle are in total
    int block_count = 1;

    // how many occurrences can one block contain
    int max_occurrences_per_block = ((int) pow(2, rle_block_bit_size)) - 1;

    // what value is being counter currently
    // -- either 0 or 1
    char currently_counting_occurrence = threshheld_picture_linearized->data[0];

    // what is current occurrences count
    int occurrences_count_per_block = 0;


    // MAIN
    for(unsigned long i = 0 ; i < threshheld_picture_linearized->size ; i++){

        // if data value is same as previous, just add to occurrences count
        if(threshheld_picture_linearized->data[i] == currently_counting_occurrence){
            occurrences_count_per_block++;

            // if occurrences count is max - add to new block
            if(occurrences_count_per_block > max_occurrences_per_block){
                occurrences_count_per_block = 1;
                block_count++;
            }

            // if data value is different as previous, add to new block
        }else {
            currently_counting_occurrence = threshheld_picture_linearized->data[i];
            occurrences_count_per_block = 1;
            block_count++;
        }
    }

    return block_count * (1 + rle_block_bit_size);
}
