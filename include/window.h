#ifndef WINDOW_H
#define WINDOW_H

static mrb_value mrb_fltk_window_initialize_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_window_show_method(mrb_state *mrb, mrb_value self);
void mrb_fltk_window_class_init(mrb_state *mrb);

#endif // WINDOW_H
