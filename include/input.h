#ifndef INPUT_H
#define INPUT_H

#define DEFINE_FLTK_INPUT_CLASS()                                     \
  ARENA_SAVE;                                                         \
                                                                      \
  DEFINE_CLASS( input, "Input", mrb_fltk_widget_class );              \
                                                                      \
  DEFINE_STRING_ATTRIBUTE_ACCESSOR( input, value, Fl_Widget, value ); \
                                                                      \
  ARENA_RESTORE;

#endif // INPUT_H
