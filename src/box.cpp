#include <mruby.h>
#include <mruby/data.h>
#include <mruby/string.h>

#include <Fl/Fl_Box.h>

#include "macros.h"
#include "helpers.h"
#include "widget.h"
#include "box.h"

// FLTK::Box#initialize
mrb_value mrb_fltk_box_initialize_instance_method( mrb_state *mrb, mrb_value self ) {
  SETUP_DATA_TYPE( box );

  mrb_value *argv;
  int argc;
  Fl_Box *fl_box;

  mrb_get_args( mrb, "*", &argv, &argc );

  if( mrb_fltk_arg_check( "iiii", argc, argv ) ) { // x, y, width, height
    fl_box = new Fl_Box( (int)mrb_fixnum( argv[0] ), (int)mrb_fixnum( argv[1] ), (int)mrb_fixnum( argv[2] ), (int)mrb_fixnum( argv[3] ) );
  } else if( mrb_fltk_arg_check( "iiiis", argc, argv ) ) { // x, y, width, height, label
    fl_box = new Fl_Box( (int)mrb_fixnum( argv[0] ), (int)mrb_fixnum( argv[1] ), (int)mrb_fixnum( argv[2] ), (int)mrb_fixnum( argv[3] ), RSTRING_PTR( argv[4] ) );
    // } else if( mrb_fltk_arg_check( "*iiiis", argc, argv ) ) { // box_type, x, y, width, height, label
    //   // TODO: Get the first argument and make sure it's a FLTK::BoxType
    //   //       If it is, unwrap the Fl_Boxtype struct from within it
    //   fl_box = new Fl_Box( (int)mrb_fixnum( argv[0] ), (int)mrb_fixnum( argv[1] ), (int)mrb_fixnum( argv[2] ), (int)mrb_fixnum( argv[3] ), RSTRING_PTR( argv[4] ) );
  } else {
    mrb_raise( mrb, E_ARGUMENT_ERROR, "invalid argument" ); // TODO: Error should show valid arguments

    return mrb_nil_value(); // NOTE: Won't reach here but shut's up compiler warnings
  }

  SETUP_DATA_POINTER( fl_box );

  return self;
}

void mrb_fltk_box_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  struct RClass *mrb_fltk_module = mrb_module_get( mrb, "FLTK" );
  struct RClass *mrb_fltk_widget_class = mrb_class_get_under( mrb, mrb_fltk_module, "Widget" );

  DEFINE_CLASS( box, Box, mrb_fltk_widget_class );

  DEFINE_INSTANCE_METHOD( box, initialize, ARGS_ANY() );

  ARENA_RESTORE;
}
