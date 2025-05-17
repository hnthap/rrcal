#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "argparse.h"

/**
 * @brief Parse rational number, i.e. convert string representation to Rational.
 * Return 0 if success, otherwise, return 1.
 * 
 * @param pRational Pointer to the Rational variable
 * @param s Parsed string
 * @return int 
 */
int parse_rational(Rational *pRational, char *s);

int parse_arguments(int argc, char *argv[], Arguments *pArgs) {
    int i, rc;
    pArgs->polynomial.n = -1;
    for (i = 1; i < argc; i += 1) {
        pArgs->polynomial.n += 1;
        if (pArgs->polynomial.n > RRCAL_POLYNOMIAL_MAX_DEGREE) {
            (void)printf("\nError: Polynomial degree (%d) out of range", pArgs->polynomial.n);
            return 1;
        }
        rc = parse_rational(&pArgs->polynomial.a[pArgs->polynomial.n], argv[i]);
        if (rc) return rc;
    }
    return 0;
}

int parse_rational(Rational *pRational, char *s) {
    const char *p = s;
    char *endp;
    pRational->negative = 0;
    if (*p == '-') {
        pRational->negative = 1;
        p += 1;
    }
    else if (*p == '+') {
        p += 1;
    }
    errno = 0;
    pRational->p = strtoull(p, &endp, 10);
    if (p == endp) {
        (void)printf("\nError: No numerator found in '%s'", s);
        return 1;
    }
    if (errno == ERANGE && pRational->p == ULLONG_MAX) {
        (void)printf("\nError: Numerator '%s' out of range", p);
        return 1;
    }
    if (errno != 0) {
        perror("strtoull (numerator)");
        return 1;
    }
    errno = 0;
    if (*endp == '\0') {
        pRational->q = 1;
        return 0;
    }
    if (*endp != '/') {
        (void)printf("\nError: Missing '/' separator in '%s'", s);
        return 1;
    }
    p = endp + 1;
    pRational->q = strtoull(p, &endp, 10);
    if (p == endp) {
        (void)printf("\nError: No denominator found in '%s'", s);
        return 1;
    }
    if (errno == ERANGE && pRational->q == ULLONG_MAX) {
        (void)printf("\nError: Denominator '%s' out of range", p);
        return 1;
    }
    if (errno != 0) {
        perror("strtoull (denominator)");
        return 1;
    }
    if (*endp != '\0') {
        (void)printf("\nError: Extra characters after denominator in '%s'", s);
        return 1;
    }
    if (pRational->q == 0) {
        (void)printf("\nError: Denominator cannot be zero in '%s'", s);;
        return 1;
    }
    return 0;
}
