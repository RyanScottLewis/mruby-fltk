#include <mruby.h>
#include <mruby/data.h>
#include <mruby/hash.h>
#include <mruby/string.h>

#include <Fl/Fl.h>
#include <Fl/Fl_draw.h>

#include "macros.h"
#include "helpers.h"

// FLTK.event_key(key=nil)
// Gets which key on the keyboard was last pushed.
// If a key is given, returns true if the given key was held down (or pressed) during the last event.
mrb_value mrb_fltk_event_key_module_method( mrb_state *mrb, mrb_value self ) {
  mrb_value key;
  mrb_get_args( mrb, "i", &key );

  if( mrb_nil_p( key ) ) {
    return mrb_fixnum_value( Fl::event_key() );
  } else {
    if( Fl::event_key( mrb_fixnum( key ) ) ) {
      return mrb_true_value();
    } else {
      return mrb_false_value();
    }
  }
}

// FLTK.focus
// Gets the current focused widget.
mrb_value mrb_fltk_focus_getter_module_method( mrb_state *mrb, mrb_value self ) {
  // TODO: I dunno how to go about this.
  //  Find the MRB instance wrapping the pointer
  //    Problem is that this seems impossible
  // OR
  //  Get the MRB class based on the pointer, set the DATA_PTR, and initialize it
  //    Problem is this works unless you want to retrieve a MRB subclass of that object. For example, I have a `class Sidebar < FLTK::HoldBrowser`.
}

// FLTK.focus=(widget)
// Sets the current focused widget.
mrb_value mrb_fltk_focus_setter_module_method( mrb_state *mrb, mrb_value self ) {
  mrb_value mrb_widget;
  mrb_get_args( mrb, "o", &mrb_widget );
  // TODO: Raise error unless it is a FLTK::Widget

  GET_DATA( fl_widget, Fl_Widget, mrb_widget );

  Fl::focus( fl_widget );

  return mrb_widget;
}

// FLTK.font
// FLTK.font(font_face, font_size)
// Gets or sets the current font, which is then used in various drawing routines.
mrb_value mrb_fltk_font_module_method( mrb_state *mrb, mrb_value self ) {
  mrb_value mrb_face, mrb_size;
  mrb_get_args( mrb, "|ii", &mrb_face, &mrb_size );

  if( mrb_nil_p( mrb_face ) || mrb_nil_p( mrb_size ) ) {
    fl_font( mrb_fixnum( mrb_face ), mrb_fixnum( mrb_size ) );

    return self;
  } else {
    return mrb_fixnum_value( fl_font() );
  }
}

// FLTK.measure(text)
// Get the width and height of a string, according to the last call to FLTK.font.
mrb_value mrb_fltk_measure_module_method( mrb_state *mrb, mrb_value self ) {
  int width = 0;
  int height = 0;
  char *text;
  mrb_get_args( mrb, "z", &text );

  fl_measure( text, width, height );

  mrb_value result = mrb_hash_new( mrb );
  mrb_hash_set( mrb, result, mrb_symbol_value( mrb_intern_cstr( mrb, "width" ) ), mrb_fixnum_value( width ) );
  mrb_hash_set( mrb, result, mrb_symbol_value( mrb_intern_cstr( mrb, "height" ) ), mrb_fixnum_value( height ) );

  return result;
}

// FLTK.run
mrb_value mrb_fltk_run_module_method( mrb_state *mrb, mrb_value self ) {
  return mrb_fixnum_value( Fl::run() );
}

// FLTK.width(text)
// Get the width of a string.
mrb_value mrb_fltk_width_module_method( mrb_state *mrb, mrb_value self ) {
  char *text;
  mrb_get_args( mrb, "z", &text );

  return mrb_fixnum_value( fl_width( text ) );
}

