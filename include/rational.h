/**
 * @brief Header file defining the rational number type and
 * basic functionalities.
 */

#ifndef RRCAL_RATIONAL_H
#define RRCAL_RATIONAL_H

#include "types.h"

#define RRCAL_RATIONAL_MAX_BUFFER_SIZE (36)

/**
 * @brief Rational number type
 */
typedef struct {
    UInteger p;  /* Numerator */
    UInteger q;  /* Demoninator */
    int negative; /* Whether the value is negative */
} Rational;

/**
 * @brief Copy a rational value.
 * 
 * @param value 
 * @param pTarget 
 */
void rational_copy(Rational value, Rational *pTarget);

/**
 * @brief Initialize a rational number from the specified numerator, denominator
 * and sign.
 * 
 * @param pValue 
 * @param p 
 * @param q 
 * @param negative 
 * @return int 
 */
int rational_init(Rational *pValue, UInteger p, UInteger q, int negative);

/**
 * @brief Initialize rational number from an integer.
 * 
 * @param pValue 
 * @param value 
 * @return 0 if success, otherwise, 1.
 */
int rational_init_from_int(Rational *pValue, int64_t value);

/**
 * @brief Convert rational number to string.
 * 
 * @param value 
 * @param pBuffer 
 * @param size
 * @return Size of output string if success, otherwise, 0.
 */
size_t rational_to_string(Rational value, char *pBuffer, size_t size);

/**
 * @brief Convert rational number to string,
 * with leading "+" sign for positive value.
 * 
 * @param value 
 * @param pBuffer 
 * @param size
 * @return Size of output string if success, otherwise, 0.
 */
size_t rational_to_string_v2(Rational value, char *pBuffer, size_t size);

/**
 * @brief Simplify a rational number.
 * 
 * @param p1 
 * @param p2 
 */
void rational_simplify(Rational *pValue);

/**
 * @brief Add two rational numbers.
 * 
 * @param p1 
 * @param p2 
 * @return Rational 
 */
void rational_add(Rational r1, Rational r2, Rational *pResult);

/**
 * @brief Multiply two rational numbers.
 * 
 * @param p1 
 * @param p2 
 * @return Rational 
 */
void rational_multiply(Rational r1, Rational r2, Rational *pResult);

#endif  /* RRCAL_RATIONAL_H */
