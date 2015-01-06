#include <mruby.h>
#include <mruby/data.h>
#include <mruby/string.h>

#include <Fl/Fl_Hold_Browser.h>

#include "macros.h"
#include "helpers.h"
#include "browser.h"
#include "hold_browser.h"

// FLTK::HoldBrowser#initialize
mrb_value mrb_fltk_hold_browser_initialize_instance_method( mrb_state *mrb, mrb_value self ) {
  SETUP_DATA_TYPE( hold_browser );

  mrb_value *argv;
  int argc;
  Fl_Hold_Browser *fl_hold_browser;

  mrb_get_args( mrb, "*", &argv, &argc );

  if( mrb_fltk_arg_check( "iiii", argc, argv ) ) { // x, y, width, height
    fl_hold_browser = new Fl_Hold_Browser( (int)mrb_fixnum( argv[0] ), (int)mrb_fixnum( argv[1] ), (int)mrb_fixnum( argv[2] ), (int)mrb_fixnum( argv[3] ) );
  } else if( mrb_fltk_arg_check( "iiiis", argc, argv ) ) { // x, y, width, height, label
    fl_hold_browser = new Fl_Hold_Browser( (int)mrb_fixnum( argv[0] ), (int)mrb_fixnum( argv[1] ), (int)mrb_fixnum( argv[2] ), (int)mrb_fixnum( argv[3] ), RSTRING_PTR( argv[4] ) );
  } else {
    mrb_raise( mrb, E_ARGUMENT_ERROR, "invalid argument" ); // TODO: Error should show valid arguments

    return mrb_nil_value(); // NOTE: Won't reach here but shut's up compiler warnings
  }

  SETUP_DATA_POINTER( fl_hold_browser );

  return self;
}

void mrb_fltk_hold_browser_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  struct RClass *mrb_fltk_module = mrb_module_get( mrb, "FLTK" );
  struct RClass *mrb_fltk_browser_class = mrb_class_get_under( mrb, mrb_fltk_module, "Browser" );

  DEFINE_CLASS( hold_browser, HoldBrowser, mrb_fltk_browser_class );

  DEFINE_INSTANCE_METHOD( hold_browser, initialize, ARGS_ANY() );

  ARENA_RESTORE;
}
