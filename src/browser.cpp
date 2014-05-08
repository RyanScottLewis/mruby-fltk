#include <mruby.h>
#include <mruby/variable.h>

#include "mrb_fltk.h"
#include "widget.h"

// =-=- FLTK::Browser -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=

DECLARE_WIDGET( browser, Fl_Browser );

// FLTK::Browser#add(line) Adds a new line to the end of the browser.
static mrb_value
mrb_fltk_browser_add_method(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP( widget );
  
  mrb_value text = mrb_nil_value();
  mrb_get_args(mrb, "S", &text);
  
  ( (Fl_Browser *) context->fl_instance )->add( RSTRING_PTR(text) );
  
  return mrb_nil_value();
}


// FLTK::Browser#column_widths Gets the current column width array.
static mrb_value
mrb_fltk_browser_column_widths_get_method(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP( widget );
  
  const int* widths = ( (Fl_Browser *) context->fl_instance )->column_widths();
  int index = 0;
  
  ARENA_SAVE;
  mrb_value results = mrb_ary_new(mrb);
  
  while ( widths[index] ) {
    mrb_ary_push( mrb, results, mrb_fixnum_value( widths[index] ) );
    ARENA_RESTORE;
    index++;
  }
  
  return results;
}

// FLTK::Browser#column_widths=(widths) Sets the current array.
static mrb_value
mrb_fltk_browser_column_widths_set_method(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP( widget );
  
  static int *widths;
  
  if ( widths ) free( (void *) widths );
  
  widths = (int *) ( (Fl_Browser *) context->fl_instance )->column_widths();
  
  mrb_value results = mrb_nil_value();
  mrb_get_args(mrb, "A", &results);
  
  int index = 0, length = RARRAY_LEN(results);
  
  widths = (int *) malloc( sizeof(int) * (length+1) );
  for (index = 0; index < length; index++) {
    widths[index] = mrb_fixnum( mrb_funcall( mrb, RARRAY_PTR(results)[index], "to_i", 0, NULL ) );
  }
  widths[index] = 0;
  
  ( (Fl_Browser *) context->fl_instance )->column_widths(widths);
  
  return mrb_nil_value();
}

// FLTK::Browser#icon(line) Returns the icon currently defined for line. 
// FLTK::Browser#icon(line, icon=nil) Set the image icon for line to the value icon. 
static mrb_value
mrb_fltk_browser_icon_method(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP( widget );
  
  mrb_value line = mrb_nil_value(), icon = mrb_nil_value();
  mrb_get_args(mrb, "i|o", &line, &icon);
  
  if ( mrb_nil_p(icon) ) {
    // if ( mrb_nil_p(line) )
      // TODO: Raise Error
    
    Fl_Image *icon = ( (Fl_Browser *) context->fl_instance )->icon( mrb_fixnum(line) );
    
    if ( !icon ) return mrb_nil_value();
    
    CONTEXT_CREATE( icon, icon_context );
    icon_context->fl_instance = icon;
    
    mrb_value args[1];
    
    struct RClass* mrb_fltk_class = mrb_class_get(mrb, "FLTK");
    struct RClass* mrb_fltk_image_class = mrb_class_ptr( mrb_const_get( mrb, mrb_obj_value(mrb_fltk_class), mrb_intern_cstr(mrb, "Image") ) );
    
    args[0] = CONTEXT_WRAP( icon, icon_context );
    
    return mrb_class_new_instance(mrb, 1, args, mrb_fltk_image_class);
  } // TODO: else: the SETTER
  
  return mrb_nil_value();
}

// FLTK::Browser#load(filename) Clears the browser and reads the file, adding each line from the file to the browser. 
static mrb_value
mrb_fltk_browser_load_method(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP( widget );
  
  mrb_value filename;
  mrb_get_args(mrb, "S", &filename);
  
  return mrb_fixnum_value( ( (Fl_Browser *) context->fl_instance )->load( RSTRING_PTR(filename) ) );
}

// FLTK::Browser#text(line) Returns the label text for the specified line. 
// FLTK::Browser#text(line, text) Sets the text for the specified line. 
static mrb_value
mrb_fltk_browser_text_method(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP( widget );
  
  mrb_value line = mrb_nil_value(), text = mrb_nil_value();
  mrb_get_args( mrb, "i|S", &line, &text );
  
  if ( mrb_nil_p(text) ) {
    const char* text;
    
    if ( mrb_nil_p(line) ) {
      int value = ( (Fl_Browser *) context->fl_instance )->value();
      
      text = ( (Fl_Browser *) context->fl_instance )->text(value);
    } else {
      text = ( (Fl_Browser *) context->fl_instance )->text( mrb_fixnum(line) );
    }
    
    if ( !text ) return mrb_nil_value();
    
    return mrb_str_new_cstr(mrb, text);
  }
  
  ( (Fl_Browser *) context->fl_instance )->text( mrb_fixnum(line), RSTRING_PTR(text) );
  
  return mrb_nil_value(); // TODO: Return text
}

// =-=- FLTK::SelectBrowser -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=

DECLARE_WIDGET( select_browser, Fl_Select_Browser );