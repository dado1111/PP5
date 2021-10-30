//
// Created by dado1111 on 29/10/2021.
//

#include "test_picture_manipulation.h"

int main(){
    test_linearize_picture();
}
void test_linearize_picture() {

    struct PictureLinearized* pictureLinearized;
    struct Picture* picture = allocate_Picture(3,3,3);

    char field[3][3][3] = {
            {{0,0,0},{0,0,1},{0,1,0}},
            {{0,1,1},{1,0,0},{1,0,1}},
            {{1,1,0},{1,1,1},{0,0,0}}
    };

    // copy
    for(int z = 0; z < picture->z ; z++){
        for(int y = 0 ; y < picture->y ; y++){
            for(int x = 0 ; x < picture->x ; x++){
                picture->data[z][y][x] = field[z][y][x];
            }
        }
    }

    pictureLinearized = linearize_Picture(picture);

    // check
    if(pictureLinearized->size != 27){
        printf("linearized size != expected size: %ld != %ld", pictureLinearized->size, 27l);
        return;
    }

    char resulted_field[27] = {
            0,0,0, 0,0,1, 0,1,0, 0,1,1, 1,0,0, 1,0,1, 1,1,0, 1,1,1, 0,0,0
    };

    for(int i = 0 ; i < 27 ; i++){
        if(pictureLinearized->data[i] != resulted_field[i]){
            printf("data at index %d wrong, expected != resulted: %d != %d", i, resulted_field[i], pictureLinearized->data[i]);
            return;
        }
    }

    printf("test_linearize_picture -OK\n");

    free_Picture(picture);
    free_PictureLinearized(pictureLinearized);
}
