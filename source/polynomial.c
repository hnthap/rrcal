#include <stdio.h>
#include "polynomial.h"

void polynomial_copy(Polynomial origin, Polynomial *pTarget) {
    int i;
    pTarget->n = origin.n;
    for (i = 0; i <= origin.n; i += 1) {
        pTarget->a[i] = origin.a[i];
    }
}

int polynomial_init_int_coefficients(int n, UInteger a[], Polynomial *pResult) {
    int i;
    if (n < 0 || n > RRCAL_POLYNOMIAL_MAX_DEGREE) {
        return 2;
    }
    i = n;
    while (a[i] == 0 && i >= 1) {
        i -= 1;
    }
    pResult->n = i;
    while (i >= 0) {
        rational_init_from_int(&(pResult->a[i]), a[i]);
        i -= 1;
    }
    return 0;
}

void polynomial_calculate(Polynomial p, Rational x, Rational *pResult) {
    int i;
    rational_copy(p.a[p.n], pResult); /* p := a_n */
    for (i = p.n - 1; i >= 0; i -= 1) {
        rational_multiply(*pResult, x, pResult); /* p := p * x */
        rational_add(*pResult, p.a[i], pResult); /* p := p + a */
    }
}

size_t polynomial_to_string(Polynomial p, char *pBuffer, size_t size) {
    char s[RRCAL_RATIONAL_MAX_BUFFER_SIZE];
    size_t newSize = 0;
    int i;
    if (p.n > 1) {
        rational_to_string(p.a[p.n], s, RRCAL_RATIONAL_MAX_BUFFER_SIZE);
        newSize += snprintf(pBuffer + newSize, size - newSize, "%sx^%d ", s, p.n);
    }
    for (i = p.n - 1; i > 1; i -= 1) {
        if (p.a[i].p != 0) {
            rational_to_string_v2(p.a[i], s, RRCAL_RATIONAL_MAX_BUFFER_SIZE);
            newSize += snprintf(pBuffer + newSize, size - newSize, "%sx^%d ", s, i);
        }
    }
    if (p.n >= 1 && p.a[1].p != 0) {
        if (p.n == 1) {
            rational_to_string(p.a[1], s, RRCAL_RATIONAL_MAX_BUFFER_SIZE);
        }
        else {
            rational_to_string_v2(p.a[1], s, RRCAL_RATIONAL_MAX_BUFFER_SIZE);
        }
        newSize += snprintf(pBuffer + newSize, size - newSize, "%sx ", s);
    }
    if (p.a[0].p != 0 || (p.a[0].p == 0 && p.n == 0)) {
        if (p.n == 0) {
            rational_to_string(p.a[0], s, RRCAL_RATIONAL_MAX_BUFFER_SIZE);
        }
        else {
            rational_to_string_v2(p.a[0], s, RRCAL_RATIONAL_MAX_BUFFER_SIZE);
        }
        newSize += snprintf(pBuffer + newSize, size - newSize, "%s ", s);
    }
    return newSize;
}
