#include "TNumVec.h"

static void ReallocTNumVec(TNumVec * vec);
static void MyStrcpy(char * output, char * input);

void InitTNumVec(TNumVec * vec) {
    unsigned int n = 1;
    vec->items = (TItem*) malloc(n * sizeof(TItem));
    vec->capacity = 1;
    vec->size = 0;
}
static void ReallocTNumVec(TNumVec * vec) {
    vec->capacity = ((vec->size + 1) * 2);
    vec->items = (TItem *) realloc(vec->items, vec->capacity * sizeof(TItem));
}
static void MyStrcpy(char * output, char * input) {
    while (*input) {
        *output++ = *input++;
    }
    *output = '\0';
}
void AddItem(TNumVec * vec, unsigned int number, char * string) { 
    if (vec->size == vec->capacity) {
        ReallocTNumVec(vec);
    }
    vec->items[vec->size].key = number;
    MyStrcpy(vec->items[vec->size].value, string);
    vec->size += 1;
}
TItem GetItem(TNumVec * vec, const int i) {    
    return vec->items[i];
}
void DeleteTNumVec(TNumVec * vec) {
    vec->capacity = 0;
    vec->size = 0;
    free(vec->items);
}