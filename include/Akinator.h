/**
 * @file
 * @brief All main akinator functions
*/
#ifndef AKINATOR_H
#define AKINATOR_H

#include "AkinatorErrors.h"

akinatorErrorCode draw_akinator_menu();

akinatorErrorCode read_akinator_base(TreeData* tree, const char* filename);

#endif