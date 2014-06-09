#include <mruby.h>
#include <mruby/data.h>
#include <mruby/string.h>

#include <Fl/Fl_Button.h>

#include "macros.h"
#include "helpers.h"
#include "widget.h"
#include "button.h"

// FLTK::Window#initialize
mrb_value mrb_fltk_button_initialize_instance_method( mrb_state *mrb, mrb_value self ) {
  SETUP_DATA_TYPE( button );

  mrb_value *argv;
  int argc;
  Fl_Button *fl_button;

  mrb_get_args( mrb, "*", &argv, &argc );

  if( mrb_fltk_arg_check( "iiiis", argc, argv ) ) { // x, y, width, height, label
    fl_button = new Fl_Button( (int)mrb_fixnum( argv[0] ), (int)mrb_fixnum( argv[1] ), (int)mrb_fixnum( argv[2] ), (int)mrb_fixnum( argv[3] ), RSTRING_PTR( argv[4] ) );
  } else {
    mrb_raise( mrb, E_ARGUMENT_ERROR, "invalid argument" ); // TODO: Error should show valid arguments

    return mrb_nil_value(); // NOTE: Won't reach here but shut's up compiler warnings
  }

  SETUP_DATA_POINTER( fl_button );

  return self;
}

// FLTK::Button#shortcut
// FLTK::Button#shortcut=(value)
IMPLEMENT_FIXNUM_ATTRIBUTE_ACCESSOR( button, shortcut, Fl_Button, shortcut );

void mrb_fltk_button_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  struct RClass *mrb_fltk_module = mrb_class_get( mrb, "FLTK" );
  struct RClass *mrb_fltk_widget_class = mrb_class_get_under( mrb, mrb_fltk_module, "Widget" );

  DEFINE_CLASS( button, Button, mrb_fltk_widget_class );

  DEFINE_INSTANCE_METHOD( button, initialize, ARGS_ANY() );
  DEFINE_INSTANCE_METHOD_ACCESSOR( button, shortcut );

  ARENA_RESTORE;
}
