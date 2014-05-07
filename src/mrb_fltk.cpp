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
#include "fltk.h"
#include "widget.h"
#include "group.h"
#include "image.h"

// =-=- Contexts -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

CONTEXT_DEFINE( image,       Fl_Image );
CONTEXT_DEFINE( menu_item,   Fl_Menu_Item );
CONTEXT_DEFINE( text_buffer, Fl_Text_Buffer );
CONTEXT_DEFINE( widget,      Fl_Widget );

// =-=- Helpers -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

static void
mrb_fltk_free(mrb_state *mrb, void *p)
{
  free(p);
}

static bool
mrb_fltk_arg_check(const char *t, int argc, mrb_value *argv)
{
  int n, l = strlen(t);
  
  if ( l != argc ) return false;
  
  for ( n = 0; n < l; n++ ) {
    if ( n >= argc ) return false;
    if ( t[n] == 'i' && mrb_type( argv[n] ) != MRB_TT_FIXNUM ) return false;
    if ( t[n] == 'd' && mrb_type( argv[n] ) != MRB_TT_FLOAT ) return false;
    if ( t[n] == 's' && mrb_type( argv[n] ) != MRB_TT_STRING ) return false;
    if ( t[n] == 'b' && mrb_type( argv[n] ) != MRB_TT_TRUE && mrb_type( argv[n] ) != MRB_TT_FALSE ) return false;
  }
  
  return true;
}

// =-=- FLTK::Window  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// FLTK::Widget#show
static mrb_value
mrb_fltk_window_show_method(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP(widget);
  
  ( (Fl_Window *) context->fl_instance )->show();
  
  return mrb_nil_value();
}

// =-=- Widgets -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

DECLARE_WIDGET( browser,             Fl_Browser );
DECLARE_WIDGET( input,               Fl_Input );
DECLARE_WIDGET( menu_bar,            Fl_Menu_Bar );
DECLARE_WIDGET( menu_button,         Fl_Menu_Button );
DECLARE_WIDGET( select_browser,      Fl_Select_Browser );
DECLARE_WIDGET( text_display,        Fl_Text_Display );
DECLARE_WIDGET( text_editor,         Fl_Text_Editor );
DECLARE_WIDGET( value_output,        Fl_Value_Output );
DECLARE_WIDGET( widget,              Fl_Widget );

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

DECLARE_WINDOW( window,        Fl_Window );
DECLARE_WINDOW( double_window, Fl_Double_Window );

// =-=- Hidden Objects -=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

DECLARE_HIDDEN_OBJECT( Fl_Shared_Image, Fl_Image );
DECLARE_HIDDEN_OBJECT( Fl_Group,        Fl_Widget );
DECLARE_HIDDEN_OBJECT( Fl_Box,          Fl_Widget );

