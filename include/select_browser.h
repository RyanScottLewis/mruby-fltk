#ifndef SELECT_BROWSER_H
#define SELECT_BROWSER_H

#include <mruby/data.h>

#include "helpers.h"
#include "macros.h"

DEFINE_DATA_TYPE( select_browser, SelectBrowser );

void mrb_fltk_select_browser_class_init( mrb_state *mrb );

#endif // SELECT_BROWSER_H
