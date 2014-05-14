#ifndef WINDOW_H
#define WINDOW_H

#include <mruby/data.h>

#include "macros.h"

DEFINE_DATA_TYPE( window, Window );

mrb_value mrb_fltk_window_initialize_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_window_show_instance_method( mrb_state *mrb, mrb_value self );
void mrb_fltk_window_class_init( mrb_state *mrb );

#endif // WINDOW_H
