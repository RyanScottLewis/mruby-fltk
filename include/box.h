#ifndef BOX_H
#define BOX_H

#include <mruby/data.h>

#include "helpers.h"
#include "macros.h"

DEFINE_DATA_TYPE( box, Box );

mrb_value mrb_fltk_box_initialize_instance_method( mrb_state *mrb, mrb_value self );
void mrb_fltk_box_class_init( mrb_state *mrb );

#endif // BOX_H
