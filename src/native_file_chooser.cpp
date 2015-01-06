#include <mruby.h>
#include <mruby/data.h>
#include <mruby/string.h>

#include <Fl/Fl_Native_File_Chooser.h>

#include "macros.h"
#include "helpers.h"
#include "native_file_chooser.h"

// FLTK::NativeFileChooser#initialize(type=FLTK::NativeFileChooser::BROWSE_FILE)
mrb_value mrb_fltk_native_file_chooser_initialize_instance_method( mrb_state *mrb, mrb_value self ) {
  SETUP_DATA_TYPE( native_file_chooser );

  Fl_Native_File_Chooser *fl_native_file_chooser;

  mrb_value mrb_type;
  mrb_get_args( mrb, "|i", &mrb_type );

  if( mrb_nil_p( mrb_type ) ) {
    fl_native_file_chooser = new Fl_Native_File_Chooser();
  } else {
    fl_native_file_chooser = new Fl_Native_File_Chooser( mrb_fixnum( mrb_type ) );
  }

  SETUP_DATA_POINTER( fl_native_file_chooser );

  return self;
}

// FLTK::NativeFileChooser#count
// Returns the number of filenames (or directory names) the user selected.
IMPLEMENT_FIXNUM_ATTRIBUTE_READER( native_file_chooser, count, Fl_Native_File_Chooser, count );

// FLTK::NativeFileChooser#directory
// Returns the current preset directory value.
// FLTK::NativeFileChooser#directory=(value)
// Preset the directory the browser will show when opened.
IMPLEMENT_STRING_ATTRIBUTE_ACCESSOR( native_file_chooser, directory, Fl_Native_File_Chooser, directory );

// FLTK::NativeFileChooser#error_message
// Returns a system dependent error message for the last method that failed.
IMPLEMENT_STRING_ATTRIBUTE_READER( native_file_chooser, error_message, Fl_Native_File_Chooser, errmsg );

// FLTK::NativeFileChooser#filename(index=nil)
// Return the filename the user choose. If index is given, return one of the filenames the user selected.
mrb_value mrb_fltk_native_file_chooser_filename_instance_method( mrb_state *mrb, mrb_value self ) {
  // TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
  // Segfaults! Wowza
  // TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO TODO
  GET_DATA( fl_native_file_chooser, Fl_Native_File_Chooser, self );

  mrb_value mrb_index;
  mrb_get_args( mrb, "|i", &mrb_index );

  mrb_value mrb_filename;

  if( mrb_nil_p( mrb_index ) ) {
    mrb_filename = mrb_str_new_cstr( mrb, fl_native_file_chooser->filename() );
  } else {
    mrb_filename = mrb_str_new_cstr( mrb, fl_native_file_chooser->filename( mrb_fixnum( mrb_index ) ) );
  }
  printf( "-==--==--==-=-=-=-=-=-=-=-=--=-=-=----------\n" );
  mrb_p( mrb, mrb_filename );
  printf( "-==--==--==-=-=-=-=-=-=-=-=--=-=-=----------\n" );
  return mrb_filename;
}
// FLTK::NativeFileChooser#filter
// Returns the filter string last set.
// FLTK::NativeFileChooser#filter=(value)
// Sets the filename filters used for browsing.
IMPLEMENT_STRING_ATTRIBUTE_ACCESSOR( native_file_chooser, filter, Fl_Native_File_Chooser, filter );

// FLTK::NativeFileChooser#filter_value
// Returns which filter value was last selected by the user.
// FLTK::NativeFileChooser#filter_value=(value)
// Sets which filter will be initially selected.
IMPLEMENT_FIXNUM_ATTRIBUTE_ACCESSOR( native_file_chooser, filter_value, Fl_Native_File_Chooser, filter_value );

// FLTK::NativeFileChooser#filters
// Gets how many filters were available, not including "All Files".
IMPLEMENT_FIXNUM_ATTRIBUTE_READER( native_file_chooser, filters, Fl_Native_File_Chooser, filters );

// FLTK::NativeFileChooser#options
// Gets the platform specific option flags.
// FLTK::NativeFileChooser#options=(value)
// Sets the platform specific chooser options. (NO_OPTIONS, SAVEAS_CONFIRM, NEW_FOLDER, or PREVIEW)
IMPLEMENT_FIXNUM_ATTRIBUTE_ACCESSOR( native_file_chooser, options, Fl_Native_File_Chooser, options );

// FLTK::NativeFileChooser#preset_file
// Get the preset filename.
// FLTK::NativeFileChooser#preset_file=(value)
// Sets the default filename for the chooser.
IMPLEMENT_STRING_ATTRIBUTE_ACCESSOR( native_file_chooser, preset_file, Fl_Native_File_Chooser, preset_file );

// FLTK::NativeFileChooser#show
// Post the chooser's dialog.
IMPLEMENT_FIXNUM_ATTRIBUTE_READER( native_file_chooser, show, Fl_Native_File_Chooser, show );

