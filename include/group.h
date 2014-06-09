#ifndef GROUP_H
#define GROUP_H

#include <mruby/data.h>

#include "helpers.h"
#include "macros.h"

DEFINE_DATA_TYPE( group, Group );

void mrb_fltk_group_class_init( mrb_state *mrb );

#endif // GROUP_H
