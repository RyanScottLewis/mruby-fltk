#ifndef SELECT_BROWSER_H
#define SELECT_BROWSER_H

#include <mruby/data.h>

#include "helpers.h"
#include "macros.h"

DEFINE_DATA_TYPE( select_browser, SelectBrowser );

mrb_value mrb_fltk_select_browser_initialize_instance_method( mrb_state *mrb, mrb_value self );
void mrb_fltk_select_browser_class_init( mrb_state *mrb );

#endif // SELECT_BROWSER_H
