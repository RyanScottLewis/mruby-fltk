#include <stdio.h>
#include <memory.h>

#include <Fl/Fl.h>

#include <Fl/Fl_Box.h>
#include <Fl/Fl_Button.h>
#include <Fl/Fl_Check_Button.h>
#include <Fl/Fl_Double_Window.h>
#include <Fl/Fl_File_Chooser.h>
#include <Fl/Fl_Image.h>
#include <Fl/Fl_Input.h>
#include <Fl/Fl_Light_Button.h>
#include <Fl/Fl_Menu.h>
#include <Fl/Fl_Menu_Bar.h>
#include <Fl/Fl_Menu_Button.h>
#include <Fl/Fl_Radio_Button.h>
#include <Fl/Fl_Radio_Light_Button.h>
#include <Fl/Fl_Radio_Round_Button.h>
#include <Fl/Fl_Repeat_Button.h>
#include <Fl/Fl_Return_Button.h>
#include <Fl/Fl_Round_Button.h>
#include <Fl/Fl_Select_Browser.h>
#include <Fl/Fl_Shared_Image.h>
#include <Fl/Fl_Text_Display.h>
#include <Fl/Fl_Text_Editor.h>
#include <Fl/Fl_Toggle_Button.h>
#include <Fl/Fl_Value_Output.h>
#include <Fl/Fl_Window.h>
#include <Fl/fl_ask.h>

#include <mruby.h>

#include <mruby/proc.h>
#include <mruby/data.h>
#include <mruby/string.h>
#include <mruby/array.h>
#include <mruby/hash.h>
#include <mruby/class.h>
#include <mruby/variable.h>

#include "mrb_fltk.h"
#include "helpers.h"

#include "fltk.h"
#include "widget.h"
#include "group.h"

#include "button.h"
#include "image.h"
#include "shared_image.h"
#include "input.h"
#include "value_output.h"
#include "menu_bar.h"
#include "menu_item.h"
#include "browser.h"
#include "text_buffer.h"
#include "text_display.h"
#include "text_editor.h"
#include "window.h"
#include "double_window.h"

// =-=- Contexts -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

CONTEXT_DEFINE( image,       Fl_Image );
CONTEXT_DEFINE( menu_item,   Fl_Menu_Item );
CONTEXT_DEFINE( text_buffer, Fl_Text_Buffer );
CONTEXT_DEFINE( widget,      Fl_Widget );

// =-=- Widgets -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

DECLARE_WIDGET( widget,         Fl_Widget );

DECLARE_WIDGET( browser,        Fl_Browser );
DECLARE_WIDGET( input,          Fl_Input );
DECLARE_WIDGET( menu_bar,       Fl_Menu_Bar );
DECLARE_WIDGET( menu_button,    Fl_Menu_Button );
DECLARE_WIDGET( select_browser, Fl_Select_Browser );
DECLARE_WIDGET( text_display,   Fl_Text_Display );
DECLARE_WIDGET( text_editor,    Fl_Text_Editor );
DECLARE_WIDGET( value_output,   Fl_Value_Output );

// =-=- Buttons -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

DECLARE_WIDGET( button,              Fl_Button );
DECLARE_WIDGET( check_button,        Fl_Check_Button );
DECLARE_WIDGET( light_button,        Fl_Light_Button );
DECLARE_WIDGET( radio_button,        Fl_Radio_Button );
DECLARE_WIDGET( radio_light_button,  Fl_Radio_Light_Button );
DECLARE_WIDGET( radio_round_button,  Fl_Radio_Round_Button );
DECLARE_WIDGET( repeat_button,       Fl_Repeat_Button );
DECLARE_WIDGET( return_button,       Fl_Return_Button );
DECLARE_WIDGET( round_button,        Fl_Round_Button );
DECLARE_WIDGET( toggle_button,       Fl_Toggle_Button );
DECLARE_WIDGET( toggle_light_button, Fl_Toggle_Light_Button );
DECLARE_WIDGET( toggle_round_button, Fl_Toggle_Round_Button );

// =-=- Windows -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=



// =-=- Hidden Objects -=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

DECLARE_HIDDEN_OBJECT( Fl_Shared_Image, Fl_Image );
DECLARE_HIDDEN_OBJECT( Fl_Group,        Fl_Widget );
DECLARE_HIDDEN_OBJECT( Fl_Box,          Fl_Widget );

// =-=- Constants -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

