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

static void skip_input();

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

        scanf("%c", &ch);
        skip_input();
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
                fflush(stdin);
            }
            break;

        case '5':
            if ((error = write_akinator_tree_to_file(&tree)))
            {
                printf("Try again!\n");
                fflush(stdin);
            }
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
    skip_input();

    if (error = read_tree_from_file(tree, filename))
    {
        print_tree_error(error);
        return READ_AKINATOR_TREE_ERROR;
    }

    return NO_AKINATOR_ERRORS;
}

akinatorErrorCode write_akinator_tree_to_file(TreeData* tree)
{
    assert(tree);

    treeErrorCode error = NO_TREE_ERRORS;
    char filename[FILENAME_LEN] = {};

    printf("Enter filename to write:\n");
    scanf("%s", filename);

    if (error = wrire_tree_to_file(filename, tree))
    {
        print_tree_error(error);
        return WRIRE_AKINATOR_TREE_ERROR;
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
    if ((!segment->left) && (!segment->right))
    {
        
    }
    char ch = 0;
    bool workFlag = true;
    

    while (workFlag)
    {
        printf("It is %s?\n", segment->data.stringPtr);
        printf("[y/n]\n");
        scanf("%c", &ch);
        skip_input();

        switch (ch)
        {
        case 'y':
            
            break;
        case 'n':

            break;
        
        default:
            printf("Please select y or no:");
            break;
        }
    }

}

static void skip_input()
{
    int ch = 0;
    while ((ch = getchar()) != '\n') {}
}