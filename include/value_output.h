#ifndef VALUE_OUTPUT_H
#define VALUE_OUTPUT_H

static mrb_value mrb_fltk_value_output_initialize_method(mrb_state *mrb, mrb_value self);

#define DEFINE_FLTK_VALUE_OUTPUT_CLASS()                              \
  ARENA_SAVE;                                                         \
                                                                      \
  DEFINE_CLASS( value_output, "ValueOutput", mrb_fltk_widget_class ); \
                                                                      \
  ARENA_RESTORE;

#endif // VALUE_OUTPUT_H
