//
// Created by dado1111 on 28/10/2021.
//

#ifndef PP5_PICTURE_MANIPULATION_H
#define PP5_PICTURE_MANIPULATION_H

#include "libraries.h"

struct Picture* load_file(char* filename, int size_x_dim, int size_y_dim, int size_z_dim);

void threshold_in_place(struct Picture* picture, short threshold);

struct PictureLinearized* linearize_Picture(struct Picture* picture);

#endif //PP5_PICTURE_MANIPULATION_H
