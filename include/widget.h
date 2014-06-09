#ifndef WIDGET_H
#define WIDGET_H

#include <mruby/data.h>

#include "helpers.h"
#include "macros.h"

DEFINE_DATA_TYPE( widget, Widget );

void mrb_fltk_widget_class_init( mrb_state *mrb );

#endif // WIDGET_H