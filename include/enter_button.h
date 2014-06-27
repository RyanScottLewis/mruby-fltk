#ifndef ENTER_BUTTON_H
#define ENTER_BUTTON_H

#include <mruby/data.h>

#include "helpers.h"
#include "macros.h"

DEFINE_DATA_TYPE( enter_button, EnterButton );

void mrb_fltk_enter_button_class_init( mrb_state *mrb );

#endif // ENTER_BUTTON_H
