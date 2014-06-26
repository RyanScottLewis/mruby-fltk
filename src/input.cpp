#include <mruby.h>
#include <mruby/data.h>
#include <mruby/string.h>

#include <Fl/Fl_Input.h>

#include "macros.h"
#include "helpers.h"
#include "widget.h"
#include "input.h"

// FLTK::Input#initialize
mrb_value mrb_fltk_input_initialize_instance_method( mrb_state *mrb, mrb_value self ) {
  SETUP_DATA_TYPE( input );

  mrb_value *argv;
  int argc;
  Fl_Input *fl_input;

  mrb_get_args( mrb, "*", &argv, &argc );

  if( mrb_fltk_arg_check( "iiii", argc, argv ) ) { // x, y, width, height
    fl_input = new Fl_Input( (int)mrb_fixnum( argv[0] ), (int)mrb_fixnum( argv[1] ), (int)mrb_fixnum( argv[2] ), (int)mrb_fixnum( argv[3] ) );
  } else if( mrb_fltk_arg_check( "iiiis", argc, argv ) ) { // x, y, width, height, label
    fl_input = new Fl_Input( (int)mrb_fixnum( argv[0] ), (int)mrb_fixnum( argv[1] ), (int)mrb_fixnum( argv[2] ), (int)mrb_fixnum( argv[3] ), RSTRING_PTR( argv[4] ) );
  } else {
    mrb_raise( mrb, E_ARGUMENT_ERROR, "invalid argument" ); // TODO: Error should show valid arguments

    return mrb_nil_value(); // NOTE: Won't reach here but shut's up compiler warnings
  }

  SETUP_DATA_POINTER( fl_input );

  return self;
}

// FLTK::Input#value
// FLTK::Input#value=(value)
IMPLEMENT_STRING_ATTRIBUTE_ACCESSOR( input, value, Fl_Input, value );

void mrb_fltk_input_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  struct RClass *mrb_fltk_module = mrb_class_get( mrb, "FLTK" );
  struct RClass *mrb_fltk_widget_class = mrb_class_get_under( mrb, mrb_fltk_module, "Widget" );

  DEFINE_CLASS( input, Input, mrb_fltk_widget_class );

  DEFINE_INSTANCE_METHOD( input, initialize, ARGS_ANY() );
  DEFINE_INSTANCE_METHOD_ACCESSOR( input, value );

  ARENA_RESTORE;
}
