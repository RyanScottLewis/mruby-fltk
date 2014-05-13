#ifndef WIDGET_H
#define WIDGET_H

#include <memory.h>

#include <mruby/data.h>
#include <mruby/variable.h>

#include <Fl/Fl_Widget.h>

#include "mrb_fltk.h"
#include "helpers.h"

CONTEXT_DEFINE( widget, Widget, Fl_Widget );

static mrb_value mrb_fltk_widget_initialize_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_widget_callback_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_widget_hide_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_widget_image_get_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_widget_image_set_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_widget_redraw_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_widget_show_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_widget_visible_method( mrb_state *mrb, mrb_value self );
void mrb_fltk_widget_class_init( mrb_state *mrb );

#endif // WIDGET_H