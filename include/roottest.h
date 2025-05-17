#ifndef RRCAL_INTROOT_H
#define RRCAL_INTROOT_H

#include "polynomial.h"

/**
 * @brief Test for rational roots of a rational polynomial
 * using the rational root theorem.
 * 
 * @param p 
 * @param pRootCount 
 * @param roots 
 * @param maxRootCount
 */
int test_rational_roots(
    Polynomial p,
    int *pRootCount,
    Rational roots[],
    int maxRootCount
);

#endif  /* RRCAL_INTROOT_H */