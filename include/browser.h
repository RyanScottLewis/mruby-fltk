#ifndef BROWSER_H
#define BROWSER_H

static mrb_value mrb_fltk_browser_add_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_browser_column_widths_get_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_browser_column_widths_set_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_browser_icon_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_browser_load_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_browser_text_method(mrb_state *mrb, mrb_value self);

#define DEFINE_FLTK_BROWSER_CLASS()                                                                                 \
  ARENA_SAVE;                                                                                                       \
                                                                                                                    \
  DEFINE_CLASS( browser, "Browser", mrb_fltk_group_class );                                                         \
                                                                                                                    \
  DEFINE_INSTANCE_METHOD( browser, load, ARGS_REQ(1)               );                                               \
  DEFINE_INSTANCE_METHOD( browser, text, ARGS_REQ(1) | ARGS_OPT(1) );                                               \
  DEFINE_INSTANCE_METHOD( browser, icon, ARGS_REQ(1) | ARGS_OPT(1) );                                               \
                                                                                                                    \
  DEFINE_FIXNUM_ATTRIBUTE_ACCESSOR( widget, value, Fl_Browser, value );                                             \
                                                                                                                    \
  mrb_define_method( mrb, mrb_fltk_widget_class, "column_widths",  mrb_fltk_widget_image_get_method, ARGS_NONE() ); \
  mrb_define_method( mrb, mrb_fltk_widget_class, "column_widths=", mrb_fltk_widget_image_set_method, ARGS_REQ(1) ); \
                                                                                                                    \
  ARENA_RESTORE;

#endif // BROWSER_H
