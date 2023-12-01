/**
 * @file
 * @brief Main akinator functions sources
*/
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "AkinatorErrors.h"
#include "Tree.h"
#include "Akinator.h"

static treeErrorCode akinator_guess_object_recursive(TreeSegment* segment);

static treeErrorCode add_new_akinator_node(TreeSegment* segment);

static void skip_input();

akinatorErrorCode main_akinator_loop()
{
    #define RETURN(code) do {                       \
        treeErrorCode treeErr;                      \
        if((treeErr = tree_dtor(&tree)))            \
        {                                           \
            print_tree_error(treeErr);              \
        }                                           \
        return code;                                \
    }while(0)

    akinatorErrorCode error = NO_AKINATOR_ERRORS;
    TreeData tree = {};

    char ch = 0;
    while (true)
    {
        draw_akinator_menu();

        scanf("%c[^\n]", &ch);
        skip_input();
        switch (ch)
        {
        case '1':
            akinator_guess_object(&tree);
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

    if (tree->root)
    {
        if (tree_dtor(tree))
        {
            return ERROR_IN_TREE_DTOR;
        }
    }

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
    scanf("%s[^\n]", filename);

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
    treeErrorCode error = NO_TREE_ERRORS;

    if (!(tree->root))
    {
        tree->root = new_segment(TEXT_SEGMENT_DATA, MAX_TEXT_LEN, tree->root, &error);
        if (error)
        {
            return CREATE_NEW_TREE_ERROR;
        }
        strcpy(tree->root->data.stringPtr, "Unknown_thing");
    }

    if ((error = akinator_guess_object_recursive(tree->root)))
    {
        return GUESS_RECURSIVE_ERROR;
    }

    return NO_AKINATOR_ERRORS;
}

static treeErrorCode akinator_guess_object_recursive(TreeSegment* segment)
{
    treeErrorCode error = NO_TREE_ERRORS;
    if (!segment)
    {
        return NULL_SEGMENT_POINTER;
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
            if (segment->right)
            {
                error = akinator_guess_object_recursive(segment->right);
                workFlag = false;
            }
            else
            {
                printf("I said, I know this thing\n");
                workFlag = false;
            }
            break;

        case 'n':
            if (segment->left)
            {
                error = akinator_guess_object_recursive(segment->left);
                workFlag = false;
            }
            else
            {
                error = add_new_akinator_node(segment);
                workFlag = false;
            }
            break;
        
        default:
            printf("Please select y or n:\n");
            break;
        }
    }

    return error;
}

static treeErrorCode add_new_akinator_node(TreeSegment* segment)
{
    assert(segment);
    treeErrorCode error = NO_TREE_ERRORS;

    segment->right = new_segment(TEXT_SEGMENT_DATA, MAX_TEXT_LEN, segment, &error);
    if (error)
    {
        return error;
    }

    segment->left = new_segment(TEXT_SEGMENT_DATA, segment->data_len, segment, &error);
    if (error)
    {
        return error;
    }

    strncpy(segment->left->data.stringPtr, segment->data.stringPtr, MAX_TEXT_LEN);

    ssize_t position_n = 0;
    printf("What is it?\n");
    position_n = getline(&(segment->right->data.stringPtr), &(segment->right->data_len), stdin);
    segment->right->data.stringPtr[position_n - 1] = '\0';
    
    printf("What the difference betwin %s and %s?\n", segment->right->data.stringPtr, segment->left->data.stringPtr);
    position_n = getline(&(segment->data.stringPtr), &(segment->data_len), stdin);
    segment->data.stringPtr[position_n - 1] = '\0';

    return NO_TREE_ERRORS;
}

static void skip_input()
{
    int ch = 0;
    while ((ch = getchar()) != '\n' || (ch == EOF)) {}
}