#include "TStruct.h"
#include "TNumVec.h"
#include "TParser.h"
#include "MyRadixSort.h"
#include <stdio.h>

void PrintKeys(TNumVec * vec);
int main() {
    TNumVec myVec;
    InitTNumVec(&myVec);
    unsigned int number = 0;
    char key[KEY_LEN];
    char string[VALUE_LEN + SPACE_FOR_NULL];
    while (scanf("%8c\t%s", key, string) == 2) {
        number = ReadKey(key);
        int length = MyStrlen(string);
        if (length != VALUE_LEN) { 
            for (int i = length; i < VALUE_LEN; i++){
                string[i] = '\0';
            }
        }
        AddItem(&myVec, number, string);
        string[0] = '\0';
        getchar();
    }
    MyRadixSort(&(myVec.items), &myVec.size);
    PrintKeys(&myVec);
    DeleteTNumVec(&myVec);
    return 0;
}

void PrintKeys(TNumVec * vec) {
    for (unsigned int i = 0; i < vec->size; i++) {
        PrintCarPlateNumber(GetItem(vec,i).key);
        PrintValue((GetItem(vec, i).value));
    } 
}