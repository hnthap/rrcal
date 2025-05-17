#include "checkvalue.h"
#include "moremath.h"
#include "roottest.h"

/**
 * @brief Clean up root zero from a polynomial, i.e. transform p(x) into q(x),
 * where 
 * 
 * * p(x) is a nonzero polynomial;
 * 
 * * p(x) has n roots of zero (n >= 0);
 * 
 * * and p(x) = x^n q(x).
 * 
 * @return Number of roots of zero of p(x).
 */
int clean_root_zero(Polynomial *);
/**
 * @brief Add new root to a list of roots (array of Rational). Return 0 if
 * success, otherwise, return 2.
 * 
 * @return int 
 */
int add_root(Rational, int *, Rational[], int);
/**
 * @brief Prepare the polynomial and mathematical variables to work with using
 * the Rational root theorem.
 * 
 */
void prepare_rational_root_theorem(Polynomial *, UInteger *, UInteger *);
/**
 * @brief Test all possible rational roots with the specified polynomial.
 * Return 0 if success.
 * 
 * @return int 
 */
int test_all_rational_roots(Polynomial *, UInteger, UInteger, int *, Rational[], int);
/**
 * @brief Increment power values.
 * @return 0 if success, otherwise, 1 if it cannot be incremented anymore.
 */
int increment_power(int, int[], int[], int[]);
/**
 * @brief Calculate ranges of powers of A and B's prime factors, to be used
 * with the application of the Rational root theorem. Return 0 if success.
 * 
 * @return int 
 */
int make_factor_range(UInteger, UInteger, int *, UInteger[], int[], int[], int);

int test_rational_roots(Polynomial p, int *pRootCount, Rational roots[], int maxRootCount) {
    Polynomial polynomial;
    Rational root;
    UInteger a, b;
    *pRootCount = 0;
    if (p.n == 0) return 0;
    polynomial_copy(p, &polynomial);
    if (clean_root_zero(&polynomial)) {
        root.p = 0;
        root.q = 1;
        root.negative = 0;
        add_root(root, pRootCount, roots, maxRootCount);
    }
    if (polynomial.n == 0) return 0;
    prepare_rational_root_theorem(&polynomial, &a, &b);
    return test_all_rational_roots(&polynomial, a, b, pRootCount, roots, maxRootCount);
}

int clean_root_zero(Polynomial *pP) {
    int zeroCount = 0, i;
    for (i = 0; i <= pP->n; i += 1) {
        if (pP->a[i].p != 0) break;
        zeroCount += 1;
    }
    if (zeroCount != 0) {
        pP->n -= zeroCount;
        for (i = 0; i <= pP->n; i += 1) {
            pP->a[i] = pP->a[i + zeroCount];
        }
    }
    return zeroCount;
}

int add_root(
    Rational root,
    int *pRootCount,
    Rational roots[],
    int maxRootCount
) {
    int rc = check_out_of_range_uinteger("root count", *pRootCount + 1, maxRootCount, 2);
    if (rc) return rc;
    roots[*pRootCount] = root;
    *pRootCount += 1;
    return 0;
}

void prepare_rational_root_theorem(
    Polynomial *pP,
    UInteger *pA,
    UInteger *pB
) {
    int i;
    UInteger multiple = pP->a[0].q;
    for (i = 1; i <= pP->n; i += 1) {
        multiple = lcm(multiple, pP->a[i].q);
    }
    *pB = multiple / pP->a[pP->n].q * pP->a[pP->n].p;
    *pA = multiple / pP->a[0].q * pP->a[0].p;
}

int increment_power(int primeCount, int minPower[], int maxPower[], int power[]) {
    int i;
    for (i = 0; i < primeCount; i += 1) {
        if (power[i] < maxPower[i]) {
            power[i] += 1;
            return 0;
        }
        power[i] = minPower[i];
    }
    return 1;
}

int make_factor_range(
    UInteger a,
    UInteger b,
    int *pPrimeCount,
    UInteger primeFactors[],
    int minPower[],
    int maxPower[],
    int maxPrimeCount
) {
    int rc, i, j, aPrimeCount, bPrimeCount;
    UInteger aFactors[RRCAL_MAX_PRIME_COUNT][2];
    UInteger bFactors[RRCAL_MAX_PRIME_COUNT][2];
    rc = factorize(a, &aPrimeCount, aFactors, RRCAL_MAX_PRIME_COUNT);
    if (rc) return rc;
    rc = factorize(b, &bPrimeCount, bFactors, RRCAL_MAX_PRIME_COUNT);
    if (rc) return rc;
    i = j = 0;
    *pPrimeCount = 0;
    while (i < aPrimeCount || j < bPrimeCount) {
        rc = check_out_of_range_uinteger(
            "factor range's prime count",
            *pPrimeCount + 1,
            maxPrimeCount,
            2
        );
        if (rc) return rc;
        if (i < aPrimeCount && j < bPrimeCount && aFactors[i][0] == bFactors[j][0]) {
            primeFactors[*pPrimeCount] = aFactors[i][0];
            minPower[*pPrimeCount] = -bFactors[j][1];
            maxPower[*pPrimeCount] = aFactors[i][1];
            i = j = i + 1;
        }
        else if (i < aPrimeCount) {
            primeFactors[*pPrimeCount] = aFactors[i][0];
            minPower[*pPrimeCount] = 0;
            maxPower[*pPrimeCount] = aFactors[i][1];
            i += 1;
        }
        else {
            primeFactors[*pPrimeCount] = bFactors[j][0];
            minPower[*pPrimeCount] = -bFactors[j][1];
            maxPower[*pPrimeCount] = 0;
            j += 1;
        }
        *pPrimeCount += 1;
    }
    return 0;
}

int test_all_rational_roots(
    Polynomial *pP,
    UInteger a,
    UInteger b,
    int *pRootCount,
    Rational roots[],
    int maxRootCount
) {
    int rc, i, j, primeCount;
    Rational x, result;
    UInteger primeFactors[RRCAL_MAX_PRIME_COUNT];
    int minPower[RRCAL_MAX_PRIME_COUNT];
    int maxPower[RRCAL_MAX_PRIME_COUNT];
    int power[RRCAL_MAX_PRIME_COUNT];
    rc = make_factor_range(
        a, 
        b, 
        &primeCount, 
        primeFactors, 
        minPower, 
        maxPower, 
        RRCAL_MAX_PRIME_COUNT
    );
    if (rc) return rc;
    for (i = 0; i < primeCount; i += 1) {
        power[i] = minPower[i];
    }
    while (1) {
        x.p = 1;
        x.q = 1;
        for (i = 0; i < primeCount; i += 1) {
            if (power[i] < 0) {
                for (j = 0; j < -power[i]; j += 1) x.q *= primeFactors[i];
            }
            else if (power[i] > 0) {
                for (j = 0; j < power[i]; j += 1) x.p *= primeFactors[i];
            }
        }
        for (i = 0; i != 2; i += 1) {
            x.negative = i;
            polynomial_calculate(*pP, x, &result);
            if (result.p == 0) {
                rc = add_root(x, pRootCount, roots, maxRootCount);
                if (rc) return rc;
            }
        }
        if (increment_power(primeCount, minPower, maxPower, power)) break;
    }
    return 0;
}
