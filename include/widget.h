#ifndef WIDGET_H
#define WIDGET_H

#include <mruby/data.h>

#include "helpers.h"
#include "macros.h"

DEFINE_DATA_TYPE( widget, Widget );

// mrb_value mrb_fltk_widget_image_getter_instance_method( mrb_state *mrb, mrb_value self );
// mrb_value mrb_fltk_widget_image_setter_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_widget_callback_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_widget_height_getter_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_widget_hide_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_widget_label_getter_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_widget_label_setter_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_widget_parent_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_widget_redraw_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_widget_show_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_widget_visible_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_widget_width_getter_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_widget_x_getter_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_widget_y_getter_instance_method( mrb_state *mrb, mrb_value self );

void mrb_fltk_widget_class_init( mrb_state *mrb );

#endif // WIDGET_H