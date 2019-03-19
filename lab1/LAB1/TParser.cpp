#include "TParser.h"
static bool MyIsDigit(const char symbol) {
    return '0' <= symbol && symbol <= '9';
}
unsigned int ReadKey(char * key) {
    unsigned int number = 0;
    int digit = 10000000;
    for (int i = 0; i < KEY_LEN; i++) {
        if (key[i] == ' ') {
            continue;
        }
        if (MyIsDigit(key[i])) {
            number += (key[i] - '0') * digit;
        } else {
            number += (key[i]) * digit;
        }
        digit = digit / 10;
        if (i == 4 || i == 6) {
            digit = digit / 10;
        }
    }
    return number;
}
int MyStrlen(const char *string) {
    register const char *pStr;

    for (pStr = string; *pStr; ++pStr);
    return(pStr - string);
}
void PrintCarPlateNumber(unsigned int number) {
    char output[KEY_LEN - 2];
    int digit = 10000000;
    for (int i = 0; i < KEY_LEN - 2 ; i++) {
    if ((i >= 1) && (i <= 3 )){
        output[i] = (char) (number / digit) + '0';
        } else {
        output[i] = (char) (number / digit);
    }
        number = number % digit;
        digit = digit / 10;
        if (i == 3 || i == 4) {
            digit = digit / 10;
        }
    }
    for (int i = 0; i < KEY_LEN - 2; i++) {
        if (i == 1 || i == 4) {
            printf(" ");
        }
        printf("%c",output[i]);
    }
    printf("\t");
}
void PrintValue(const char * value) {
    puts(value);
}