#include <Fl/Fl.h>
#include <Fl/Fl_Group.h>

#include <mruby.h>

#include "fltk.h"
#include "widget.h"
#include "group.h"

#include "pack.h"
#include "box.h"

#include "button.h"
#include "enter_button.h"

#include "input.h"
// #include "value_output.h"

#include "browser.h"
#include "hold_browser.h"
#include "select_browser.h"

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

  mrb_fltk_pack_class_init( mrb );
  mrb_fltk_box_class_init( mrb );

  mrb_fltk_button_class_init( mrb );
  mrb_fltk_enter_button_class_init( mrb );

  mrb_fltk_input_class_init( mrb );
  // mrb_fltk_value_output_class_init( mrb );

  mrb_fltk_browser_class_init( mrb );
  mrb_fltk_hold_browser_class_init( mrb );
  mrb_fltk_select_browser_class_init( mrb );

  // mrb_fltk_image_class_init( mrb );
  // mrb_fltk_shared_image_class_init( mrb );

  // mrb_fltk_menu_item_class_init( mrb );
  // mrb_fltk_menu_bar_class_init( mrb );

  // mrb_fltk_text_buffer_class_init( mrb );
  // mrb_fltk_text_display_class_init( mrb );
  // mrb_fltk_text_editor_class_init( mrb );

  mrb_fltk_window_class_init( mrb );
  // mrb_fltk_double_window_class_init( mrb );

  Fl_Group::current( 0 ); // Prevent new widgets from being added to a group
}

void mrb_mruby_fltk_gem_final( mrb_state *mrb ) {
}
}
