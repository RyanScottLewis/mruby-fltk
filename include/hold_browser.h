#ifndef HOLD_BROWSER_H
#define HOLD_BROWSER_H

#include <mruby/data.h>

#include "helpers.h"
#include "macros.h"

DEFINE_DATA_TYPE( hold_browser, HoldBrowser );

void mrb_fltk_hold_browser_class_init( mrb_state *mrb );

#endif // HOLD_BROWSER_H
