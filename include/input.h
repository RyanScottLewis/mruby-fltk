#ifndef INPUT_H
#define INPUT_H

#include <mruby/data.h>

#include "helpers.h"
#include "macros.h"

DEFINE_DATA_TYPE( input, Input );

void mrb_fltk_input_class_init( mrb_state *mrb );

#endif // INPUT_H
