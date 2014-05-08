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
// #include "constants.h"

#include "fltk.h"
#include "widget.h"
#include "group.h"

#include "button.h"
#include "input.h"
#include "value_output.h"
#include "browser.h"

#include "menu_bar.h"
#include "menu_item.h"

#include "text_buffer.h"
#include "text_display.h"
#include "text_editor.h"

#include "image.h"
#include "shared_image.h"

#include "window.h"
#include "double_window.h"

// =-=- Contexts -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// TODO: Should be in respective files

CONTEXT_DEFINE( image, Fl_Image );
CONTEXT_DEFINE( menu_item, Fl_Menu_Item );
CONTEXT_DEFINE( text_buffer, Fl_Text_Buffer );
CONTEXT_DEFINE( widget, Fl_Widget );

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
  DEFINE_FLTK_INPUT_CLASS();
  DEFINE_FLTK_VALUE_OUTPUT_CLASS();
  
  DEFINE_FLTK_BROWSER_CLASS();
  
  DEFINE_FLTK_IMAGE_CLASS();
  DEFINE_FLTK_SHARED_IMAGE_CLASS();
  
  DEFINE_FLTK_MENU_ITEM_CLASS();
  DEFINE_FLTK_MENU_BAR_CLASS();
  
  DEFINE_FLTK_TEXT_BUFFER_CLASS();
  DEFINE_FLTK_TEXT_DISPLAY_CLASS();
  DEFINE_FLTK_TEXT_EDITOR_CLASS();
  
  DEFINE_FLTK_WINDOW_CLASS();
  DEFINE_FLTK_DOUBLE_WINDOW_CLASS();
}

void mrb_mruby_fltk_gem_final(mrb_state* mrb) {

}
