#ifndef WINDOW_H
#define WINDOW_H

#define DEFINE_FLTK_WINDOW_CLASS()                                      \
  ARENA_SAVE;                                                           \
                                                                        \
  DEFINE_CLASS( double_window, "DoubleWindow", mrb_fltk_window_class ); \
                                                                        \
  ARENA_RESTORE;

#endif // WINDOW_H
