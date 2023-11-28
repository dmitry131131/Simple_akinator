#include <stdio.h>

#include "Tree.h"
#include "Akinator.h"

void ggg(TreeSegment* seg, double num);

int main()
{
    #define RETURN(err) do{                 \
        tree_dtor(&tree);                   \
        return 0;                           \
    }while(0)

    treeErrorCode error = NO_TREE_ERRORS;

    draw_akinator_label();
    
    main_akinator_loop();

    #undef RETURN
}