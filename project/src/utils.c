#include <string.h>
#include "utils.h"

size_t custom_strlen(const char* str) {
    return  strlen(str);
}

int custom_pow(int base, int power) {
    int res = 1;
    for (; power > 0; power--) {
        res = res * base;
    }
    return res;
}

