#ifndef TSTRUCT_H_
#define TSTRUCT_H_

const int KEY_LEN = 8;
const int VALUE_LEN = 64;
const int SPACE_FOR_NULL = 1;

typedef struct TItem {
    char value[VALUE_LEN + SPACE_FOR_NULL];
    unsigned int key = 0;
    unsigned char curDigit = 0;
} TItem;

typedef struct TNumVec {
    unsigned int size = 0;
    unsigned int capacity = 0;
    TItem* items;
} TNumVec;

#endif // TSTRUCT_H_