#include <mruby.h>
#include <mruby/data.h>
#include <mruby/string.h>
#include <mruby/array.h>

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

// FLTK::Browser#column_char()
// Gets the current column separator character.
mrb_value mrb_fltk_browser_column_char_getter_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_browser, Fl_Browser, self );

  char fl_column_char = fl_browser->column_char();

  if( fl_column_char ) {
    char column_char[1] = { fl_column_char };

    return mrb_str_new_cstr( mrb, column_char ); // FIXME: This gives strange output. Got "\t0\703qZ\777\177", should be "\t"
  } else {
    return mrb_nil_value();
  }
}

// FLTK::Browser#column_char=(value)
// Sets the current column separator character.
mrb_value mrb_fltk_browser_column_char_setter_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_browser, Fl_Browser, self );

  mrb_value value;
  mrb_get_args( mrb, "S", &value );
  value = mrb_str_resize( mrb, value, 1 );

  fl_browser->column_char( mrb_str_to_cstr( mrb, value )[0] );

  return self; // TODO: Real value
}

// FLTK::Browser#column_widths()
// Gets the current column width array.
mrb_value mrb_fltk_browser_column_widths_getter_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_browser, Fl_Browser, self );

  const int *fl_column_widths = fl_browser->column_widths();
  int fl_column_widths_length = sizeof( fl_column_widths ) / sizeof( int );
  mrb_value mrb_column_widths = mrb_ary_new( mrb );

  for( size_t i = 0; i < fl_column_widths_length; ++i )
    mrb_ary_push( mrb, mrb_column_widths, mrb_fixnum_value( fl_column_widths[i] ) );

  return mrb_column_widths;
}

// FLTK::Browser#column_widths=(values)
// Sets the current column width array.
mrb_value mrb_fltk_browser_column_widths_setter_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_browser, Fl_Browser, self );

  mrb_value value;
  mrb_get_args( mrb, "A", &value );

  // TODO: convert all values to Ints using collect(&:to_i)

  mrb_int value_length = mrb_ary_len( mrb, value );
  mrb_int column_widths[value_length];

  for( size_t i = 0; i < value_length; ++i )
    column_widths[i] = mrb_fixnum( mrb_ary_entry( value, i ) );

  fl_browser->column_widths( column_widths );

  return self; // TODO: Real value
}

// TODO: Should be more ruby-ish?
// TODO: Needs to handle invalid index and null data! FIXME SEGFAULT when index is out of range
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
    void *data = fl_browser->data( index );

    return data ? mrb_obj_value( data ) : mrb_nil_value();
  }
}

// FLTK::Browser#size()
// Get how many lines in the browser.
mrb_value mrb_fltk_browser_size_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_browser, Fl_Browser, self );

  return mrb_fixnum_value( fl_browser->size() );
}

// FLTK::Browser#text(index)
// Get text of line at index.
mrb_value mrb_fltk_browser_text_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_browser, Fl_Browser, self );

  mrb_int index;
  mrb_get_args( mrb, "i", &index );

  return mrb_str_new_cstr( mrb, fl_browser->text( index ) );
}

// FLTK::Browser#remove(index)
// Remove the line at index.
mrb_value mrb_fltk_browser_remove_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_browser, Fl_Browser, self );

  mrb_int index;
  mrb_get_args( mrb, "i", &index );

  fl_browser->remove( index );

  return self; // TODO: Should return the value at index?
}

// FLTK::Button#value
// FLTK::Button#value=(index)
// Gets the index of the currently selected item
IMPLEMENT_FIXNUM_ATTRIBUTE_ACCESSOR( browser, value, Fl_Browser, value );

void mrb_fltk_browser_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  struct RClass *mrb_fltk_module = mrb_module_get( mrb, "FLTK" );
  struct RClass *mrb_fltk_group_class = mrb_class_get_under( mrb, mrb_fltk_module, "Group" );

  DEFINE_CLASS( browser, Browser, mrb_fltk_group_class );

  DEFINE_INSTANCE_METHOD( browser, initialize, MRB_ARGS_ANY() );

  DEFINE_INSTANCE_METHOD( browser, add, MRB_ARGS_REQ( 1 ) );
  DEFINE_INSTANCE_METHOD( browser, clear, MRB_ARGS_NONE() );
  DEFINE_INSTANCE_METHOD_ACCESSOR( browser, column_char );
  DEFINE_INSTANCE_METHOD_ACCESSOR( browser, column_widths );
  DEFINE_INSTANCE_METHOD( browser, data, MRB_ARGS_ARG( 1, 1 ) );
  DEFINE_INSTANCE_METHOD( browser, remove, MRB_ARGS_REQ( 1 ) );
  DEFINE_INSTANCE_METHOD( browser, size, MRB_ARGS_NONE() );
  DEFINE_INSTANCE_METHOD( browser, text, MRB_ARGS_REQ( 1 ) );
  DEFINE_INSTANCE_METHOD_ACCESSOR( browser, value );

  ARENA_RESTORE;
}
