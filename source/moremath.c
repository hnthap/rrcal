#include <math.h>
#include <stdio.h>
#include "checkvalue.h"
#include "moremath.h"

int factorize_one(
    UInteger *pA,
    UInteger divisor,
    int *pPrimeCount,
    UInteger result[][2],
    int maxPrimeCount
);

UInteger gcd(UInteger a, UInteger b)
{
    int d = 0;
    if (a == 0 || b == 0) return a + b;
    if (a == b) return a;
    while (a % 2 == 0 && b % 2 == 0) {
        a /= 2;
        b /= 2;
        d += 1;
    }
    while (a % 2 == 0) a /= 2;
    while (b % 2 == 0) b /= 2;
    while (a != b) {
        if (a > b) {
            a -= b;
            while (a % 2 == 0) a /= 2;
        }
        else if (a < b) {
            b -= a;
            while (b % 2 == 0) b /= 2;
        }
        else {
            break;
        }
    }
    while (d) {
        a *= 2;
        d -= 1;
    }
    return a;
}

UInteger lcm(UInteger a, UInteger b) {
    return a * b / gcd(a, b);
}

int factorize(
    UInteger a,
    int *pPrimeCount,
    UInteger result[][2],
    int maxPrimeCount
) {
    int rc;
    UInteger limit, c, d;
    if (a == 0) return 1;
    *pPrimeCount = 0;
    if (a == 1) return 0;
    rc = factorize_one(&a, 2, pPrimeCount, result, maxPrimeCount);
    if (rc) return rc;
    rc = factorize_one(&a, 3, pPrimeCount, result, maxPrimeCount);
    if (rc) return rc;
    limit = (UInteger)floor(sqrt(a));
    for (c = 5; c <= limit || a != 1; c += 6) {
        for (d = 0; d != 4; d += 2) {
            rc = factorize_one(&a, c + d, pPrimeCount, result, maxPrimeCount);
            if (rc) return rc;
        }
    }
    return 0;
}

int factorize_one(
    UInteger *pA,
    UInteger divisor,
    int *pPrimeCount,
    UInteger result[][2],
    int maxPrimeCount
) {
    int rc;
    if (*pA % divisor == 0) {
        rc = check_out_of_range_uinteger(
            "*pPrimeCount",
            (*pPrimeCount) + 1,
            maxPrimeCount,
            2
        );
        if (rc) return rc;
        result[*pPrimeCount][0] = divisor;
        result[*pPrimeCount][1] = 0;
        while (*pA % divisor == 0) {
            result[*pPrimeCount][1] += 1;
            *pA /= divisor;
        }
        *pPrimeCount += 1;
    }
    return 0;
}
