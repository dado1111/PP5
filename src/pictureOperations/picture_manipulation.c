//
// Created by dado1111 on 28/10/2021.
//

#include "picture_manipulation.h"
#include "libraries.h"

struct Picture* load_file(char* filename, int size_x_dim, int size_y_dim, int size_z_dim){

    struct Picture* picture = allocate_Picture(size_x_dim, size_y_dim, size_z_dim);

    char filepath[100];
    strcpy(filepath, "../res/");
    strcat(filepath, filename);



    FILE* f = fopen(filepath, "rb");
    if( f == NULL )
    {
        fprintf(stderr,"Cannot open file %s\n",filename);
        return picture;
    }

    for(int z = 0 ; z < size_z_dim ; z++){
        for(int y = 0 ; y < size_y_dim ; y++){
            fread(picture->data[z][y], sizeof(char), size_x_dim, f);
        }
    }

    fclose(f);

    return picture;
}

void threshold_in_place(struct Picture* picture, short threshold) {

    for(int z = 0 ; z < picture->z ; z++){
        for(int y = 0 ; y < picture->y ; y++){
            for(int x = 0 ; x < picture->x ; x++){
                if(picture->data[z][y][x] > threshold){
                    picture->data[z][y][x] = 1;
                }else{
                    picture->data[z][y][x] = 0;
                }
            }
        }
    }
}

struct PictureLinearized *linearize_Picture(struct Picture *picture) {

    long size = picture->x * picture->y * picture->z;

    struct PictureLinearized* pictureLinearized = allocate_PictureLinearized(size);
    pictureLinearized->size = size;
    long index_size = 0;

    for(int z = 0 ; z < picture->z ; z++){
        for(int y = 0 ; y < picture->y ; y++){
            for(int x = 0 ; x < picture->x ; x++){
                pictureLinearized->data[index_size] = picture->data[z][y][x];
                index_size++;
            }
        }
    }

    return pictureLinearized;
}