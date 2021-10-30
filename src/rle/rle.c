//
// Created by dado1111 on 28/10/2021.
//

#include "rle.h"

unsigned int total_bit_count_for_rle(struct PictureLinearized* threshheld_picture_linearized, int rle_block_bit_size) {


    if(rle_block_bit_size < MIN_RLE_BIT_SIZE || rle_block_bit_size > MAX_RLE_BIT_SIZE ||
            threshheld_picture_linearized->size <= 0){
        return -1;
    }

    // how many values can a block count
    // if block is: [0|00] - 1 bit for value, 2 bits for count - then it can contain max 3 counts (2bits)
    int const max_value_count_per_block = ((int) pow(2, rle_block_bit_size)) - 1;

    // how many block counts of rle are in total
    int block_count = 1;

    // what value is being counted currently
    // -- either 0 or 1
    char current_value = threshheld_picture_linearized->data[0];

    // what is current occurrences count
    int current_value_count = 0;


    // main
    for(unsigned long i = 0 ; i < threshheld_picture_linearized->size ; i++){

        // if data value is same as previous, just add to count
        if(threshheld_picture_linearized->data[i] == current_value){
            current_value_count++;

            // if max count per block overflew  - add to new block
            if(current_value_count > max_value_count_per_block){
                current_value_count = 1;
                block_count++;
            }

        // if value is different from previous - add to new block
        }else{
            current_value = threshheld_picture_linearized->data[i];
            current_value_count = 1;
            block_count++;
        }
    }

    printf("rle.c: BitSize: %d \t= %i Bits\n", rle_block_bit_size, (block_count * (1+rle_block_bit_size)));

    return block_count * (1 + rle_block_bit_size);
}
