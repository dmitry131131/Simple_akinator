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
    #define RETURN(code) do {         \
        tree_dtor(&tree);             \
        return code;                  \
    }while(0)

    akinatorErrorCode error = NO_AKINATOR_ERRORS;
    TreeData tree = {};

    char ch = 0;
    bool loop_enable = true;
    while (loop_enable)
    {
        draw_akinator_menu();

        ch = (char) getchar();
        switch (ch)
        {
        case '1':
            
            break;
        case '2':

            break;

        case '3':

            break;

        case '4':
            if ((error = read_akinator_base(&tree)))
            {
                printf("Try again!\n");
            }
            break;

        case '5':

            break;

        case '6':
            tree_dump(&tree);
            break;

        case 'q':
            RETURN(error);
            break;
        
        default:
            printf("Invalid input, try again!\n");
            break;
        }
    }

    RETURN(error);
    #undef RETURN
}

akinatorErrorCode read_akinator_base(TreeData* tree)
{
    assert(tree);

    treeErrorCode error = NO_TREE_ERRORS;
    char filename[FILENAME_LEN] = {};

    printf("Enter filename to read:\n");
    scanf("%s", filename);

    if (error = read_tree_from_file(tree, filename))
    {
        print_tree_error(error);
        return READ_TREE_ERROR;
    }

    return NO_AKINATOR_ERRORS;
}

void draw_akinator_label()
{
    printf(
        " █████╗ ██╗  ██╗██╗███╗   ██╗ █████╗ ████████╗ ██████╗ ██████╗ \n"
        "██╔══██╗██║ ██╔╝██║████╗  ██║██╔══██╗╚══██╔══╝██╔═══██╗██╔══██╗\n"
        "███████║█████╔╝ ██║██╔██╗ ██║███████║   ██║   ██║   ██║██████╔╝\n"
        "██╔══██║██╔═██╗ ██║██║╚██╗██║██╔══██║   ██║   ██║   ██║██╔══██╗\n"
        "██║  ██║██║  ██╗██║██║ ╚████║██║  ██║   ██║   ╚██████╔╝██║  ██║\n"
        "╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝\n\n"
    );   
}

void draw_akinator_menu()
{
    printf(
        "Select mode:\n"
        "1 - Guess object\n"
        "2 - Give obgect description\n"
        "3 - Compare 2 objects\n"
        "4 - Read akinator tree\n"
        "5 - Write akinator tree\n"
        "6 - Show akinator tree\n"
        "q - Exit\n"
    );
}

akinatorErrorCode akinator_guess_object(TreeData* tree)
{
    assert(tree);



    return NO_AKINATOR_ERRORS;
}

static void akinator_guess_object_recursive(TreeSegment* segment)
{
    
}