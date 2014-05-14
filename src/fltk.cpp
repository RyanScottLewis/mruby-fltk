#include <mruby.h>

#include <Fl/Fl.h>

#include "macros.h"
#include "helpers.h"

// FLTK.font_name
// mrb_value
// mrb_fltk_font_name_module_method( mrb_state *mrb, mrb_value self ) {
//   mrb_value i;
//   mrb_get_args( mrb, "i", &i );
//
//   int font_type = 0;
//
//   const char *name = Fl::get_font_name( (Fl::Font)mrb_fixnum( i ), &font_type );
//
//   return name ? mrb_str_new_cstr( mrb, name ) : mrb_nil_value();
// }

// FLTK.run
mrb_value mrb_fltk_run_module_method( mrb_state *mrb, mrb_value self ) {
  return mrb_fixnum_value( Fl::run() );
}

// FLTK.set_fonts
// mrb_value
// mrb_fltk_set_fonts_module_method( mrb_state *mrb, mrb_value self ) {
//   mrb_value s;
//   mrb_get_args( mrb, "S", &s );
//
//   return mrb_fixnum_value( Fl::set_fonts( RSTRING_PTR( s ) ) );
// }

void mrb_fltk_module_init( mrb_state *mrb ) {
  ARENA_SAVE;

  struct RClass *mrb_fltk_module = mrb_define_module( mrb, "FLTK" );

  // DEFINE_MODULE_METHOD( root, font_name, MRB_ARGS_REQ( 1 ) );
  mrb_define_module_function( mrb, mrb_fltk_module, "run", mrb_fltk_run_module_method, MRB_ARGS_NONE() );
  // DEFINE_MODULE_METHOD( root, set_fonts, MRB_ARGS_REQ( 1 ) );

  ARENA_RESTORE;
}
