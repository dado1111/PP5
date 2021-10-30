//
// Created by dado1111 on 28/10/2021.
//

#ifndef PP5_RLE_H
#define PP5_RLE_H

#include "libraries.h"

#define MAX_RLE_BIT_SIZE 17
#define MIN_RLE_BIT_SIZE 2

unsigned int total_bit_count_for_rle(struct PictureLinearized* threshheld_picture_linearized, int rle_block_bit_size);

#endif //PP5_RLE_H
