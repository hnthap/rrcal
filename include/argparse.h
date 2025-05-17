#ifndef RRCAL_ARGPARSE_H
#define RRCAL_ARGPARSE_H

#include "polynomial.h"

/**
 * @brief Struct defining the set of values input via command arguments.
 * 
 */
typedef struct {
    Polynomial polynomial;
} Arguments;

/**
 * @brief Parse command's arguments.
 * 
 * @param argc Number of arguments
 * @param argv Array of arguments (array of char pointers)
 * @param pArgs Pointer to an Arguments
 * @return 0 if success, otherwise, another value.
 */
int parse_arguments(int argc, char *argv[], Arguments *pArgs);

#endif  /* RRCAL_ARGPARSE_H */