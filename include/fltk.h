#ifndef FLTK_H
#define FLTK_H

static mrb_value mrb_fltk_font_name_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_run_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_set_fonts_method( mrb_state *mrb, mrb_value self );
void mrb_fltk_module_init( mrb_state *mrb );

#endif // FLTK_H