DEFINE_FIXNUM_CONSTANT( "NO_BOX",                 FL_NO_BOX,                  mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "FLAT_BOX",               FL_FLAT_BOX,                mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "UP_BOX",                 FL_UP_BOX,                  mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "DOWN_BOX",               FL_DOWN_BOX,                mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "UP_FRAME",               FL_UP_FRAME,                mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "DOWN_FRAME",             FL_DOWN_FRAME,              mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "THIN_UP_BOX",            FL_THIN_UP_BOX,             mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "THIN_DOWN_BOX",          FL_THIN_DOWN_BOX,           mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "THIN_UP_FRAME",          FL_THIN_UP_FRAME,           mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "THIN_DOWN_FRAME",        FL_THIN_DOWN_FRAME,         mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "ENGRAVED_BOX",           FL_ENGRAVED_BOX,            mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "EMBOSSED_BOX",           FL_EMBOSSED_BOX,            mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "ENGRAVED_FRAME",         FL_ENGRAVED_FRAME,          mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "EMBOSSED_FRAME",         FL_EMBOSSED_FRAME,          mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "BORDER_BOX",             FL_BORDER_BOX,              mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "SHADOW_BOX",             _FL_SHADOW_BOX,             mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "BORDER_FRAME",           FL_BORDER_FRAME,            mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "SHADOW_FRAME",           _FL_SHADOW_FRAME,           mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "ROUNDED_BOX",            _FL_ROUNDED_BOX,            mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "RSHADOW_BOX",            _FL_RSHADOW_BOX,            mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "ROUNDED_FRAME",          _FL_ROUNDED_FRAME,          mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "RFLAT_BOX",              _FL_RFLAT_BOX,              mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "ROUND_UP_BOX",           _FL_ROUND_UP_BOX,           mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "ROUND_DOWN_BOX",         _FL_ROUND_DOWN_BOX,         mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "DIAMOND_UP_BOX",         _FL_DIAMOND_UP_BOX,         mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "DIAMOND_DOWN_BOX",       _FL_DIAMOND_DOWN_BOX,       mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "OVAL_BOX",               _FL_OVAL_BOX,               mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "OSHADOW_BOX",            _FL_OSHADOW_BOX,            mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "OVAL_FRAME",             _FL_OVAL_FRAME,             mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "OFLAT_BOX",              _FL_OFLAT_BOX,              mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "PLASTIC_UP_BOX",         _FL_PLASTIC_UP_BOX,         mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "PLASTIC_DOWN_BOX",       _FL_PLASTIC_DOWN_BOX,       mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "PLASTIC_UP_FRAME",       _FL_PLASTIC_UP_FRAME,       mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "PLASTIC_DOWN_FRAME",     _FL_PLASTIC_DOWN_FRAME,     mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "PLASTIC_THIN_UP_BOX",    _FL_PLASTIC_THIN_UP_BOX,    mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "PLASTIC_THIN_DOWN_BOX",  _FL_PLASTIC_THIN_DOWN_BOX,  mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "PLASTIC_ROUND_UP_BOX",   _FL_PLASTIC_ROUND_UP_BOX,   mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "PLASTIC_ROUND_DOWN_BOX", _FL_PLASTIC_ROUND_DOWN_BOX, mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "GTK_UP_BOX",             _FL_GTK_UP_BOX,             mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "GTK_DOWN_BOX",           _FL_GTK_DOWN_BOX,           mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "GTK_UP_FRAME",           _FL_GTK_UP_FRAME,           mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "GTK_DOWN_FRAME",         _FL_GTK_DOWN_FRAME,         mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "GTK_THIN_UP_BOX",        _FL_GTK_THIN_UP_BOX,        mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "GTK_THIN_DOWN_BOX",      _FL_GTK_THIN_DOWN_BOX,      mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "GTK_THIN_UP_FRAME",      _FL_GTK_THIN_UP_FRAME,      mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "GTK_THIN_DOWN_FRAME",    _FL_GTK_THIN_DOWN_FRAME,    mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "GTK_ROUND_UP_BOX",       _FL_GTK_ROUND_UP_BOX,       mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "GTK_ROUND_DOWN_BOX",     _FL_GTK_ROUND_DOWN_BOX,     mrb_fltk_box_type_module );
DEFINE_FIXNUM_CONSTANT( "FREE_BOXTYPE",           FL_FREE_BOXTYPE,            mrb_fltk_box_type_module );

// =-=- Gem Hooks -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

extern "C"
{

void
mrb_mruby_fltk_gem_init(mrb_state *mrb)
{
  DEFINE_FLTK_MODULE();
  DEFINE_FLTK_WIDGET_CLASS();
  DEFINE_FLTK_GROUP_CLASS();
  
  DEFINE_FLTK_BUTTON_CLASSES();
  
  DEFINE_FLTK_IMAGE_CLASS();
  DEFINE_FLTK_SHARED_IMAGE_CLASS();
  
  DEFINE_FLTK_INPUT_CLASS();
  DEFINE_FLTK_VALUE_OUTPUT_CLASS();
  
  DEFINE_FLTK_MENU_ITEM_CLASS();
  DEFINE_FLTK_MENU_BAR_CLASS();
  
  DEFINE_FLTK_BROWSER_CLASS();
  
  DEFINE_FLTK_TEXT_BUFFER_CLASS();
  DEFINE_FLTK_TEXT_DISPLAY_CLASS();
  DEFINE_FLTK_TEXT_EDITOR_CLASS();
  
  DEFINE_FLTK_WINDOW_CLASS();
  DEFINE_FLTK_DOUBLE_WINDOW_CLASS();
}

void mrb_mruby_fltk3_gem_final(mrb_state* mrb) {}

}
