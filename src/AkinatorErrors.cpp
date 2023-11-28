#include <stdio.h>

#include "Color_output.h"
#include "AkinatorErrors.h"

void print_akinator_error(akinatorErrorCode error)
{
    print_akinator_error_message(error, stderr);
}

void print_akinator_error_message(akinatorErrorCode error, FILE* stream)
{
    color_fprintf(stream, COLOR_RED, STYLE_BOLD, "Data Buffer error: ");

    #define CHECK_CODE(code, message)               \
        case code:                                  \
            fprintf(stream, message);               \
            break;                                  \

    switch (error)
    {
        case NO_AKINATOR_ERRORS:
            break;

        CHECK_CODE(READ_TREE_ERROR,          "Error in file reading process!\n");

    default:
        fprintf(stream, "Unknown error!\n");
        break;
    }
    #undef CHECK_CODE
}