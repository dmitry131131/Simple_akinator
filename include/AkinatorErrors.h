/**
 * @file
 * @brief file with all akinator errors
*/
#ifndef AKINATOR_ERRORS_H
#define AKINATOR_ERRORS_H


enum akinatorErrorCode {
    NO_AKINATOR_ERRORS,
    READ_TREE_ERROR
};

void print_akinator_error(akinatorErrorCode error);

void print_akinator_error_message(akinatorErrorCode error, FILE* stream);

#endif