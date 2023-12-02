/**
 * @file
 * @brief All main akinator functions
*/
#ifndef AKINATOR_H
#define AKINATOR_H

#include "config.h"
#include "AkinatorErrors.h"

void draw_akinator_menu();

void draw_akinator_label();

akinatorErrorCode read_akinator_base(TreeData* tree);

akinatorErrorCode write_akinator_tree_to_file(TreeData* tree);

akinatorErrorCode akinator_guess_object(TreeData* tree);

akinatorErrorCode give_object_description(TreeData* tree);

akinatorErrorCode main_akinator_loop();

#endif