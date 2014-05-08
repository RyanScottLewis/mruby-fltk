#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

static mrb_value mrb_fltk_text_display_initialize_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_text_display_buffer_get_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_text_display_buffer_set_method(mrb_state *mrb, mrb_value self);
void mrb_fltk_text_display_class_init(mrb_state *mrb);

#endif // TEXT_DISPLAY_H