// struct RClass *mrb_fltk_box_type_module;
//
// // TODO
// #define DEFINE_FLTK_CONSTANT(rb_name, fl_name, module)                 \
//   mrb_define_const( mrb, module, rb_name, mrb_fixnum(fl_name) );
//
// // enum Fl_Boxtype
// DEFINE_FLTK_CONSTANT( "NO_BOX", FL_NO_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "FLAT_BOX", FL_FLAT_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "UP_BOX", FL_UP_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "DOWN_BOX", FL_DOWN_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "UP_FRAME", FL_UP_FRAME, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "DOWN_FRAME", FL_DOWN_FRAME, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "THIN_UP_BOX", FL_THIN_UP_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "THIN_DOWN_BOX", FL_THIN_DOWN_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "THIN_UP_FRAME", FL_THIN_UP_FRAME, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "THIN_DOWN_FRAME", FL_THIN_DOWN_FRAME, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "ENGRAVED_BOX", FL_ENGRAVED_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "EMBOSSED_BOX", FL_EMBOSSED_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "ENGRAVED_FRAME", FL_ENGRAVED_FRAME, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "EMBOSSED_FRAME", FL_EMBOSSED_FRAME, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "BORDER_BOX", FL_BORDER_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "SHADOW_BOX", _FL_SHADOW_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "BORDER_FRAME", FL_BORDER_FRAME, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "SHADOW_FRAME", _FL_SHADOW_FRAME, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "ROUNDED_BOX", _FL_ROUNDED_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "RSHADOW_BOX", _FL_RSHADOW_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "ROUNDED_FRAME", _FL_ROUNDED_FRAME, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "RFLAT_BOX", _FL_RFLAT_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "ROUND_UP_BOX", _FL_ROUND_UP_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "ROUND_DOWN_BOX", _FL_ROUND_DOWN_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "DIAMOND_UP_BOX", _FL_DIAMOND_UP_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "DIAMOND_DOWN_BOX", _FL_DIAMOND_DOWN_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "OVAL_BOX", _FL_OVAL_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "OSHADOW_BOX", _FL_OSHADOW_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "OVAL_FRAME", _FL_OVAL_FRAME, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "OFLAT_BOX", _FL_OFLAT_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "PLASTIC_UP_BOX", _FL_PLASTIC_UP_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "PLASTIC_DOWN_BOX", _FL_PLASTIC_DOWN_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "PLASTIC_UP_FRAME", _FL_PLASTIC_UP_FRAME, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "PLASTIC_DOWN_FRAME", _FL_PLASTIC_DOWN_FRAME, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "PLASTIC_THIN_UP_BOX", _FL_PLASTIC_THIN_UP_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "PLASTIC_THIN_DOWN_BOX", _FL_PLASTIC_THIN_DOWN_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "PLASTIC_ROUND_UP_BOX", _FL_PLASTIC_ROUND_UP_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "PLASTIC_ROUND_DOWN_BOX", _FL_PLASTIC_ROUND_DOWN_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "GTK_UP_BOX", _FL_GTK_UP_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "GTK_DOWN_BOX", _FL_GTK_DOWN_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "GTK_UP_FRAME", _FL_GTK_UP_FRAME, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "GTK_DOWN_FRAME", _FL_GTK_DOWN_FRAME, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "GTK_THIN_UP_BOX", _FL_GTK_THIN_UP_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "GTK_THIN_DOWN_BOX", _FL_GTK_THIN_DOWN_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "GTK_THIN_UP_FRAME", _FL_GTK_THIN_UP_FRAME, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "GTK_THIN_DOWN_FRAME", _FL_GTK_THIN_DOWN_FRAME, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "GTK_ROUND_UP_BOX", _FL_GTK_ROUND_UP_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "GTK_ROUND_DOWN_BOX", _FL_GTK_ROUND_DOWN_BOX, mrb_fltk_box_type_module );
// DEFINE_FLTK_CONSTANT( "FREE_BOXTYPE", FL_FREE_BOXTYPE, mrb_fltk_box_type_module );

