#ifndef RRCAL_MOREMATH_H
#define RRCAL_MOREMATH_H

#include "types.h"

#define RRCAL_MAX_PRIME_COUNT (512)

/**
 * @brief Calculate GCD of two unsigned integers.
 * 
 * @param a 
 * @param b 
 * @return UInteger 
 */
UInteger gcd(UInteger a, UInteger b);

/**
 * @brief Calculate LCM of two unsigned integers.
 * 
 * @param a 
 * @param b 
 * @return UInteger 
 */
UInteger lcm(UInteger a, UInteger b);

/**
 * @brief Factorize an "unsigned" integer. This function treats the
 * value 0 as "unfactorable", thus would returns 1 as an error code.
 * Error code 2 would be returned when the limit defined by
 * maxPrimeCount is exceeded. If success, return 0.
 * 
 * @param a The number to be factorized
 * @param pPrimeCount Pointer to number of unique prime factors
 * @param result Array of arrays. For example, 120 = 2^3 * 3 * 5 would
 * be represented as `{{2, 3}, {3, 1}, {5, 1}}`.
 * @param maxPrimeCount Static size of the result array, i.e. the number
 * of unique prime factors.
 */
int factorize(
    UInteger a,
    int *pPrimeCount,
    UInteger result[][2],
    int maxPrimeCount
);

#endif  /* RRCAL_MOREMATH_H */