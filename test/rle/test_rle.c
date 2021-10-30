//
// Created by dado1111 on 28/10/2021.
//

#include "test_rle.h"

void copy(struct PictureLinearized* pictureLinearized){

}

int main(){
    test_total_bit_count_for_rle_default();
    test_total_bit_count_for_rle__less_bit_count_per_block__should_overflow();
}

void test_total_bit_count_for_rle_default() {

    int bit_count_per_rle_block;
    unsigned int expected_value;
    unsigned int resulted_value;
    struct PictureLinearized pictureLinearized;
    pictureLinearized.size = 10;

    // test_1
    char field_1[10] = {
            0,1,1,1,0,0,0,0,0,0
    };

    pictureLinearized.data = field_1;
    bit_count_per_rle_block = 3;


    expected_value = 3 * (bit_count_per_rle_block+1);
    resulted_value = total_bit_count_for_rle(&pictureLinearized, bit_count_per_rle_block);

    assert_equals("test_total_bit_count_for_rle_default: TEST1", expected_value, resulted_value);

    // test_2

    char field_2[10] = {
            0,1,0,1,0,1,0,1,0,1
    };

    pictureLinearized.data = field_2;
    bit_count_per_rle_block = 17;

    expected_value = 10 * (bit_count_per_rle_block+1);
    resulted_value = total_bit_count_for_rle(&pictureLinearized, bit_count_per_rle_block);

    assert_equals("test_total_bit_count_for_rle_default: TEST2", expected_value, resulted_value);
}

void test_total_bit_count_for_rle__less_bit_count_per_block__should_overflow() {

    int bit_count_per_rle_block;
    unsigned int expected_value;
    unsigned int resulted_value;
    struct PictureLinearized pictureLinearized;
    pictureLinearized.size = 10;

    // test_1
    char field_1[10] = {
            0,0,0,0,0,0,0,0,0,0
    };

    bit_count_per_rle_block = 2;
    pictureLinearized.data = field_1;

    expected_value = 4 * (bit_count_per_rle_block+1);
    resulted_value = total_bit_count_for_rle(&pictureLinearized, bit_count_per_rle_block);

    assert_equals("test_total_bit_count_for_rle__less_bit_count_per_block__should_overflow: TEST1",
                  expected_value, resulted_value);

    // test_2
    char field_2[10] = {
            0,0,0,0,0,0,0,0,0,0
    };

    bit_count_per_rle_block = 3;
    pictureLinearized.data = field_2;

    expected_value = 2 * (bit_count_per_rle_block+1);
    resulted_value = total_bit_count_for_rle(&pictureLinearized, bit_count_per_rle_block);

    assert_equals("test_total_bit_count_for_rle__less_bit_count_per_block__should_overflow: TEST2",
                  expected_value, resulted_value);
}

void assert_equals(char* testname, unsigned int expected_value, unsigned int resulted_value) {
    if(expected_value != resulted_value){
        printf("%s:\n %u != %u\n\n", testname, expected_value, resulted_value);
        return;
    }else{
        printf("%s\n -OK\n\n", testname);
    }
}
