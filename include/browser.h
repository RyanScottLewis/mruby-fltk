#ifndef BROWSER_H
#define BROWSER_H

#include <mruby/data.h>

#include "helpers.h"
#include "macros.h"

DEFINE_DATA_TYPE( browser, Browser );

mrb_value mrb_fltk_browser_initialize_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_browser_add_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_browser_clear_instance_method( mrb_state *mrb, mrb_value self );
void mrb_fltk_browser_class_init( mrb_state *mrb );

#endif // BROWSER_H