void mrb_fltk_module_init( mrb_state *mrb ) {
  ARENA_SAVE;

  struct RClass *mrb_fltk_module = mrb_define_module( mrb, "FLTK" );

  // Fl_Align
  DEFINE_FIXNUM_CONSTANT( ALIGN_CENTER, FL_ALIGN_CENTER, mrb_fltk_module );                         // Align the label horizontally in the middle.
  DEFINE_FIXNUM_CONSTANT( ALIGN_TOP, FL_ALIGN_TOP, mrb_fltk_module );                               // Align the label at the top of the widget. Inside labels appear below the top, outside labels are drawn on top of the widget.
  DEFINE_FIXNUM_CONSTANT( ALIGN_BOTTOM, FL_ALIGN_BOTTOM, mrb_fltk_module );                         // Align the label at the bottom of the widget.
  DEFINE_FIXNUM_CONSTANT( ALIGN_LEFT, FL_ALIGN_LEFT, mrb_fltk_module );                             // Align the label at the left of the widget. Inside labels appear left-justified starting at the left side of the widget, outside labels are right-justified and drawn to the left of the widget.
  DEFINE_FIXNUM_CONSTANT( ALIGN_RIGHT, FL_ALIGN_RIGHT, mrb_fltk_module );                           // Align the label to the right of the widget.
  DEFINE_FIXNUM_CONSTANT( ALIGN_INSIDE, FL_ALIGN_INSIDE, mrb_fltk_module );                         // Draw the label inside of the widget.
  DEFINE_FIXNUM_CONSTANT( ALIGN_TEXT_OVER_IMAGE, FL_ALIGN_TEXT_OVER_IMAGE, mrb_fltk_module );       // If the label contains an image, draw the text on top of the image.
  DEFINE_FIXNUM_CONSTANT( ALIGN_IMAGE_OVER_TEXT, FL_ALIGN_IMAGE_OVER_TEXT, mrb_fltk_module );       // If the label contains an image, draw the text below the image.
  DEFINE_FIXNUM_CONSTANT( ALIGN_CLIP, FL_ALIGN_CLIP, mrb_fltk_module );                             // All parts of the label that are lager than the widget will not be drawn .
  DEFINE_FIXNUM_CONSTANT( ALIGN_WRAP, FL_ALIGN_WRAP, mrb_fltk_module );                             // Wrap text that does not fit the width of the widget.
  DEFINE_FIXNUM_CONSTANT( ALIGN_IMAGE_NEXT_TO_TEXT, FL_ALIGN_IMAGE_NEXT_TO_TEXT, mrb_fltk_module ); // If the label contains an image, draw the text to the right of the image.
  DEFINE_FIXNUM_CONSTANT( ALIGN_TEXT_NEXT_TO_IMAGE, FL_ALIGN_TEXT_NEXT_TO_IMAGE, mrb_fltk_module ); // If the label contains an image, draw the text to the left of the image.
  DEFINE_FIXNUM_CONSTANT( ALIGN_IMAGE_BACKDROP, FL_ALIGN_IMAGE_BACKDROP, mrb_fltk_module );         // If the label contains an image, draw the image or deimage in the background.
  DEFINE_FIXNUM_CONSTANT( ALIGN_TOP_LEFT, FL_ALIGN_TOP_LEFT, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( ALIGN_TOP_RIGHT, FL_ALIGN_TOP_RIGHT, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( ALIGN_BOTTOM_LEFT, FL_ALIGN_BOTTOM_LEFT, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( ALIGN_BOTTOM_RIGHT, FL_ALIGN_BOTTOM_RIGHT, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( ALIGN_LEFT_TOP, FL_ALIGN_LEFT_TOP, mrb_fltk_module );           // magic value
  DEFINE_FIXNUM_CONSTANT( ALIGN_RIGHT_TOP, FL_ALIGN_RIGHT_TOP, mrb_fltk_module );         // magic value
  DEFINE_FIXNUM_CONSTANT( ALIGN_LEFT_BOTTOM, FL_ALIGN_LEFT_BOTTOM, mrb_fltk_module );     // magic value
  DEFINE_FIXNUM_CONSTANT( ALIGN_RIGHT_BOTTOM, FL_ALIGN_RIGHT_BOTTOM, mrb_fltk_module );   // magic value
  DEFINE_FIXNUM_CONSTANT( ALIGN_NOWRAP, FL_ALIGN_NOWRAP, mrb_fltk_module );               // for back compatibility
  DEFINE_FIXNUM_CONSTANT( ALIGN_POSITION_MASK, FL_ALIGN_POSITION_MASK, mrb_fltk_module ); // left, right, top, bottom
  DEFINE_FIXNUM_CONSTANT( ALIGN_IMAGE_MASK, FL_ALIGN_IMAGE_MASK, mrb_fltk_module );       // l/r, t/b, backdrop

  // Fl_Font
  DEFINE_FIXNUM_CONSTANT( HELVETICA, FL_HELVETICA, mrb_fltk_module );                         // Helvetica (or Arial) normal (0)
  DEFINE_FIXNUM_CONSTANT( HELVETICA_BOLD, FL_HELVETICA_BOLD, mrb_fltk_module );               // Helvetica (or Arial) bold
  DEFINE_FIXNUM_CONSTANT( HELVETICA_ITALIC, FL_HELVETICA_ITALIC, mrb_fltk_module );           // Helvetica (or Arial) oblique
  DEFINE_FIXNUM_CONSTANT( HELVETICA_BOLD_ITALIC, FL_HELVETICA_BOLD_ITALIC, mrb_fltk_module ); // Helvetica (or Arial) bold-oblique
  DEFINE_FIXNUM_CONSTANT( COURIER, FL_COURIER, mrb_fltk_module );                             // Courier normal
  DEFINE_FIXNUM_CONSTANT( COURIER_BOLD, FL_COURIER_BOLD, mrb_fltk_module );                   // Courier bold
  DEFINE_FIXNUM_CONSTANT( COURIER_ITALIC, FL_COURIER_ITALIC, mrb_fltk_module );               // Courier italic
  DEFINE_FIXNUM_CONSTANT( COURIER_BOLD_ITALIC, FL_COURIER_BOLD_ITALIC, mrb_fltk_module );     // Courier bold-italic
  DEFINE_FIXNUM_CONSTANT( TIMES, FL_TIMES, mrb_fltk_module );                                 // Times roman
  DEFINE_FIXNUM_CONSTANT( TIMES_BOLD, FL_TIMES_BOLD, mrb_fltk_module );                       // Times roman bold
  DEFINE_FIXNUM_CONSTANT( TIMES_ITALIC, FL_TIMES_ITALIC, mrb_fltk_module );                   // Times roman italic
  DEFINE_FIXNUM_CONSTANT( TIMES_BOLD_ITALIC, FL_TIMES_BOLD_ITALIC, mrb_fltk_module );         // Times roman bold-italic
  DEFINE_FIXNUM_CONSTANT( SYMBOL, FL_SYMBOL, mrb_fltk_module );                               // Standard symbol font
  DEFINE_FIXNUM_CONSTANT( SCREEN, FL_SCREEN, mrb_fltk_module );                               // Default monospaced screen font
  DEFINE_FIXNUM_CONSTANT( SCREEN_BOLD, FL_SCREEN_BOLD, mrb_fltk_module );                     // Default monospaced bold screen font
  DEFINE_FIXNUM_CONSTANT( ZAPF_DINGBATS, FL_ZAPF_DINGBATS, mrb_fltk_module );                 // Zapf-dingbats font
  DEFINE_FIXNUM_CONSTANT( FREE_FONT, FL_FREE_FONT, mrb_fltk_module );                         // first one to allocate
  DEFINE_FIXNUM_CONSTANT( BOLD, FL_BOLD, mrb_fltk_module );                                   // add this to helvetica, courier, or times
  DEFINE_FIXNUM_CONSTANT( ITALIC, FL_ITALIC, mrb_fltk_module );                               // add this to helvetica, courier, or times
  DEFINE_FIXNUM_CONSTANT( BOLD_ITALIC, FL_BOLD_ITALIC, mrb_fltk_module );                     // add this to helvetica, courier, or times

  // Fl_When
  DEFINE_FIXNUM_CONSTANT( WHEN_NEVER, FL_WHEN_NEVER, mrb_fltk_module );                         // Never call the callback.
  DEFINE_FIXNUM_CONSTANT( WHEN_CHANGED, FL_WHEN_CHANGED, mrb_fltk_module );                     // Do the callback only when the widget value changes.
  DEFINE_FIXNUM_CONSTANT( WHEN_NOT_CHANGED, FL_WHEN_NOT_CHANGED, mrb_fltk_module );             // Do the callback whenever the user interacts with the widget.
  DEFINE_FIXNUM_CONSTANT( WHEN_RELEASE, FL_WHEN_RELEASE, mrb_fltk_module );                     // Do the callback when the button or key is released and the value changes.
  DEFINE_FIXNUM_CONSTANT( WHEN_RELEASE_ALWAYS, FL_WHEN_RELEASE_ALWAYS, mrb_fltk_module );       // Do the callback when the button or key is released, even if the value doesn't change.
  DEFINE_FIXNUM_CONSTANT( WHEN_ENTER_KEY, FL_WHEN_ENTER_KEY, mrb_fltk_module );                 // Do the callback when the user presses the ENTER key and the value changes.
  DEFINE_FIXNUM_CONSTANT( WHEN_ENTER_KEY_ALWAYS, FL_WHEN_ENTER_KEY_ALWAYS, mrb_fltk_module );   // Do the callback when the user presses the ENTER key, even if the value doesn't change.
  DEFINE_FIXNUM_CONSTANT( WHEN_ENTER_KEY_CHANGED, FL_WHEN_ENTER_KEY_CHANGED, mrb_fltk_module ); // ?

  // Fl_Event
  DEFINE_FIXNUM_CONSTANT( NO_EVENT, FL_NO_EVENT, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( PUSH, FL_PUSH, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( RELEASE, FL_RELEASE, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( ENTER, FL_ENTER, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( LEAVE, FL_LEAVE, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( DRAG, FL_DRAG, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( FOCUS, FL_FOCUS, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( UNFOCUS, FL_UNFOCUS, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( KEYDOWN, FL_KEYDOWN, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( KEYBOARD, FL_KEYBOARD, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( KEYUP, FL_KEYUP, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( CLOSE, FL_CLOSE, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( MOVE, FL_MOVE, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( SHORTCUT, FL_SHORTCUT, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( DEACTIVATE, FL_DEACTIVATE, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( ACTIVATE, FL_ACTIVATE, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( HIDE, FL_HIDE, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( SHOW, FL_SHOW, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( PASTE, FL_PASTE, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( SELECTIONCLEAR, FL_SELECTIONCLEAR, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( MOUSEWHEEL, FL_MOUSEWHEEL, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( DND_ENTER, FL_DND_ENTER, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( DND_DRAG, FL_DND_DRAG, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( DND_LEAVE, FL_DND_LEAVE, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( DND_RELEASE, FL_DND_RELEASE, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( SCREEN_CONFIGURATION_CHANGED, FL_SCREEN_CONFIGURATION_CHANGED, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( FULLSCREEN, FL_FULLSCREEN, mrb_fltk_module );

  // Fl_Boxtype
  DEFINE_FIXNUM_CONSTANT( NO_BOX, FL_NO_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( FLAT_BOX, FL_FLAT_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( UP_BOX, FL_UP_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( DOWN_BOX, FL_DOWN_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( UP_FRAME, FL_UP_FRAME, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( DOWN_FRAME, FL_DOWN_FRAME, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( THIN_UP_BOX, FL_THIN_UP_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( THIN_DOWN_BOX, FL_THIN_DOWN_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( THIN_UP_FRAME, FL_THIN_UP_FRAME, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( THIN_DOWN_FRAME, FL_THIN_DOWN_FRAME, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( ENGRAVED_BOX, FL_ENGRAVED_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( EMBOSSED_BOX, FL_EMBOSSED_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( ENGRAVED_FRAME, FL_ENGRAVED_FRAME, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( EMBOSSED_FRAME, FL_EMBOSSED_FRAME, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( BORDER_BOX, FL_BORDER_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( SHADOW_BOX, _FL_SHADOW_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( BORDER_FRAME, FL_BORDER_FRAME, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( SHADOW_FRAME, _FL_SHADOW_FRAME, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( ROUNDED_BOX, _FL_ROUNDED_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( RSHADOW_BOX, _FL_RSHADOW_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( ROUNDED_FRAME, _FL_ROUNDED_FRAME, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( RFLAT_BOX, _FL_RFLAT_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( ROUND_UP_BOX, _FL_ROUND_UP_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( ROUND_DOWN_BOX, _FL_ROUND_DOWN_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( DIAMOND_UP_BOX, _FL_DIAMOND_UP_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( DIAMOND_DOWN_BOX, _FL_DIAMOND_DOWN_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( OVAL_BOX, _FL_OVAL_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( OSHADOW_BOX, _FL_OSHADOW_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( OVAL_FRAME, _FL_OVAL_FRAME, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( OFLAT_BOX, _FL_OFLAT_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( PLASTIC_UP_BOX, _FL_PLASTIC_UP_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( PLASTIC_DOWN_BOX, _FL_PLASTIC_DOWN_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( PLASTIC_UP_FRAME, _FL_PLASTIC_UP_FRAME, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( PLASTIC_DOWN_FRAME, _FL_PLASTIC_DOWN_FRAME, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( PLASTIC_THIN_UP_BOX, _FL_PLASTIC_THIN_UP_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( PLASTIC_THIN_DOWN_BOX, _FL_PLASTIC_THIN_DOWN_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( PLASTIC_ROUND_UP_BOX, _FL_PLASTIC_ROUND_UP_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( PLASTIC_ROUND_DOWN_BOX, _FL_PLASTIC_ROUND_DOWN_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( GTK_UP_BOX, _FL_GTK_UP_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( GTK_DOWN_BOX, _FL_GTK_DOWN_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( GTK_UP_FRAME, _FL_GTK_UP_FRAME, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( GTK_DOWN_FRAME, _FL_GTK_DOWN_FRAME, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( GTK_THIN_UP_BOX, _FL_GTK_THIN_UP_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( GTK_THIN_DOWN_BOX, _FL_GTK_THIN_DOWN_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( GTK_THIN_UP_FRAME, _FL_GTK_THIN_UP_FRAME, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( GTK_THIN_DOWN_FRAME, _FL_GTK_THIN_DOWN_FRAME, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( GTK_ROUND_UP_BOX, _FL_GTK_ROUND_UP_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( GTK_ROUND_DOWN_BOX, _FL_GTK_ROUND_DOWN_BOX, mrb_fltk_module );
  DEFINE_FIXNUM_CONSTANT( FREE_BOXTYPE, FL_FREE_BOXTYPE, mrb_fltk_module );

  // DEFINE_MODULE_METHOD( root, font_name, MRB_ARGS_REQ( 1 ) );
  mrb_define_module_function( mrb, mrb_fltk_module, "focus=", mrb_fltk_focus_setter_module_method, MRB_ARGS_REQ( 1 ) );
  mrb_define_module_function( mrb, mrb_fltk_module, "font", mrb_fltk_font_module_method, MRB_ARGS_OPT( 2 ) );
  mrb_define_module_function( mrb, mrb_fltk_module, "measure", mrb_fltk_measure_module_method, MRB_ARGS_REQ( 1 ) );
  mrb_define_module_function( mrb, mrb_fltk_module, "run", mrb_fltk_run_module_method, MRB_ARGS_NONE() );
  mrb_define_module_function( mrb, mrb_fltk_module, "width", mrb_fltk_width_module_method, MRB_ARGS_REQ( 1 ) );
  // DEFINE_MODULE_METHOD( root, set_fonts, MRB_ARGS_REQ( 1 ) );

  ARENA_RESTORE;
}
