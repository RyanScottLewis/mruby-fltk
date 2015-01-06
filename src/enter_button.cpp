#include <mruby.h>
#include <mruby/data.h>
#include <mruby/string.h>

#include <Fl/Fl.h>
#include <Fl/Fl_Button.h>

#include "macros.h"
#include "helpers.h"
#include "widget.h"
#include "button.h"
#include "enter_button.h"

// A FLTK Button subclass that runs it's callback when the enter key is pressed.
// TODO: cannot focus correctly when callback is run by pressing Enter, but works fine when clicked.
class Fl_Enter_Button : public Fl_Button {
public:
  Fl_Enter_Button( int x, int y, int w, int h, const char *n )
  : Fl_Button( x, y, w, h, n ) {
  }

  int handle( int event ) {
    if( event == FL_KEYDOWN && Fl::event_key() == FL_Enter ) {
      do_callback();

      return 0;
    }

    return Fl_Button::handle( event );
  }
};

// FLTK::EnterButton#initialize
mrb_value mrb_fltk_enter_button_initialize_instance_method( mrb_state *mrb, mrb_value self ) {
  SETUP_DATA_TYPE( enter_button );

  mrb_value *argv;
  int argc;
  Fl_Enter_Button *fl_enter_button;

  mrb_get_args( mrb, "*", &argv, &argc );

  if( mrb_fltk_arg_check( "iiiis", argc, argv ) ) { // x, y, width, height, label
    fl_enter_button = new Fl_Enter_Button( (int)mrb_fixnum( argv[0] ), (int)mrb_fixnum( argv[1] ), (int)mrb_fixnum( argv[2] ), (int)mrb_fixnum( argv[3] ), RSTRING_PTR( argv[4] ) );
  } else {
    mrb_raise( mrb, E_ARGUMENT_ERROR, "invalid argument" ); // TODO: Error should show valid arguments

    return mrb_nil_value(); // NOTE: Won't reach here but shut's up compiler warnings
  }

  SETUP_DATA_POINTER( fl_enter_button );

  return self;
}

void mrb_fltk_enter_button_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  struct RClass *mrb_fltk_module = mrb_module_get( mrb, "FLTK" );
  struct RClass *mrb_fltk_button_class = mrb_class_get_under( mrb, mrb_fltk_module, "Button" );

  DEFINE_CLASS( enter_button, EnterButton, mrb_fltk_button_class );

  DEFINE_INSTANCE_METHOD( enter_button, initialize, ARGS_ANY() );

  ARENA_RESTORE;
}
