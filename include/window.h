#ifndef WINDOW_H
#define WINDOW_H

DECLARE_WINDOW( window, Fl_Window );

static mrb_value mrb_fltk_window_show_method(mrb_state *mrb, mrb_value self);

#define DEFINE_FLTK_WINDOW_CLASS()                           \
  ARENA_SAVE;                                                \
                                                             \
  DEFINE_CLASS( window, "Window", mrb_fltk_widget_class );   \
                                                             \
  DEFINE_INSTANCE_METHOD( window, initialize, ARGS_ANY()  ); \
  DEFINE_INSTANCE_METHOD( window, show, ARGS_OPT(1) );       \
                                                             \
  DEFINE_GROUP_INSTANCE_METHODS( window );                   \
                                                             \
  ARENA_RESTORE;

#endif // WINDOW_H
