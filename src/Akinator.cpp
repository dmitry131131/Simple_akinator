/**
 * @file
 * @brief Main akinator functions sources
*/
#include <stdio.h>
#include <assert.h>

#include "AkinatorErrors.h"
#include "Tree.h"
#include "Akinator.h"

static void akinator_guess_object_recursive(TreeSegment* segment);

akinatorErrorCode main_akinator_loop()
{
    akinatorErrorCode error = NO_AKINATOR_ERRORS;

    TreeData tree = {};

    char ch = 0;
    bool loop_enable = true;
    while (loop_enable)
    {
        error = draw_akinator_menu();

        ch = getchar();
        switch (ch)
        {
        case '1':
            
            break;
        case '2':

            break;

        case '3':

            break;

        case '4':

            break;

        case '5':

            break;

        case 'q':
            
            break;
        
        default:
            printf("Invalid input, try again!\n");
            break;
        }
    }
    

    return error;
}

akinatorErrorCode read_akinator_base(TreeData* tree, const char* filename)
{
    assert(tree);
    assert(filename);

    treeErrorCode tree_err = NO_TREE_ERRORS;

    if (tree_err = read_tree_from_file(tree, filename))
    {
        print_tree_error(tree_err);
        return READ_TREE_ERROR;
    }

    return NO_AKINATOR_ERRORS;
}

akinatorErrorCode draw_akinator_menu()
{
    printf(
        " █████╗ ██╗  ██╗██╗███╗   ██╗ █████╗ ████████╗ ██████╗ ██████╗ \n"
        "██╔══██╗██║ ██╔╝██║████╗  ██║██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗\n"
        "███████║█████╔╝ ██║██╔██╗ ██║███████║   ██║   ██║   ██║██████╔╝\n"
        "██╔══██║██╔═██╗ ██║██║╚██╗██║██╔══██║   ██║   ██║   ██║██╔══██╗\n"
        "██║  ██║██║  ██╗██║██║ ╚████║██║  ██║   ██║   ╚██████╔╝██║  ██║\n"
        "╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝\n\n"
    );
    printf(
        "Select mode:"
        "1 - Guess object\n"
        "2 - Give obgect description\n"
        "3 - Compare 2 objects\n"
        "4 - Read akinator tree\n"
        "5 - Write akinator tree\n"
        "q - Exit"
    );

    return NO_AKINATOR_ERRORS;
}

akinatorErrorCode akinator_guess_object(TreeData* tree)
{
    assert(tree);



    return NO_AKINATOR_ERRORS;
}

static void akinator_guess_object_recursive(TreeSegment* segment)
{
    
}