// FLTK::NativeFileChooser#title
// Get the title of the file chooser's dialog window.
// FLTK::NativeFileChooser#title=(value)
// Set the title of the file chooser's dialog window.
IMPLEMENT_STRING_ATTRIBUTE_ACCESSOR( native_file_chooser, title, Fl_Native_File_Chooser, title );

// FLTK::NativeFileChooser#type
// Gets the current type of browser.
// FLTK::NativeFileChooser#type=(value)
// Sets the current type of browser. (BROWSE_FILE, BROWSE_DIRECTORY, BROWSE_MULTI_FILE, BROWSE_MULTI_DIRECTORY, BROWSE_SAVE_FILE, BROWSE_SAVE_DIRECTORY)
IMPLEMENT_FIXNUM_ATTRIBUTE_ACCESSOR( native_file_chooser, type, Fl_Native_File_Chooser, type );

void mrb_fltk_native_file_chooser_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  struct RClass *mrb_fltk_module = mrb_module_get( mrb, "FLTK" );

  DEFINE_CLASS( native_file_chooser, NativeFileChooser, mrb->object_class );

  // enum Fl_Native_File_Chooser::Option
  DEFINE_FIXNUM_CONSTANT( NO_OPTIONS, Fl_Native_File_Chooser::NO_OPTIONS, mrb_fltk_native_file_chooser );         // no options enabled
  DEFINE_FIXNUM_CONSTANT( SAVEAS_CONFIRM, Fl_Native_File_Chooser::SAVEAS_CONFIRM, mrb_fltk_native_file_chooser ); // Show native 'Save As' overwrite confirm dialog (if supported)
  DEFINE_FIXNUM_CONSTANT( NEW_FOLDER, Fl_Native_File_Chooser::NEW_FOLDER, mrb_fltk_native_file_chooser );         // Show 'New Folder' icon (if supported)
  DEFINE_FIXNUM_CONSTANT( PREVIEW, Fl_Native_File_Chooser::PREVIEW, mrb_fltk_native_file_chooser );               // enable preview mode

  // enum Fl_Native_File_Chooser::Type
  DEFINE_FIXNUM_CONSTANT( BROWSE_FILE, Fl_Native_File_Chooser::BROWSE_FILE, mrb_fltk_native_file_chooser );                       // browse files (lets user choose one file)
  DEFINE_FIXNUM_CONSTANT( BROWSE_DIRECTORY, Fl_Native_File_Chooser::BROWSE_DIRECTORY, mrb_fltk_native_file_chooser );             // browse directories (lets user choose one directory)
  DEFINE_FIXNUM_CONSTANT( BROWSE_MULTI_FILE, Fl_Native_File_Chooser::BROWSE_MULTI_FILE, mrb_fltk_native_file_chooser );           // browse files (lets user choose multiple files)
  DEFINE_FIXNUM_CONSTANT( BROWSE_MULTI_DIRECTORY, Fl_Native_File_Chooser::BROWSE_MULTI_DIRECTORY, mrb_fltk_native_file_chooser ); // browse directories (lets user choose multiple directories)
  DEFINE_FIXNUM_CONSTANT( BROWSE_SAVE_FILE, Fl_Native_File_Chooser::BROWSE_SAVE_FILE, mrb_fltk_native_file_chooser );             // browse to save a file
  DEFINE_FIXNUM_CONSTANT( BROWSE_SAVE_DIRECTORY, Fl_Native_File_Chooser::BROWSE_SAVE_DIRECTORY, mrb_fltk_native_file_chooser );   // browse to save a directory

  DEFINE_INSTANCE_METHOD( native_file_chooser, initialize, MRB_ARGS_OPT( 1 ) );
  DEFINE_INSTANCE_METHOD_GETTER( native_file_chooser, count );
  DEFINE_INSTANCE_METHOD_ACCESSOR( native_file_chooser, directory );
  DEFINE_INSTANCE_METHOD_GETTER( native_file_chooser, error_message );
  DEFINE_INSTANCE_METHOD( native_file_chooser, filename, MRB_ARGS_OPT( 1 ) );
  DEFINE_INSTANCE_METHOD_ACCESSOR( native_file_chooser, filter );
  DEFINE_INSTANCE_METHOD_ACCESSOR( native_file_chooser, filter_value );
  DEFINE_INSTANCE_METHOD_GETTER( native_file_chooser, filters );
  DEFINE_INSTANCE_METHOD_ACCESSOR( native_file_chooser, options );
  DEFINE_INSTANCE_METHOD_ACCESSOR( native_file_chooser, preset_file );
  DEFINE_INSTANCE_METHOD_GETTER( native_file_chooser, show );
  DEFINE_INSTANCE_METHOD_ACCESSOR( native_file_chooser, title );
  DEFINE_INSTANCE_METHOD_ACCESSOR( native_file_chooser, type );

  ARENA_RESTORE;
}
