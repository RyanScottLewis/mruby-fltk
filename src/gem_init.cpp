// #include <stdio.h>

// #include <Fl/Fl.h>

// TODO: Should be in respective files?
// #include <Fl/Fl_Box.h>
// #include <Fl/Fl_Button.h>
// #include <Fl/Fl_Check_Button.h>
// #include <Fl/Fl_Double_Window.h>
// #include <Fl/Fl_File_Chooser.h>
// #include <Fl/Fl_Image.h>
// #include <Fl/Fl_Input.h>
// #include <Fl/Fl_Light_Button.h>
// #include <Fl/Fl_Menu.h>
// #include <Fl/Fl_Menu_Bar.h>
// #include <Fl/Fl_Menu_Button.h>
// #include <Fl/Fl_Radio_Button.h>
// #include <Fl/Fl_Radio_Light_Button.h>
// #include <Fl/Fl_Radio_Round_Button.h>
// #include <Fl/Fl_Repeat_Button.h>
// #include <Fl/Fl_Return_Button.h>
// #include <Fl/Fl_Round_Button.h>
// #include <Fl/Fl_Select_Browser.h>
// #include <Fl/Fl_Shared_Image.h>
// #include <Fl/Fl_Text_Display.h>
// #include <Fl/Fl_Text_Editor.h>
// #include <Fl/Fl_Toggle_Button.h>
// #include <Fl/Fl_Value_Output.h>
// #include <Fl/Fl_Window.h>
// #include <Fl/fl_ask.h>

#include <mruby.h>

// #include <mruby/proc.h>
// #include <mruby/data.h>
// #include <mruby/string.h>
// #include <mruby/array.h>
// #include <mruby/hash.h>
// #include <mruby/class.h>
// #include <mruby/variable.h>

// #include "helpers.h"
// #include "constants.h"

#include "fltk.h"
#include "widget.h"
#include "group.h"

// #include "button.h"
// #include "input.h"
// #include "value_output.h"
// #include "browser.h"

// #include "menu_bar.h"
// #include "menu_item.h"

// #include "text_buffer.h"
// #include "text_display.h"
// #include "text_editor.h"

// #include "image.h"
// #include "shared_image.h"

#include "window.h"
// #include "double_window.h"

// =-=- Contexts -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// TODO: Should be in respective files

// CONTEXT_DEFINE( image, Fl_Image );
// CONTEXT_DEFINE( menu_item, Fl_Menu_Item );
// CONTEXT_DEFINE( text_buffer, Fl_Text_Buffer );

// =-=- Gem Hooks -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

extern "C" {

void mrb_mruby_fltk_gem_init( mrb_state *mrb ) {
  mrb_fltk_module_init( mrb );
  mrb_fltk_widget_class_init( mrb );
  mrb_fltk_group_class_init( mrb );

  // mrb_fltk_button_class_init( mrb );
  // mrb_fltk_input_class_init( mrb );
  // mrb_fltk_value_output_class_init( mrb );

  // mrb_fltk_browser_class_init( mrb );
  // mrb_fltk_select_browser_class_init( mrb );

  // mrb_fltk_image_class_init( mrb );
  // mrb_fltk_shared_image_class_init( mrb );

  // mrb_fltk_menu_item_class_init( mrb );
  // mrb_fltk_menu_bar_class_init( mrb );

  // mrb_fltk_text_buffer_class_init( mrb );
  // mrb_fltk_text_display_class_init( mrb );
  // mrb_fltk_text_editor_class_init( mrb );

  mrb_fltk_window_class_init( mrb );
  // mrb_fltk_double_window_class_init( mrb );
}

void mrb_mruby_fltk_gem_final( mrb_state *mrb ) {
}
}
