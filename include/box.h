#ifndef BOX_H
#define BOX_H

#include <mruby/data.h>

#include "helpers.h"
#include "macros.h"

DEFINE_DATA_TYPE( box, Box );

void mrb_fltk_box_class_init( mrb_state *mrb );

#endif // BOX_H
