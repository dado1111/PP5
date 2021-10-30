//
// Created by dado1111 on 28/10/2021.
//

#include "structures.h"



struct Picture* allocate_Picture(int size_x_dim, int size_y_dim, int size_z_dim){

    struct Picture* picture = malloc(sizeof(struct Picture));

    picture->x = size_x_dim;
    picture->y = size_y_dim;
    picture->z = size_z_dim;

    picture->data = calloc(size_z_dim, sizeof(char**));

    for(int z = 0 ; z < size_z_dim ; z++){
        picture->data[z] = calloc(size_y_dim, sizeof(char*));
        for(int y = 0; y < size_y_dim; y++){
            picture->data[z][y] = calloc(size_x_dim, sizeof(char));
        }
    }
    return picture;
}

void free_Picture(struct Picture* picture){
    int size_z = picture->z;
    int size_y = picture->y;

    for(int z = 0; z < size_z; z++){
        for(int y = 0; y < size_y; y++){
            free(picture->data[z][y]);
        }
        free(picture->data[z]);
    }
    free(picture->data);
    free(picture);
}

struct PictureLinearized* allocate_PictureLinearized(long size){
    struct PictureLinearized* pictureLinearized;

    pictureLinearized           = calloc(1, sizeof(struct PictureLinearized));
    pictureLinearized->data     = calloc(size, sizeof(char));

    return  pictureLinearized;
}

void free_PictureLinearized(struct PictureLinearized* pictureLinearized){
    free(pictureLinearized->data);
    free(pictureLinearized);
}

struct RangeArray* allocate_RangeArray(int size){
   struct RangeArray* rangeArray;

   rangeArray = calloc(1, sizeof(struct RangeArray));
   rangeArray->ranges = calloc(size, sizeof(struct Range*));
   rangeArray->size = size;

   for(int i = 0 ; i < size ; i++){
       rangeArray->ranges[i] = calloc(1, sizeof(struct Range));
   }

   return rangeArray;
}


void free_RangeArray(struct RangeArray* rangeArray){

    for(int i = 0 ; i < rangeArray->size ; i++){
        free(rangeArray->ranges[i]);
    }
    free(rangeArray->ranges);
    free(rangeArray);
}