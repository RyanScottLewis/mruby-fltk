#ifndef BUTTON_H
#define BUTTON_H

#include <mruby/data.h>

#include "helpers.h"
#include "macros.h"

DEFINE_DATA_TYPE( button, Button );

void mrb_fltk_button_class_init( mrb_state *mrb );

#endif // BUTTON_H
