#ifndef WINDOW_H
#define WINDOW_H

#include <mruby/data.h>

#include "helpers.h"
#include "macros.h"

DEFINE_DATA_TYPE( window, Window );

void mrb_fltk_window_class_init( mrb_state *mrb );

#endif // WINDOW_H
