#include <mruby.h>
#include <mruby/data.h>
#include <mruby/string.h>

#include <Fl/Fl_Browser.h>

#include "macros.h"
#include "helpers.h"
#include "group.h"
#include "browser.h"

// FLTK::Browser#initialize
mrb_value mrb_fltk_browser_initialize_instance_method( mrb_state *mrb, mrb_value self ) {
  SETUP_DATA_TYPE( browser );

  mrb_value *argv;
  int argc;
  Fl_Browser *fl_browser;

  mrb_get_args( mrb, "*", &argv, &argc );

  if( mrb_fltk_arg_check( "iiiis", argc, argv ) ) { // x, y, width, height, label
    fl_browser = new Fl_Browser( (int)mrb_fixnum( argv[0] ), (int)mrb_fixnum( argv[1] ), (int)mrb_fixnum( argv[2] ), (int)mrb_fixnum( argv[3] ), RSTRING_PTR( argv[4] ) );
  } else {
    mrb_raise( mrb, E_ARGUMENT_ERROR, "invalid argument" ); // TODO: Error should show valid arguments

    return mrb_nil_value(); // NOTE: Won't reach here but shut's up compiler warnings
  }

  SETUP_DATA_POINTER( fl_browser );

  return self;
}

// FLTK::Browser#add(text)
// FLTK::Browser#add(text, data)
// Adds a new line to the end of the browser with an optional data object.
mrb_value mrb_fltk_browser_add_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_browser, Fl_Browser, self );

  char *text;
  mrb_value data;
  mrb_get_args( mrb, "z|o", &text, &data );

  if( mrb_nil_p( data ) ) {
    fl_browser->add( text );
  } else {
    fl_browser->add( text, mrb_ptr( data ) );
  }

  return self;
}

// FLTK::Browser#clear()
// Clear the browser
mrb_value mrb_fltk_browser_clear_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_browser, Fl_Browser, self );

  fl_browser->clear();

  return self;
}

// TODO: Should be more ruby-ish?
// TODO: Needs to handle invalid index and null data
// FLTK::Browser#data(line)
// FLTK::Browser#data(line)
// Gets or sets the data object for the given line.
mrb_value mrb_fltk_browser_data_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_browser, Fl_Browser, self );

  mrb_int index;
  mrb_value data;
  mrb_get_args( mrb, "i|o", &index, &data );

  if( mrb_nil_p( data ) ) {
    fl_browser->data( index, mrb_ptr( data ) );

    return data;
  } else {
    return mrb_obj_value( fl_browser->data( index ) );
  }
}

// FLTK::Browser#text(index)
// Get text
mrb_value mrb_fltk_browser_text_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_browser, Fl_Browser, self );

  mrb_int index;
  mrb_get_args( mrb, "i", &index );

  return mrb_str_new_cstr( mrb, fl_browser->text( index ) );
}

// FLTK::Button#value
// FLTK::Button#value=(index)
// Gets the index of the currently selected item
IMPLEMENT_FIXNUM_ATTRIBUTE_ACCESSOR( browser, value, Fl_Browser, value );

void mrb_fltk_browser_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  struct RClass *mrb_fltk_module = mrb_class_get( mrb, "FLTK" );
  struct RClass *mrb_fltk_group_class = mrb_class_get_under( mrb, mrb_fltk_module, "Group" );

  DEFINE_CLASS( browser, Browser, mrb_fltk_group_class );

  DEFINE_INSTANCE_METHOD( browser, initialize, MRB_ARGS_ANY() );

  DEFINE_INSTANCE_METHOD( browser, add, MRB_ARGS_REQ( 1 ) );
  DEFINE_INSTANCE_METHOD( browser, clear, MRB_ARGS_NONE() );
  DEFINE_INSTANCE_METHOD( browser, data, MRB_ARGS_ARG( 1, 1 ) );
  DEFINE_INSTANCE_METHOD( browser, text, MRB_ARGS_REQ( 1 ) );
  DEFINE_INSTANCE_METHOD_ACCESSOR( browser, value );

  ARENA_RESTORE;
}
