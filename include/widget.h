#ifndef WIDGET_H
#define WIDGET_H

static mrb_value mrb_fltk_widget_initialize_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_widget_callback_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_widget_hide_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_widget_image_get_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_widget_image_set_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_widget_redraw_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_widget_show_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_widget_visible_method(mrb_state *mrb, mrb_value self);
void mrb_fltk_widget_class_init(mrb_state *mrb);

#endif // WIDGET_H