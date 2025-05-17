#include <stdio.h>
#include "checkvalue.h"

int check_out_of_range_uinteger(
    const char *varName,
    UInteger value,
    UInteger limit,
    int errorCode
) {
    if (value <= limit) return 0;
    (void)printf("\nError: %s out of range: %llu when limit is %llu",
        varName,
        value,
        limit
    );
    return errorCode;
}