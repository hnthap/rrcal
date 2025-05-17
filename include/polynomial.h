#ifndef RRCAL_POLYNOMIAL_H
#define RRCAL_POLYNOMIAL_H

#include "rational.h"

#define RRCAL_POLYNOMIAL_MAX_DEGREE (20)

/**
 * @brief Polynomial
 * 
 * a_n x^n + a_{n - 1} x^{n - 1} + ... + a_1 x + a_0
 * 
 */
typedef struct {
    int n; /* Degree */
    Rational a[RRCAL_POLYNOMIAL_MAX_DEGREE + 1]; /* Coefficients */
} Polynomial;

/**
 * @brief Copy a polynomial.
 * 
 * @param origin 
 * @param pTarget 
 */
void polynomial_copy(Polynomial origin, Polynomial *pTarget);

/**
 * @brief Initialize a polynomial with all coefficients as integers.
 * 
 * @param n Degree
 * @param a Coefficients
 * @param pResult Pointer to the result
 * 
 * @return Return one of these codes: 0 (success), 2 (invalid degree value).
 */
int polynomial_init_int_coefficients(int n, UInteger a[], Polynomial *pResult);

/**
 * @brief Calculate the value of the polynomial with an input x value.
 * 
 * P(x) = a_n x^n + a_{n - 1} x^{n - 1} + ... + a_1 x + a_0
 * 
 * P_0 = a_n
 * 
 * P_1 = P_0 x + a_{n - 1}
 * 
 * P_2 = P_1 x + a_{n - 2}
 * 
 * ...
 * 
 * P_{n - 2} = P_{n - 3} x + a_2
 * 
 * P_{n - 1} = P_{n - 2} x + a_1
 * 
 * P = P_n = P_{n - 1} x + a_0
 * 
 * @param p Polynomial
 * @param x x
 * @param pResult Pointer to the result
 */
void polynomial_calculate(Polynomial p, Rational x, Rational *pResult);

/**
 * @brief Present a polynomial as a string
 * 
 * @param p 
 * @param pBuffer 
 * @param size 
 * @return Size of output string if success, otherwise, 0
 */
size_t polynomial_to_string(Polynomial p, char *pBuffer, size_t size);

#endif  /* RRCAL_POLYNOMIAL_H */