extern "C"
{

void
mrb_mruby_fltk_gem_init(mrb_state* mrb)
{
  
  // =-=- FLTK -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  
  ARENA_SAVE;
  
  struct RClass *mrb_fltk_module = mrb_define_module(mrb, "FLTK");
  
  mrb_define_module_function( mrb, mrb_fltk_module, "font_name",    mrb_fltk_font_name, ARGS_REQ(1) );
  mrb_define_module_function( mrb, mrb_fltk_module, "run",          mrb_fltk_run,       ARGS_NONE() );
  mrb_define_module_function( mrb, mrb_fltk_module, "set_fonts",    mrb_fltk_set_fonts, ARGS_REQ(1) );
  
  ARENA_RESTORE;
  
  // =-=- FLTK::Widget  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  
  ARENA_SAVE;
  
  DEFINE_CLASS( widget, "Widget", mrb->object_class );
  
  DEFINE_INSTANCE_METHOD( widget, callback,   ARGS_OPT(1) );
  DEFINE_INSTANCE_METHOD( widget, hide,       ARGS_NONE() );
  DEFINE_INSTANCE_METHOD( widget, initialize, ARGS_ANY() );
  DEFINE_INSTANCE_METHOD( widget, redraw,     ARGS_NONE() );
  DEFINE_INSTANCE_METHOD( widget, show,       ARGS_NONE() );
  
  DEFINE_FIXNUM_ATTRIBUTE_READER( widget, height, Fl_Widget, h );
  DEFINE_FIXNUM_ATTRIBUTE_READER( widget, width,  Fl_Widget, w );
  DEFINE_FIXNUM_ATTRIBUTE_READER( widget, x,      Fl_Widget, x );
  DEFINE_FIXNUM_ATTRIBUTE_READER( widget, y,      Fl_Widget, y );
  
  DEFINE_FIXNUM_ATTRIBUTE_ACCESSOR( widget, box,        Fl_Widget, box );
  DEFINE_FIXNUM_ATTRIBUTE_ACCESSOR( widget, label_font, Fl_Widget, labelfont );
  DEFINE_FIXNUM_ATTRIBUTE_ACCESSOR( widget, label_size, Fl_Widget, labelsize );
  
  DEFINE_STRING_ATTRIBUTE_ACCESSOR( widget, label, Fl_Widget, label );
  
  mrb_define_method( mrb, mrb_fltk_widget_class, "image",      mrb_fltk_widget_image_get_method,  ARGS_NONE() );
  mrb_define_method( mrb, mrb_fltk_widget_class, "image=",     mrb_fltk_widget_image_set_method,  ARGS_REQ(1) );
  mrb_define_method( mrb, mrb_fltk_widget_class, "visible?",   mrb_fltk_widget_visible,    ARGS_NONE() );
  
  ARENA_RESTORE;
  
  // =-=- FLTK::Image -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  
  ARENA_SAVE;
  
  DEFINE_CLASS( image, "Image", mrb->object_class );
  
  DEFINE_INSTANCE_METHOD( image, initialize,    ARGS_REQ(3) );
  DEFINE_INSTANCE_METHOD( image, copy,          ( MRB_ARGS_REQ(1) | MRB_ARGS_REQ(3) ) );
  
  DEFINE_FIXNUM_ATTRIBUTE_READER( image, width,          Fl_Image, w  );
  DEFINE_FIXNUM_ATTRIBUTE_READER( image, height,         Fl_Image, h  );
  DEFINE_FIXNUM_ATTRIBUTE_READER( image, depth,          Fl_Image, d  );
  DEFINE_FIXNUM_ATTRIBUTE_READER( image, line_data_size, Fl_Image, ld );
  
  ARENA_RESTORE;
  
  // =-=- FLTK::SharedImage -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  
  ARENA_SAVE;
  
  DEFINE_CLASS( shared_image, "SharedImage", mrb_fltk_image_class );
  
  DEFINE_CLASS_METHOD( shared_image, get, ARGS_REQ(1) );
  
  ARENA_RESTORE;
  
  // =-=- FLTK::Button and Subclasses -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=
  
  ARENA_SAVE;
  
  DEFINE_CLASS( button,              "Button",            mrb_fltk_widget_class );
  DEFINE_CLASS( check_button,        "CheckButton",       mrb_fltk_button_class );
  DEFINE_CLASS( light_button,        "LightButton",       mrb_fltk_button_class );
  DEFINE_CLASS( menu_button,         "MenuButton",        mrb_fltk_button_class );
  DEFINE_CLASS( radio_button,        "RadioButton",       mrb_fltk_button_class );
  DEFINE_CLASS( radio_light_button,  "RadioLightButton",  mrb_fltk_button_class );
  DEFINE_CLASS( radio_round_button,  "RadioRoundButton",  mrb_fltk_button_class );
  DEFINE_CLASS( repeat_button,       "RepeatButton",      mrb_fltk_button_class );
  DEFINE_CLASS( return_button,       "ReturnButton",      mrb_fltk_button_class );
  DEFINE_CLASS( round_button,        "RoundButton",       mrb_fltk_button_class );
  DEFINE_CLASS( toggle_button,       "ToggleButton",      mrb_fltk_button_class );
  DEFINE_CLASS( toggle_light_button, "ToggleLightButton", mrb_fltk_button_class );
  DEFINE_CLASS( toggle_round_button, "ToggleRoundButton", mrb_fltk_button_class );
  
  ARENA_RESTORE;
  
  // =-=- FLTK::ValueOutput -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  
  ARENA_SAVE;
  
  DEFINE_CLASS( value_output, "ValueOutput", mrb_fltk_widget_class );
  
  ARENA_RESTORE;
  
  // =-=- FLTK::Input -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  
  ARENA_SAVE;
  
  DEFINE_CLASS( input, "Input", mrb_fltk_widget_class );
  
  DEFINE_STRING_ATTRIBUTE_ACCESSOR( input, value, Fl_Widget, value );
  
  ARENA_RESTORE;
  
  // =-=- FLTK::MenuItem -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=
  
  ARENA_SAVE;
  
  DEFINE_CLASS( input, "MenuItem", mrb->object_class );
  
  ARENA_RESTORE;
  
  
  struct RClass* mrb_fltk_menu_item_class = mrb_define_class_under(mrb, mrb_fltk_class, "MenuItem", mrb->object_class);
  mrb_define_method(mrb, mrb_fltk_menu_item_class, "initialize", [] (mrb_state* mrb, mrb_value self) -> mrb_value {
    mrb_fltk_menu_item_context* context =
      (mrb_fltk_menu_item_context*) malloc(sizeof(mrb_fltk_menu_item_context));
    if (!context) mrb_raise(mrb, E_RUNTIME_ERROR, "can't alloc memory");
    memset(context, 0, sizeof(mrb_fltk_menu_item_context));
    context->rb_instance = self;
    context->fl_instance = new Fl_Menu_Item;
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "context"), mrb_obj_value(
      Data_Wrap_Struct(mrb, mrb->object_class,
      &fltk_menu_item_type, (void*) context)));
    return self;
  }, ARGS_NONE());
  
  
  
  
  
  
  DEFINE_CLASS(MenuBar, MenuItem);
  
  mrb_define_method(mrb, mrb_fltk_menu_bar_class, "add", [] (mrb_state* mrb, mrb_value self) -> mrb_value {
    CONTEXT_SETUP(Widget);
    mrb_value b = mrb_nil_value(), caption, shortcut;
    mrb_get_args(mrb, "&Si", &b, &caption, &shortcut);
    ((Fl_Menu_Bar*) context->fl_instance)->add(RSTRING_PTR(caption), mrb_fixnum(shortcut), [] (Fl_Widget* w, void* d) {
    });
    return mrb_nil_value();
  }, ARGS_REQ(1));
  
  mrb_define_method(mrb, mrb_fltk_menu_bar_class, "menu", [] (mrb_state* mrb, mrb_value self) -> mrb_value {
    CONTEXT_SETUP(Widget);
    struct RClass* mrb_fltk_class = mrb_class_get(mrb, "FLTK");
    struct RClass* mrb_fltk_menu_item_class = mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mrb_fltk_class), mrb_intern_cstr(mrb, "MenuItem")));
    mrb_value args[1];
    args[0] = mrb_obj_value(
      Data_Wrap_Struct(mrb, mrb->object_class,
      &fltk_menu_item_type, (void*) ((Fl_Menu_Bar*) context->fl_instance)->menu()));
    return mrb_class_new_instance(mrb, 1, args, mrb_fltk_menu_item_class);
  }, ARGS_NONE());
  
  
  
  
  
  
  DEFINE_CLASS(Group, Widget);
  INHERIT_GROUP(Group);
  
  
  
  DEFINE_CLASS(Browser, Group);
  
  mrb_define_method(mrb, mrb_fltk_browser_class, "load", [] (mrb_state* mrb, mrb_value self) -> mrb_value {
    CONTEXT_SETUP(Widget);
    mrb_value filename;
    mrb_get_args(mrb, "S", &filename);
    return mrb_fixnum_value(((Fl_Browser*) context->fl_instance)->load(RSTRING_PTR(filename)));
  }, ARGS_REQ(1));
  
  DEFINE_FIXNUM_ATTRIBUTE(Browser, Widget, value);
  
  mrb_define_method(mrb, mrb_fltk_browser_class, "text", [] (mrb_state* mrb, mrb_value self) -> mrb_value {
    CONTEXT_SETUP(Widget);
    mrb_value line = mrb_nil_value(), text = mrb_nil_value();
    mrb_get_args(mrb, "|i|S", &line, &text);
    if (mrb_nil_p(text)) {
      const char* text = NULL;
      if (mrb_nil_p(line)) {
        int value = ((Fl_Browser*) context->fl_instance)->value();
        text = ((Fl_Browser*) context->fl_instance)->text(value);
      } else {
        text = ((Fl_Browser*) context->fl_instance)->text(mrb_fixnum(line));
      }
      if (!text) return mrb_nil_value();
      return mrb_str_new_cstr(mrb, text);
    }
    ((Fl_Browser*) context->fl_instance)->text(mrb_fixnum(line), RSTRING_PTR(text));
    return mrb_nil_value();
  }, ARGS_REQ(1) | ARGS_OPT(1));
  
  mrb_define_method(mrb, mrb_fltk_browser_class, "icon", [] (mrb_state* mrb, mrb_value self) -> mrb_value {
    CONTEXT_SETUP(Widget);
    mrb_value line = mrb_nil_value(), image = mrb_nil_value();
    mrb_get_args(mrb, "|i|o", &line, &image);
    if (mrb_nil_p(image)) {
      Fl_Image* image = NULL;
      if (mrb_nil_p(line)) {
        int value = ((Fl_Browser*) context->fl_instance)->value();
        image = ((Fl_Browser*) context->fl_instance)->icon(value);
      } else {
        image = ((Fl_Browser*) context->fl_instance)->icon(mrb_fixnum(line));
      }
      if (!image) return mrb_nil_value();
      mrb_fltk_image_context* image_context =
        (mrb_fltk_image_context*) malloc(sizeof(mrb_fltk_image_context));
      if (!context) mrb_raise(mrb, E_RUNTIME_ERROR, "can't alloc memory");
      memset(image_context, 0, sizeof(mrb_fltk_image_context));
      image_context->rb_instance = self;
      image_context->fl_instance = image;
      mrb_value args[1];
      struct RClass* mrb_fltk_class = mrb_class_get(mrb, "FLTK");
      struct RClass* mrb_fltk_image_class = mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mrb_fltk_class), mrb_intern_cstr(mrb, "Image")));
      args[0] = mrb_obj_value(
        Data_Wrap_Struct(mrb, mrb->object_class,
        &fltk_image_type, (void*) image_context));
      return mrb_class_new_instance(mrb, 1, args, mrb_fltk_image_class);
    }
    return mrb_nil_value();
  }, ARGS_REQ(1) | ARGS_OPT(1));
  
  mrb_define_method(mrb, mrb_fltk_browser_class, "add", [] (mrb_state* mrb, mrb_value self) -> mrb_value {
    CONTEXT_SETUP(Widget);
    mrb_value text = mrb_nil_value();
    mrb_get_args(mrb, "S", &text);
    ((Fl_Browser*) context->fl_instance)->add(RSTRING_PTR(text));
    return mrb_nil_value();
  }, ARGS_REQ(1));
  
  mrb_define_method(mrb, mrb_fltk_browser_class, "column_widths", [] (mrb_state* mrb, mrb_value self) -> mrb_value {
    CONTEXT_SETUP(Widget);
    const int* widths = ((Fl_Browser*) context->fl_instance)->column_widths();
    int n = 0;
    ARENA_SAVE;
    mrb_value arr = mrb_ary_new(mrb);
    while (widths[n]) {
      mrb_ary_push(mrb, arr, mrb_fixnum_value(widths[n]));
      ARENA_RESTORE;
      n++;
    }
    return arr;
  }, ARGS_NONE());
  
  mrb_define_method(mrb, mrb_fltk_browser_class, "column_widths=", [] (mrb_state* mrb, mrb_value self) -> mrb_value {
    CONTEXT_SETUP(Widget);
    static int* widths = NULL;
    if (widths) free((void*) widths);
    widths = (int*) ((Fl_Browser*) context->fl_instance)->column_widths();
    mrb_value arr = mrb_nil_value();
    mrb_get_args(mrb, "A", &arr);
    int n = 0, len = RARRAY_LEN(arr);
    widths = (int*) malloc(sizeof(int) * (len+1));
    for (n = 0; n < len; n++) {
      widths[n] = mrb_fixnum(mrb_funcall(mrb, RARRAY_PTR(arr)[n], "to_i", 0, NULL));
    }
    widths[n] = 0;
    ((Fl_Browser*) context->fl_instance)->column_widths(widths);
    return mrb_nil_value();
  }, ARGS_REQ(1));
  
  
  DEFINE_CLASS(SelectBrowser, Browser);
  
  DEFINE_CLASS(TextDisplay, Group);
  
  DEFINE_CLASS(TextEditor, TextDisplay);
  
  
  
  struct RClass* mrb_fltk_window_class = mrb_define_class_under(mrb, mrb_fltk_class, "Window", mrb_fltk_widget_class);
  mrb_define_method(mrb, mrb_fltk_window_class, "initialize", mrb_fltk_window_init, ARGS_ANY());
  mrb_define_method(mrb, mrb_fltk_window_class, "show", mrb_fltk_window_show, ARGS_OPT(1));
  INHERIT_GROUP(Window);
  
  
  DEFINE_CLASS(DoubleWindow, Window);
  
  
  
  struct RClass* _class_fltk3_TextBuffer = mrb_define_class_under(mrb, mrb_fltk_class, "TextBuffer", mrb->object_class);
  mrb_define_method(mrb, _class_fltk3_TextBuffer, "initialize", [] (mrb_state* mrb, mrb_value self) -> mrb_value {
    mrb_fltk3_TextBuffer_context* context =
      (mrb_fltk3_TextBuffer_context*) malloc(sizeof(mrb_fltk3_TextBuffer_context));
    if (!context) mrb_raise(mrb, E_RUNTIME_ERROR, "can't alloc memory");
    memset(context, 0, sizeof(mrb_fltk3_TextBuffer_context));
    context->rb_instance = self;
    context->fl_instance = new fltk3::TextBuffer;
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "context"), mrb_obj_value(
      Data_Wrap_Struct(mrb, mrb->object_class,
      &fltk3_TextBuffer_type, (void*) context)));
    return self;
  }, ARGS_NONE());
  
  mrb_define_method(mrb, _class_fltk3_TextDisplay, "buffer", [] (mrb_state* mrb, mrb_value self) -> mrb_value {
    CONTEXT_SETUP(Widget);
    struct RClass* mrb_fltk_class = mrb_class_get(mrb, "FLTK3");
    struct RClass* _class_fltk3_TextBuffer = mrb_class_ptr(mrb_const_get(mrb, mrb_obj_value(mrb_fltk_class), mrb_intern_cstr(mrb, "TextBuffer")));
    mrb_value args[1];
    args[0] = mrb_obj_value(
      Data_Wrap_Struct(mrb, mrb->object_class,
      &fltk3_TextBuffer_type, (void*) ((fltk3::TextDisplay*) context->fl_instance)->buffer()));
    return mrb_class_new_instance(mrb, 1, args, _class_fltk3_TextBuffer);
  }, ARGS_NONE());
  
  mrb_define_method(mrb, _class_fltk3_TextDisplay, "buffer=", [] (mrb_state* mrb, mrb_value self) -> mrb_value {
    CONTEXT_SETUP(Widget);
    mrb_value textbuffer;
    mrb_get_args(mrb, "o", &textbuffer);
    mrb_value textbuffer_value_context;
    mrb_fltk3_TextBuffer_context* textbuffer_context = NULL;
    textbuffer_value_context = mrb_iv_get(mrb, textbuffer, mrb_intern_cstr(mrb, "context"));
    Data_Get_Struct(mrb, textbuffer_value_context, &fltk3_TextBuffer_type, textbuffer_context);
    ((fltk3::TextDisplay*) context->fl_instance)->buffer(textbuffer_context->fl_instance);
    return mrb_nil_value();
  }, ARGS_REQ(1));
  
  DEFINE_FIXNUM_ATTRIBUTE_READER(TextBuffer, TextBuffer, length);
  DEFINE_STR_PROP(TextBuffer, TextBuffer, text);
  
  ARENA_RESTORE;
  
  fltk3::register_images();
}

void mrb_mruby_fltk3_gem_final(mrb_state* mrb) {}

}
