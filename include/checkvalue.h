#ifndef RRCAL_CHECKVALUE_H
#define RRCAL_CHECKVALUE_H

#include "types.h"

/**
 * @brief Check if a UInteger value is in range. Return 0 if the value is
 * valid, otherwise, return the indicated error code.
 * 
 * @param varName Variable name
 * @param value Checked value
 * @param limit Range limit, which the checked value is not expected to exceed
 * @param errorCode Indicated error code to return if the checked value is
 * invalid
 * @return int 
 */
int check_out_of_range_uinteger(
    const char *varName,
    UInteger value,
    UInteger limit,
    int errorCode
);

#endif  /* RRCAL_CHECKVALUE_H */