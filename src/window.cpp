#include <mruby.h>
#include <mruby/data.h>
#include <mruby/string.h>

#include <Fl/Fl_Window.h>

#include "macros.h"
#include "helpers.h"
#include "group.h"
#include "window.h"

// FLTK::Window#initialize
mrb_value mrb_fltk_window_initialize_instance_method( mrb_state *mrb, mrb_value self ) {
  SETUP_DATA_TYPE( window );

  mrb_value *argv;
  int argc;
  Fl_Window *fl_window;

  mrb_get_args( mrb, "*", &argv, &argc );

  if( mrb_fltk_arg_check( "iis", argc, argv ) ) { // width, height, title
    fl_window = new Fl_Window( (int)mrb_fixnum( argv[0] ), (int)mrb_fixnum( argv[1] ), RSTRING_PTR( argv[2] ) );
  } else if( mrb_fltk_arg_check( "iiiis", argc, argv ) ) { // x, y, width, height, title
    fl_window = new Fl_Window( (int)mrb_fixnum( argv[0] ), (int)mrb_fixnum( argv[1] ), (int)mrb_fixnum( argv[2] ), (int)mrb_fixnum( argv[3] ), RSTRING_PTR( argv[4] ) );
  } else {
    mrb_raise( mrb, E_ARGUMENT_ERROR, "invalid argument" ); // TODO: Error should show valid arguments

    return mrb_nil_value(); // NOTE: Won't reach here but shut's up compiler warnings
  }

  SETUP_DATA_POINTER( fl_window );

  return self;
}

// FLTK::Window#show
// TODO: Should return true if it worked, false if it didnt
mrb_value mrb_fltk_window_show_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_window, Fl_Window );

  fl_window->show();

  return self;
}

void mrb_fltk_window_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  struct RClass *mrb_fltk_module = mrb_class_get( mrb, "FLTK" );
  struct RClass *mrb_fltk_group_class = mrb_class_get_under( mrb, mrb_fltk_module, "Group" );

  DEFINE_CLASS( window, Window, mrb_fltk_group_class );

  DEFINE_INSTANCE_METHOD( window, initialize, ARGS_ANY() );
  DEFINE_INSTANCE_METHOD( window, show, ARGS_OPT( 1 ) );

  ARENA_RESTORE;
}
