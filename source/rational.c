#include <stdio.h>
#include <string.h>
#include "moremath.h"
#include "rational.h"

void rational_copy(Rational value, Rational *pTarget) {
    pTarget->p = value.p;
    pTarget->q = value.q;
    pTarget->negative = value.negative;
}

int rational_init(Rational *pValue, UInteger p, UInteger q, int negative) {
    if (q == 0) return 1;
    (*pValue).p = p;
    (*pValue).q = q;
    (*pValue).negative = negative;
    return 0;
}

int rational_init_from_int(Rational *pValue, int64_t value) {
    if (value < 0) {
        pValue->p = -value;
        pValue->negative = 1;
    }
    else {
        pValue->p = value;
        pValue->negative = 0;
    }
    pValue->q = 1;
    return 0;
}

size_t rational_to_string(Rational value, char *pBuffer, size_t size) {
    if (value.q == 1) {
        return snprintf(
            pBuffer, 
            size, 
            "%s%llu", 
            value.negative ? "- " : "", 
            value.p
        );
    }
    return snprintf(
        pBuffer, 
        size, 
        "%s%llu/%llu", 
        value.negative ? "- " : "", 
        value.p, 
        value.q
    );
}

size_t rational_to_string_v2(Rational value, char *pBuffer, size_t size) {
    if (value.q == 1) {
        return snprintf(
            pBuffer, 
            size, 
            "%s%llu", 
            value.negative ? "- " : "+ ", 
            value.p
        );
    }
    return snprintf(
        pBuffer, 
        size, 
        "%s%llu/%llu", 
        value.negative ? "- " : "+ ", 
        value.p, 
        value.q
    );
}

void rational_simplify(Rational *pValue) {
    UInteger divisor = gcd(pValue->p, pValue->q);
    if (divisor != 0) {
        pValue->p /= divisor;
        pValue->q /= divisor;
    }
}

void rational_add(Rational r1, Rational r2, Rational *pResult) {
    UInteger a, b;
    Rational result;
    result.q = r1.q / gcd(r1.q, r2.q) * r2.q;
    a = result.q / r1.q * r1.p;
    b = result.q / r2.q * r2.p;
    if (r1.negative == 0) {
        if (r2.negative == 0) { /* *p1 > 0 and *p2 > 0 */
            result.p = a + b;
            result.negative = 0;
        }
        else { /* *p1 > 0 and *p2 < 0 */
            if (a < b) {
                result.p = b - a;
                result.negative = 1;
            }
            else {
                result.p = a - b;
                result.negative = 0;
            }
        }
    }
    else {
        if (r2.negative == 0) { /* *p1 < 0 and *p2 > 0 */
            if (a < b) {
                result.p = b - a;
                result.negative = 0;
            }
            else {
                result.p = a - b;
                result.negative = 1;
            }
        }
        else { /* *p1 < 0 and *p2 < 0 */
            result.p = a + b;
            result.negative = 1;
        }
    }
    rational_simplify(&result);
    rational_copy(result, pResult);
}

void rational_multiply(Rational r1, Rational r2, Rational *pResult) {
    Rational result;
    result.p = r1.p * r2.p;
    result.q = r1.q * r2.q;
    result.negative = r1.negative ^ r2.negative; /* XOR */
    rational_simplify(&result);
    rational_copy(result, pResult);
}
