// FLTK.font_name
static mrb_value
mrb_fltk_font_name_method(mrb_state *mrb, mrb_value self)
{
  mrb_value i;
  mrb_get_args(mrb, "i", &i);
  
  int font_type = 0;
  
  const char *name = Fl::get_font_name( (Fl::Font) mrb_fixnum(i), &font_type );
  
  return name ? mrb_str_new_cstr(mrb, name) : mrb_nil_value();
}

// FLTK.run
static mrb_value
mrb_fltk_run_method(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value( Fl::run() );
}

// FLTK.set_fonts
static mrb_value
mrb_fltk_set_fonts_method(mrb_state *mrb, mrb_value self)
{
  mrb_value s;
  mrb_get_args(mrb, "S", &s);
  
  return mrb_fixnum_value( Fl::set_fonts( RSTRING_PTR(s) ) );
}

void
mrb_fltk_module_init(mrb_state *mrb)
{
  ARENA_SAVE;
  
  struct RClass *mrb_fltk_module = mrb_define_module(mrb, "FLTK");
  
  mrb_define_module_function( mrb, mrb_fltk_module, "font_name", mrb_fltk_font_name, ARGS_REQ(1) );
  mrb_define_module_function( mrb, mrb_fltk_module, "run",       mrb_fltk_run,       ARGS_NONE() );
  mrb_define_module_function( mrb, mrb_fltk_module, "set_fonts", mrb_fltk_set_fonts, ARGS_REQ(1) );
  
  ARENA_RESTORE;
}
