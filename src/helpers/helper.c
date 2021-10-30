//
// Created by dado1111 on 29/10/2021.
//
#include "helper.h"

struct RangeArray* getRanges(int thread_count, int min, int max){

    struct RangeArray* rangeArray = allocate_RangeArray(thread_count);

    int size = max - min;

    int single_range = size / thread_count;
    int leftover_range = size % thread_count;

    int range = min;

    for(int i = 0 ; i < thread_count ; i++){
        rangeArray->ranges[i]->from = range;
        range += single_range;
        range += leftover_range-- > 0 ? 1 : 0;
        rangeArray->ranges[i]->to = range;
    }

    return rangeArray;
}
