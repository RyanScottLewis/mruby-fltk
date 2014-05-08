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

#define DEFINE_FLTK_WIDGET_CLASS()                                                                               \
  ARENA_SAVE;                                                                                                    \
                                                                                                                 \
  DEFINE_CLASS( widget, "Widget", mrb->object_class );                                                           \
                                                                                                                 \
  DEFINE_INSTANCE_METHOD( widget, callback,   ARGS_OPT(1) );                                                     \
  DEFINE_INSTANCE_METHOD( widget, hide,       ARGS_NONE() );                                                     \
  DEFINE_INSTANCE_METHOD( widget, initialize, ARGS_ANY() );                                                      \
  DEFINE_INSTANCE_METHOD( widget, redraw,     ARGS_NONE() );                                                     \
  DEFINE_INSTANCE_METHOD( widget, show,       ARGS_NONE() );                                                     \
                                                                                                                 \
  DEFINE_FIXNUM_ATTRIBUTE_READER( widget, height, Fl_Widget, h );                                                \
  DEFINE_FIXNUM_ATTRIBUTE_READER( widget, width,  Fl_Widget, w );                                                \
  DEFINE_FIXNUM_ATTRIBUTE_READER( widget, x,      Fl_Widget, x );                                                \
  DEFINE_FIXNUM_ATTRIBUTE_READER( widget, y,      Fl_Widget, y );                                                \
                                                                                                                 \
  DEFINE_FIXNUM_ATTRIBUTE_ACCESSOR( widget, box,        Fl_Widget, box );                                        \
  DEFINE_FIXNUM_ATTRIBUTE_ACCESSOR( widget, label_font, Fl_Widget, labelfont );                                  \
  DEFINE_FIXNUM_ATTRIBUTE_ACCESSOR( widget, label_size, Fl_Widget, labelsize );                                  \
                                                                                                                 \
  DEFINE_STRING_ATTRIBUTE_ACCESSOR( widget, label, Fl_Widget, label );                                           \
                                                                                                                 \
  mrb_define_method( mrb, mrb_fltk_widget_class, "image",      mrb_fltk_widget_image_get_method,  ARGS_NONE() ); \
  mrb_define_method( mrb, mrb_fltk_widget_class, "image=",     mrb_fltk_widget_image_set_method,  ARGS_REQ(1) ); \
  mrb_define_method( mrb, mrb_fltk_widget_class, "visible?",   mrb_fltk_widget_visible,           ARGS_NONE() ); \
                                                                                                                 \
  ARENA_RESTORE;

#endif // WIDGET_H