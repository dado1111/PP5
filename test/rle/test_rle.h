//
// Created by dado1111 on 28/10/2021.
//

#ifndef PP5_TEST_RLE_H
#define PP5_TEST_RLE_H

#include "rle/rle.h"

void assert_equals(char* testname, unsigned expected_value, unsigned int resulted_value);

void test_total_bit_count_for_rle_default();

void test_total_bit_count_for_rle__less_bit_count_per_block__should_overflow();



#endif //PP5_TEST_RLE_H
