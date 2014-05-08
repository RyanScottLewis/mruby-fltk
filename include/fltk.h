#ifndef FLTK_H
#define FLTK_H

static mrb_value mrb_fltk_font_name_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_run_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_set_fonts_method(mrb_state *mrb, mrb_value self);

#define DEFINE_FLTK_MODULE()                                                                           \
  ARENA_SAVE;                                                                                          \
                                                                                                       \
  struct RClass *mrb_fltk_module = mrb_define_module(mrb, "FLTK");                                     \
                                                                                                       \
  mrb_define_module_function( mrb, mrb_fltk_module, "font_name",    mrb_fltk_font_name, ARGS_REQ(1) ); \
  mrb_define_module_function( mrb, mrb_fltk_module, "run",          mrb_fltk_run,       ARGS_NONE() ); \
  mrb_define_module_function( mrb, mrb_fltk_module, "set_fonts",    mrb_fltk_set_fonts, ARGS_REQ(1) ); \
                                                                                                       \
  ARENA_RESTORE;

#endif // FLTK_H