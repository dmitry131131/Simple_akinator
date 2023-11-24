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
        case NO_DATA_BUFFER_ERRORS:
            break;

        CHECK_CODE(ALLOC_MEMORY_ERROR,          "Error in calloc, alloced memory for buffer!\n");

    default:
        fprintf(stream, "Unknown error!\n");
        break;
    }
    #undef CHECK_CODE
}