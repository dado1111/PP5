//
// Created by dado1111 on 28/10/2021.
//

#ifndef PP5_STRUCTURES_H
#define PP5_STRUCTURES_H

#include "libraries.h"

struct Picture{
    int x;
    int y;
    int z;
    char ***data;
};

struct PictureLinearized{
    long size;
    char *data;
};

// used in main for multi thread
struct Range{
    int from;
    int to;
};

struct RangeArray{
    struct Range **ranges;
    int size;
};

// used in main for multithread proxy function
struct ProxyArgument{
    struct Range* range;
    struct PictureLinearized* pictureLinearized;
};




struct Picture* allocate_Picture(int size_x_dim, int size_y_dim, int size_z_dim);
void free_Picture(struct Picture* picture);

struct PictureLinearized* allocate_PictureLinearized(long size);
void free_PictureLinearized(struct PictureLinearized* pictureLinearized);

struct RangeArray* allocate_RangeArray(int size);
void free_RangeArray(struct RangeArray* rangeArray);

#endif //PP5_STRUCTURES_H
