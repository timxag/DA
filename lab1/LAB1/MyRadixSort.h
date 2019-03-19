#ifndef MYRADIXSORT_H_
#define MYRADIXSORT_H_

#include "TStruct.h"
#include <stdlib.h>

const int BIT = 1;
const int BYTE = 8 * BIT;
const int DIGIT_SIZE = 256;
const int KEY_LEN_IN_BYTES = 4;
// постоянно будем сдвигать вправо на 3 байта,чтобы попасть в curDigit
const int COUNT_MOVE_TO_RIGHT = 3;

void MyRadixSort(TItem ** input, const unsigned int * size);

#endif // MYRADIXSORT_H_