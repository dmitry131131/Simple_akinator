/**
 * @file
 * @brief Main akinator functions sources
*/
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "AkinatorErrors.h"
#include "Tree.h"
#include "Akinator.h"

struct Call_array
{
    const TreeSegment** array;
    size_t len;
};


static treeErrorCode akinator_guess_object_recursive(TreeSegment* segment);

static akinatorErrorCode give_object_description_recursive(TreeSegment* segment);

static treeErrorCode add_new_akinator_node(TreeSegment* segment);

static akinatorErrorCode object_compare(const TreeSegment* first, const TreeSegment* second);

static size_t give_tree_depth(const TreeSegment* start_segment);

static void skip_input();

akinatorErrorCode main_akinator_loop()
{
    #define RETURN(code) do {                           \
        treeErrorCode treeErr;                          \
        if (tree.root)                                  \
        {                                               \
            if((treeErr = tree_dtor(&tree)))            \
            {                                           \
                print_tree_error(treeErr);              \
                return AKINATOR_TREE_DTOR_ERROR;        \
            }                                           \
        }                                               \
        return code;                                    \
    }while(0)

    akinatorErrorCode error = NO_AKINATOR_ERRORS;
    TreeData tree = {};

    char ch = 0;
    while (true)
    {
        error = NO_AKINATOR_ERRORS;
        draw_akinator_menu();

        scanf("%c[^\n]", &ch);
        __fpurge(stdin);
        switch (ch)
        {
        case '1':
            if ((error = akinator_guess_object(&tree)))
            {
                print_akinator_error(error);
            }
            __fpurge(stdin);
            break;
        case '2':
            if ((error = give_object_description(&tree)))
            {
                print_akinator_error(error);
            }
            __fpurge(stdin);
            break;

        case '3':
            if ((error = give_object_diff(&tree)))
            {
                print_akinator_error(error);
            }
            __fpurge(stdin);
            break;

        case '4':
            if ((error = read_akinator_base(&tree)))
            {
                printf("Try again!\n");
            }
            __fpurge(stdin);
            break;

        case '5':
            if ((error = write_akinator_tree_to_file(&tree)))
            {
                printf("Try again!\n");
            }
            __fpurge(stdin);
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

#define CHECK_OBJ(obj) do{                                      \
    if (!(obj))                                                 \
    {                                                           \
        printf("Object not found!\n");                          \
        return NO_AKINATOR_ERRORS;                              \
    }                                                           \
    if (((obj)->left != NULL) || ((obj)->right != NULL))        \
    {                                                           \
        printf("Object not found!\n");                          \
        return NO_AKINATOR_ERRORS;                              \
    }                                                           \
}while(0)

akinatorErrorCode give_object_diff(TreeData* tree)
{
    assert(tree);

    if (!(tree->root))
    {
        return AKINATOR_TREE_IS_NOT_EXIST;
    }
    akinatorErrorCode error = NO_AKINATOR_ERRORS;

    char* first  = NULL;
    char* second = NULL;
    size_t len = 0;

    printf("Please enter first object name: \n");

    ssize_t position_n = 0;
    position_n = getline(&first, &(len), stdin);
    first[position_n - 1] = '\0';

    TreeSegment* first_seg = find_segment(tree, first);
    free(first);
    first = NULL;
    CHECK_OBJ(first_seg);

    printf("Please enter second object name: \n");

    position_n = 0;
    position_n = getline(&second, &(len), stdin);
    second[position_n - 1] = '\0';

    TreeSegment* second_seg = find_segment(tree, second);
    free(second);
    first = NULL;
    CHECK_OBJ(second_seg);

    if ((error = object_compare(first_seg, second_seg)))
    {
        return error;
    }

    return NO_AKINATOR_ERRORS;
}

static akinatorErrorCode object_compare(const TreeSegment* first, const TreeSegment* second)
{
    if (!first || !second)
    {
        return NULL_AKINATOR_SEGMENT;
    }

    Call_array first_call_array  = {};
    Call_array second_call_array = {};

    first_call_array.len  = give_tree_depth(first);
    second_call_array.len = give_tree_depth(second);

    first_call_array.array  = (const TreeSegment**) calloc(first_call_array.len  + 1, sizeof(TreeSegment*));
    second_call_array.array = (const TreeSegment**) calloc(second_call_array.len + 1, sizeof(TreeSegment*));

    size_t count = 0;
    const TreeSegment* seg = first;
    while(seg->parent)
    {
        (first_call_array.array)[first_call_array.len - count] = seg;
        seg = seg->parent;
        count++;
    }
    (first_call_array.array)[first_call_array.len - count] = seg;

    count = 0;
    seg = second;
    while(seg->parent)
    {
        (second_call_array.array)[second_call_array.len - count] = seg;
        seg = seg->parent;
        count++;
    }
    (second_call_array.array)[second_call_array.len - count] = seg;

    printf("Both of them are: \n");

    count = 0;
    while (((first_call_array.array)[count]     == (second_call_array.array)[count]) 
        && ((first_call_array.array)[count + 1] == (second_call_array.array)[count + 1]))
    {
        if ((first_call_array.array)[count]->left == (first_call_array.array)[count + 1])
        {
            printf("not ");
        }

        printf("%s, ", (first_call_array.array)[count]->data.stringPtr);
        count++;
    }

    printf("\nBut %s is: \n", first->data.stringPtr);
    for (size_t i = count; i < first_call_array.len; i++)
    {
        if ((first_call_array.array)[i]->left == (first_call_array.array)[i + 1])
        {
            printf("not ");
        }

        printf("%s, ", (first_call_array.array)[i]->data.stringPtr);
    }

    printf("\nAnd %s is: \n", second->data.stringPtr);
    for (size_t i = count; i < second_call_array.len; i++)
    {
        if ((second_call_array.array)[i]->left == (second_call_array.array)[i + 1])
        {
            printf("not ");
        }

        printf("%s, ", (second_call_array.array)[i]->data.stringPtr);
    }

    printf("\n");

    free(first_call_array.array);
    free(second_call_array.array);

    return NO_AKINATOR_ERRORS;
}

static size_t give_tree_depth(const TreeSegment* start_segment)
{
    assert(start_segment);
    size_t count = 0;
    const TreeSegment* seg = start_segment;
    while (seg->parent) 
    {
        seg = seg->parent;
        count++;
    }

    return count;
}

akinatorErrorCode give_object_description(TreeData* tree)
{
    assert(tree);
    akinatorErrorCode error = NO_AKINATOR_ERRORS;

    if (!(tree->root))
    {
        return AKINATOR_TREE_IS_NOT_EXIST;
    }

    char* text = NULL;
    size_t len = 0;

    printf("Please enter object name: \n");

    ssize_t position_n = 0;
    position_n = getline(&text, &(len), stdin);
    text[position_n - 1] = '\0';

    TreeSegment* seg = find_segment(tree, text);

    free(text);

    CHECK_OBJ(seg);

    printf("This object: ");

    error = give_object_description_recursive(seg);

    printf("\n");

    return error;
}

#undef CHECK_OBJ

static akinatorErrorCode give_object_description_recursive(TreeSegment* segment)
{
    akinatorErrorCode error = NO_AKINATOR_ERRORS;
    if (!segment)
    {
        return FIND_AKINATOR_SEGMENT_ERROR;
    }

    if (segment->parent == nullptr)
    {
        return NO_AKINATOR_ERRORS;
    }

    if (segment->parent->right == segment)
    {
        printf("is %s, ", segment->parent->data.stringPtr);
    }
    else if (segment->parent->left == segment)
    {
        printf("is not %s, ", segment->parent->data.stringPtr);
    }
    
    error = give_object_description_recursive(segment->parent);

    return error;
}

akinatorErrorCode read_akinator_base(TreeData* tree)
{
    assert(tree);
    #define DTOR do{                        \
        if (tree_dtor(tree))                \
        {                                   \
            return ERROR_IN_TREE_DTOR;      \
        }                                   \
    }while(0)

    treeErrorCode error = NO_TREE_ERRORS;

    char filename[FILENAME_LEN] = {};

    printf("Enter filename to read:\n");
    scanf("%s", filename);
    skip_input();

    if ((error = read_tree_from_file(tree, filename)))
    {
        print_tree_error(error);
        return READ_AKINATOR_TREE_ERROR;
    }

    return NO_AKINATOR_ERRORS;
    #undef DTOR
}

akinatorErrorCode write_akinator_tree_to_file(TreeData* tree)
{
    assert(tree);

    treeErrorCode error = NO_TREE_ERRORS;
    char filename[FILENAME_LEN] = {};

    printf("Enter filename to write:\n");
    scanf("%s[^\n]", filename);

    if ((error = wrire_tree_to_file(filename, tree)))
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
        int count = 0;
        sscanf("Unknown_thing", "%ms%n", &(tree->root->data.stringPtr), &count);
        tree->root->data_len = (size_t) count;
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

    if ((error = copy_segment(segment->left, segment)))
    {
        return error;
    }

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
    while ((ch = getchar()) != '\n' && (ch != EOF)) {}
}