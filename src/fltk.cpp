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
