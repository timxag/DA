#include "MyRadixSort.h"
void MyRadixSort(TItem ** input, const unsigned int * size) {
    TItem* output = (TItem *) malloc(*size * sizeof(TItem)); 
    int digit[DIGIT_SIZE];
    for (int i = 0; i < DIGIT_SIZE; i++) {
        digit[i] = 0;
    }
    int idx = 0;
    int countMoveToLeft = 3;
    unsigned int buffer = 0;
        for (int j = KEY_LEN_IN_BYTES; j > 0; j--){
        for (int i = 0; i < *size; i++) {
            buffer = (*(*input+i)).key << (countMoveToLeft * BYTE);
            (*(*input+i)).curDigit = buffer >> (COUNT_MOVE_TO_RIGHT * BYTE);
            idx = (*(*input+i)).curDigit;
            digit[idx] = digit[idx] + 1;
        }
        for (int  i = 1; i < DIGIT_SIZE; i++) {
            digit[i] = digit[i] + digit[i - 1];
        }
        for (int i = *size - 1; i >= 0; i--) {
            idx = (*(*input+i)).curDigit;
            digit[idx] = digit[idx] - 1;
            output[digit[idx]] = (*(*input+i));
        }
        for (int i = 0; i < DIGIT_SIZE; i++) {
            digit[i] = 0;
        }

        TItem* b; 
        b = *input; 
        *input = output;
        output = b;
        countMoveToLeft--;
    }
    free(output);
}