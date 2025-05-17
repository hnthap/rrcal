#include <stdio.h>
#include "argparse.h"
#include "macros.h"
#include "roottest.h"

int main(int argc, char *argv[]) {
    int rc, i, rootCount;
    char s[RRCAL_POLYNOMIAL_STRING_MAX_LENGTH];
    Rational roots[RRCAL_MAX_ROOT_COUNT];
    Arguments args;
    rc = parse_arguments(argc, argv, &args);
    if (rc) {
        (void)printf("\nError code: %d", rc);
        return rc;
    }
    if (polynomial_to_string(args.polynomial, s, RRCAL_POLYNOMIAL_STRING_MAX_LENGTH) == 0) {
        (void)printf("\nError: Failed to convert polynomial to string");
        return 1;
    }
    rc = test_rational_roots(args.polynomial, &rootCount, roots, RRCAL_MAX_ROOT_COUNT);
    if (rc) {
        (void)printf("\nError code: %d.", rc);
        return rc;
    }
    (void)printf("\n%shas %d rational root(s):", s, rootCount);
    for (i = 0; i < rootCount; i += 1) {
        if (roots[i].q == 1) {
            (void)printf("\n[%d]\t%s%llu", i + 1, roots[i].negative ? "- " : "", roots[i].p);
        }
        else {
            (void)printf(
                "\n[%d]\t%s%llu/%llu",
                i + 1, 
                roots[i].negative ? "- " : "", 
                roots[i].p, 
                roots[i].q
            );
        }
    }
    return 0;
}
