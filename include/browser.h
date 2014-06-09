#ifndef BROWSER_H
#define BROWSER_H

#include <mruby/data.h>

#include "helpers.h"
#include "macros.h"

DEFINE_DATA_TYPE( browser, Browser );

void mrb_fltk_browser_class_init( mrb_state *mrb );

#endif // BROWSER_H
