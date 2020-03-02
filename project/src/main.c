#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "prime.h"

#define ERR_ARGS_COUNT (-1)
#define ERR_WRONG_FLG (-2)

#define TST_FOO_FIX     1
#define TST_FOO_IMPL    2
#define TST_MOD_IMPL    3


/* NOTE(stitaevskiy):
 * We use `atoi` function just for simplification and code reducing.
 * This function doesn't report conversation errors.
 * For safety program we recommend using `strtol` and its analogs.
 * (See `man atoi` and `man strtol` for more info).
 *
 * const char str_num[] = "1234";
 * char* end = NULL;
 * int val = (int) strtol(str_num, &end, 0);
 * if (end != '\0') {
 *     //ERROR
 * }
 *
 * */

int main(int argc, const char** argv) {
    if (argc < 3) {
        return ERR_ARGS_COUNT;
    }

    int test_case = atoi(argv[1]);
    const char* data;
    data = argv[2];

    switch (test_case) {
        case TST_FOO_FIX: {
            printf("%zu\n", custom_strlen(data));
            break;
        }
        case TST_FOO_IMPL: {
            if (argc != 4) {
                return ERR_ARGS_COUNT;
            }
            printf("%i\n", custom_pow(atoi(data), atoi(argv[3])));
            break;
        }
        case TST_MOD_IMPL: {
            printf("%i\n", prime_number(atoi(data)));
            break;
        }
        default: {
            return ERR_WRONG_FLG;
        }
    }

    return 0;
}
