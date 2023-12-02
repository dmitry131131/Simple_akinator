#include <stdio.h>

#include "Tree.h"
#include "Akinator.h"

int main()
{
    akinatorErrorCode error = NO_AKINATOR_ERRORS;

    draw_akinator_label();
    
    if ((error = main_akinator_loop()))
    {
        print_akinator_error(error);
    }
}