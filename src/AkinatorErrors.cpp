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

        CHECK_CODE(READ_AKINATOR_TREE_ERROR,          "Error in file reading process!\n");
        CHECK_CODE(WRIRE_AKINATOR_TREE_ERROR,         "Error in file writing process!\n");
        CHECK_CODE(CREATE_NEW_TREE_ERROR,             "Error in creating new tree!\n");
        CHECK_CODE(GUESS_RECURSIVE_ERROR,             "Error guessing element in tree!\n");
        CHECK_CODE(ERROR_IN_TREE_DTOR,                "Error in distructing tree!\n");

    default:
        fprintf(stream, "Unknown error!\n");
        break;
    }
    #undef CHECK_CODE
}