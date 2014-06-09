#ifndef BUTTON_H
#define BUTTON_H

#include <mruby/data.h>

#include "helpers.h"
#include "macros.h"

DEFINE_DATA_TYPE( button, Button );

mrb_value mrb_fltk_button_initialize_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_button_shortcut_getter_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_button_shortcut_setter_instance_method( mrb_state *mrb, mrb_value self );
void mrb_fltk_button_class_init( mrb_state *mrb );

#endif // BUTTON_H
