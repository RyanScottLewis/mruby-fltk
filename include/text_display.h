#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

static mrb_value mrb_fltk_text_display_initialize_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_text_display_buffer_get_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_text_display_buffer_set_method(mrb_state *mrb, mrb_value self);

#define DEFINE_FLTK_TEXT_DISPLAY_CLASS()                                                                                  \
  ARENA_SAVE;                                                                                                             \
                                                                                                                          \
  DEFINE_CLASS( text_display, "TextDisplay", mrb_fltk_group_class );                                                      \
                                                                                                                          \
  mrb_define_method( mrb, mrb_fltk_text_display_class, "buffer",  mrb_fltk_text_display_buffer_get_method, ARGS_NONE() ); \
  mrb_define_method( mrb, mrb_fltk_text_display_class, "buffer=", mrb_fltk_text_display_buffer_set_method, ARGS_REQ(1) ); \
                                                                                                                          \
  ARENA_RESTORE;

#endif // TEXT_DISPLAY_H
