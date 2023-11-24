#include <stdio.h>

#include "Tree.h"

void ggg(TreeSegment* seg, double num);

int main()
{
    #define RETURN(err) do{                 \
        tree_dtor(&tree);                   \
        return 0;                           \
    }while(0)

    TreeData tree = {};
    treeErrorCode error = NO_TREE_ERRORS;

    
    if ((error = tree_ctor(&tree)))
    {
        print_tree_error(error);
        RETURN(error);
    }

    double num = 0;

    scanf("%lf", &num);

    tree.root->data.D_number = num;
    tree.root->type = DOUBLE_SEGMENT_DATA;

    while(scanf("%lf", &num))
    {
        ggg(tree.root, num);
    }
    
    tree_dump(&tree);

    RETURN(0);

    #undef RETURN
}

void ggg(TreeSegment* seg, double num)
{
    if (num > seg->data.D_number)
    {
        if (seg->right)
        {
            ggg(seg->right, num);
        }
        else
        {
            seg->right = new_segment(DOUBLE_SEGMENT_DATA, sizeof(double), &(seg->right));
            seg->right->data.D_number = num;
        }
    }
    else
    {
        if (seg->left)
        {
            ggg(seg->left, num);
        }
        else
        {
            seg->left = new_segment(DOUBLE_SEGMENT_DATA, sizeof(double), &(seg->left));
            seg->left->data.D_number = num;
        }
    }
}