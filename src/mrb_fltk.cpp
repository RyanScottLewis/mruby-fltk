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

#if 1
#define ARENA_SAVE                                     \
  int ai = mrb_gc_arena_save(mrb);                     \
  if (ai == MRB_ARENA_SIZE) {                          \
    mrb_raise(mrb, E_RUNTIME_ERROR, "arena overflow"); \
  }
#define ARENA_RESTORE            \
  mrb_gc_arena_restore(mrb, ai);
#else
#define ARENA_SAVE
#define ARENA_RESTORE
#endif

static void
mrb_fltk_free(mrb_state *mrb, void *p)
{
  free(p);
}

#define DECLARE_TYPE(name, type)                                                           \
typedef struct {                                                                           \
  type *fl_instance;                                                                       \
  mrb_value rb_instance;                                                                   \
  mrb_state *mrb;                                                                          \
} mrb_fltk_##name##_context;                                                               \
                                                                                           \
static const struct mrb_data_type fltk_##name##_type = { "fltk_" # name, mrb_fltk_free };

DECLARE_TYPE( widget, Fl_Widget );
DECLARE_TYPE( text_buffer, Fl_Text_Buffer );
DECLARE_TYPE( image, Fl_Image );
DECLARE_TYPE( menu_item, Fl_Menu_Item );

static bool
arg_check(const char *t, int argc, mrb_value *argv)
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

#define CONTEXT_SETUP(name)                                                 \
  mrb_value value_context;                                                  \
  mrb_fltk_##name##_context *context = NULL;                                \
  value_context = mrb_iv_get( mrb, self, mrb_intern_cstr(mrb, "context") ); \
  Data_Get_Struct( mrb, value_context, &fltk_##name##_type, context );

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// =-=- FLTK::Widget  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// FLTK::Widget#box
// Gets the box type of the widget.
static mrb_value
mrb_fltk_widget_box_get(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP(widget);
  
  struct RClass* mrb_fltk_class = mrb_class_get( mrb, "FLTK" );
  struct RClass* mrb_fltk_box_class = mrb_class_ptr( mrb_const_get( mrb, mrb_obj_value(mrb_fltk_class), mrb_intern_cstr(mrb, "Box") ) );
  
  mrb_value args[1];
  args[0] = mrb_obj_value(
    Data_Wrap_Struct( mrb, mrb->object_class, &fltk_widget_type, (void*) context->fl_instance->box() )
  );
  
  return mrb_class_new_instance( mrb, 1, args, mrb_fltk_box_class );
}

// FLTK::Widget#box=(box_type)
// Sets the box type for the widget. Must be a FLTK::BoxType.
static mrb_value
mrb_fltk_widget_box_set(mrb_state *mrb, mrb_value self)
{ // TODO: Must be a FLTK::BoxType.
  CONTEXT_SETUP(widget);
  
  mrb_value box_type;
  mrb_get_args( mrb, "i", &box_type );
  
  if ( !mrb_nil_p(box_type) ) {
    context->fl_instance->box( (Fl_Boxtype) mrb_fixnum(box_type) );
  } else {
    context->fl_instance->box(); // TODO: Should raise error
  }
  
  return mrb_nil_value();
}

// FLTK::Widget#image
// Gets the image that is used as part of the widget label.
static mrb_value
mrb_fltk_widget_image_get(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP(widget);
  
  struct RClass* mrb_fltk_class = mrb_class_get( mrb, "FLTK" );
  struct RClass* mrb_fltk_image_class = mrb_class_ptr( mrb_const_get( mrb, mrb_obj_value(mrb_fltk_class), mrb_intern_cstr(mrb, "Image") ) );
  
  mrb_value args[1];
  args[0] = mrb_obj_value(
    Data_Wrap_Struct(mrb, mrb->object_class, &fltk_image_type, (void*) context->fl_instance->image() )
  );
  
  return mrb_class_new_instance( mrb, 1, args, mrb_fltk_image_class );
}

// FLTK::Widget#image=(image)
// Sets the image to use as part of the widget label. Must be a FLTK::Image
static mrb_value
mrb_fltk_widget_image_set(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP(widget);
  
  mrb_value image;
  mrb_get_args( mrb, "o", &image );
  
  
  if (!mrb_nil_p(image)) {
    mrb_value image_value_context;
    mrb_fltk_image_context *image_context;
    
    image_value_context = mrb_iv_get( mrb, image, mrb_intern_cstr(mrb, "context") );
    Data_Get_Struct( mrb, image_value_context, &fltk_image_type, image_context );
    
    context->fl_instance->image( (Fl_Image*) image_context->fl_instance );
  } else {
    context->fl_instance->image( NULL );
  }
  
  return mrb_nil_value();
}

// FLTK::Widget#show
// Makes a widget visible.
static mrb_value
mrb_fltk_widget_show(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP(widget);
  
  context->fl_instance->show();
  
  return mrb_nil_value();
}

// FLTK::Widget#hide
// Makes a widget invisible.
static mrb_value
mrb_fltk_widget_hide(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP(widget);
  
  context->fl_instance->hide();
  
  return mrb_nil_value();
}

// FLTK::Widget#visible?
// Returns whether a widget is visible.
static mrb_value
mrb_fltk_widget_visible(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP(widget);
  
  return context->fl_instance->visible() ? mrb_true_value() : mrb_false_value();
}

static void
_mrb_fltk_widget_callback(Fl_Widget *v, void *data)
{
  mrb_value args[2];
  
  mrb_fltk_widget_context *context = (mrb_fltk_widget_context*) data;
  mrb_state *mrb = context->mrb;
  mrb_value proc = mrb_iv_get( mrb, context->rb_instance, mrb_intern_cstr(mrb, "callback") );
  mrb_value value = mrb_iv_get( mrb, context->rb_instance, mrb_intern_cstr(mrb, "value") );
  args[0] = context->rb_instance;
  args[1] = value;
  
  mrb_yield_argv( mrb, proc, 2, args );
}

// FLTK::Widget#callback
// Gets or sets the current callback function for the widget. 
static mrb_value
mrb_fltk_widget_callback(mrb_state *mrb, mrb_value self)
{ // TODO: Make this more Ruby-ish! And the variables are ambiguous
  CONTEXT_SETUP(widget);
  
  mrb_value b = mrb_nil_value();
  mrb_value v = mrb_nil_value();
  
  mrb_get_args(mrb, "&|o", &b, &v);
  
  if ( !mrb_nil_p(b) ) {
    mrb_iv_set( mrb, self, mrb_intern_cstr(mrb, "callback"), b );
    mrb_iv_set( mrb, self, mrb_intern_cstr(mrb, "value"), v );
    
    context->fl_instance->callback( _mrb_fltk_widget_callback, context );
  }
  return mrb_nil_value();
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// =-=- FLTK::Window  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// FLTK::Widget#show
static mrb_value
mrb_fltk_window_show(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP(widget);
  
  ( (Fl_Window*) context->fl_instance )->show(0, NULL);
  
  return mrb_nil_value();
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// =-=- FLTK::Group -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

static mrb_value
mrb_fltk_group_begin(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP(widget);
  
  mrb_value b = mrb_nil_value();
  
  mrb_get_args(mrb, "&", &b);
  
  if ( !mrb_nil_p(b) ) {
    mrb_value args[1];
    
    args[0] = self;
    
    ( (Fl_Group*) context->fl_instance )->begin();
    mrb_yield_argv( mrb, b, 1, args );
    ( (Fl_Group*) context->fl_instance )->end();
  } else {
    ( (Fl_Group*) context->fl_instance )->begin();
  }
  
  return mrb_nil_value();
}

static mrb_value
mrb_fltk_group_end(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP(widget);
  
  ( (Fl_Group*) context->fl_instance )->end();
  
  return mrb_nil_value();
}

static mrb_value
mrb_fltk_group_resizable_get(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP(widget);
  
  struct RClass* mrb_fltk_class = mrb_class_get(mrb, "FLTK");
  struct RClass* mrb_fltk_widget_class = mrb_class_ptr( mrb_const_get( mrb, mrb_obj_value(mrb_fltk_class), mrb_intern_cstr(mrb, "Widget") ) );
  
  mrb_value args[1];
  
  args[0] = mrb_obj_value(
    Data_Wrap_Struct( mrb, mrb->object_class, &fltk_widget_type, (void*) ( (Fl_Group*) context->fl_instance )->resizable() )
  );
  
  return mrb_class_new_instance( mrb, 1, args, mrb_fltk_widget_class );
}

static mrb_value
mrb_fltk_group_resizable_set(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP(widget);
  
  mrb_value arg;
  mrb_get_args(mrb, "o", &arg);
  
  mrb_value arg_value_context;
  
  mrb_fltk_widget_context* arg_context = NULL;
  
  arg_value_context = mrb_iv_get( mrb, arg, mrb_intern_cstr(mrb, "context") );
  
  Data_Get_Struct( mrb, arg_value_context, &fltk_widget_type, arg_context );
  ( (Fl_Group*) context->fl_instance )->resizable( arg_context->fl_instance );
  
  return mrb_nil_value();
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// =-=- FLTK::Image -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// FLTK::Image#initialize
static mrb_value
mrb_fltk_image_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_value arg;
  mrb_get_args(mrb, "o", &arg);
  
  mrb_iv_set( mrb, self, mrb_intern_cstr(mrb, "context"), arg );
  
  return self;
}

// FLTK::Image#release
static mrb_value
mrb_fltk_image_release(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP(image);
  
  ( (Fl_Shared_Image*) context->fl_instance )->release();
  
  mrb_iv_set( mrb, self, mrb_intern_cstr(mrb, "context"), mrb_nil_value() );
  
  return mrb_nil_value();
}
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// =-=- FLTK  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// FLTK.run
static mrb_value
mrb_fltk_run(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum_value( Fl::run() );
}

// FLTK.alert
static mrb_value
mrb_fltk_alert(mrb_state *mrb, mrb_value self)
{
  mrb_value s;
  mrb_get_args(mrb, "S", &s);
  
  fl_alert( RSTRING_PTR(s) );
  
  return mrb_nil_value();
}

// FLTK.choice
static mrb_value
mrb_fltk_choice(mrb_state *mrb, mrb_value self)
{
  mrb_value args[4];
  
  mrb_get_args(mrb, "SSSS", &args[0], &args[1], &args[2], &args[3]);
  
  return fl_choice( "%s", RSTRING_PTR(args[0]), RSTRING_PTR(args[1]), RSTRING_PTR(args[2]), RSTRING_PTR(args[3]) ) ? mrb_true_value() : mrb_false_value();
}

// FLTK.ask
static mrb_value
mrb_fltk_ask(mrb_state *mrb, mrb_value self)
{
  mrb_value arg;
  
  mrb_get_args(mrb, "S", &arg);
  
  return fl_ask( "%s", RSTRING_PTR(arg) ) ? mrb_true_value() : mrb_false_value();
}

// FLTK.set_fonts
static mrb_value
mrb_fltk_set_fonts(mrb_state *mrb, mrb_value self)
{
  mrb_value s;
  mrb_get_args(mrb, "S", &s);
  
  return mrb_fixnum_value(Fl::set_fonts(RSTRING_PTR(s)));
}

// FLTK.font_name
static mrb_value
mrb_fltk_font_name(mrb_state *mrb, mrb_value self)
{
  mrb_value i;
  mrb_get_args(mrb, "i", &i);
  
  int font_type = 0;
  
  const char *name = Fl::get_font_name( (Fl::Font) mrb_fixnum(i), &font_type );
  
  return name ? mrb_str_new_cstr(mrb, name) : mrb_nil_value();
}

// FLTK.file_chooser
static mrb_value
mrb_fltk_file_chooser(mrb_state *mrb. mrb_value self)
{
  mrb_value message, pattern;
  mrb_get_args(mrb, "SS", &message, &pattern);
  
  const char *fname = Fl::file_chooser( RSTRING_PTR(message), RSTRING_PTR(pattern), NULL );
  
  return fname ? mrb_str_new_cstr(mrb, fname); : mrb_nil_value();
}

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// =-=- Widget Macro  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define DECLARE_WIDGET(name, type)                                                                                        \
static mrb_value                                                                                                          \
mrb_fltk_##name##_init(mrb_state *mrb, mrb_value self)                                                                    \
{                                                                                                                         \
  mrb_value *argv;                                                                                                        \
                                                                                                                          \
  int argc;                                                                                                               \
  mrb_get_args( mrb, "*", &argv, &argc );                                                                                 \
                                                                                                                          \
  mrb_fltk_widget_context *context = (mrb_fltk_widget_context*) malloc( sizeof(mrb_fltk_widget_context) );                \
                                                                                                                          \
  if (!context) mrb_raise(mrb, E_RUNTIME_ERROR, "can't alloc memory");                                                    \
                                                                                                                          \
  memset( context, 0, sizeof(mrb_fltk_widget_context) );                                                                  \
  context->rb_instance = self;                                                                                            \
  context->mrb = mrb;                                                                                                     \
                                                                                                                          \
  if ( arg_check("o", argc, argv) ) {                                                                                     \
    if ( strcmp( mrb_obj_classname(mrb, argv[0]), "fltk_widget" ) )                                                       \
      mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid argument");                                                               \
    mrb_iv_set( mrb, self, mrb_intern_cstr(mrb, "context"), argv[0] );                                                    \
    return self;                                                                                                          \
  } else if ( arg_check("iiii", argc, argv) ) {                                                                           \
    context->fl_instance = (Fl_Widget*) new type (                                                                        \
      (int) mrb_fixnum( argv[0] ),                                                                                        \
      (int) mrb_fixnum( argv[1] ),                                                                                        \
      (int) mrb_fixnum( argv[2] ),                                                                                        \
      (int) mrb_fixnum( argv[3] )                                                                                         \
    );                                                                                                                    \
  } else if (arg_check("iiiis", argc, argv)) {                                                                            \
    context->fl_instance = (Fl_Widget*) new type (                                                                        \
      (int) mrb_fixnum( argv[0] ),                                                                                        \
      (int) mrb_fixnum( argv[1] ),                                                                                        \
      (int) mrb_fixnum( argv[2] ),                                                                                        \
      (int) mrb_fixnum( argv[3] ),                                                                                        \
      RSTRING_PTR( argv[4] )                                                                                              \
    );                                                                                                                    \
  } else {                                                                                                                \
    mrb_raise( mrb, E_ARGUMENT_ERROR, "invalid argument" );                                                               \
  }                                                                                                                       \
                                                                                                                          \
  mrb_iv_set( mrb, self, mrb_intern_cstr(mrb, "context"), mrb_obj_value(                                                  \
    Data_Wrap_Struct( mrb, mrb->object_class, &fltk_widget_type, (void*) context) )                                       \
  );                                                                                                                      \
                                                                                                                          \
  return self;                                                                                                            \
}

DECLARE_WIDGET( widget, Fl_Widget );
DECLARE_WIDGET( browser, Fl_Browser );
DECLARE_WIDGET( select_browser, Fl_Select_Browser );
DECLARE_WIDGET( value_output, Fl_Value_Output );
DECLARE_WIDGET( input, Fl_Input );
DECLARE_WIDGET( menu_bar, Fl_Menu_Bar );
DECLARE_WIDGET( button, Fl_Button );
DECLARE_WIDGET( check_button, Fl_Check_Button );
DECLARE_WIDGET( light_button, Fl_Light_Button );
DECLARE_WIDGET( menu_button, Fl_Menu_Button );
DECLARE_WIDGET( radio_button, Fl_Radio_Button );
DECLARE_WIDGET( radio_light_button, Fl_Radio_Light_Button );
DECLARE_WIDGET( radio_round_button, Fl_Radio_Round_Button );
DECLARE_WIDGET( repeat_button, Fl_Repeat_Button );
DECLARE_WIDGET( return_button, Fl_Return_Button );
DECLARE_WIDGET( round_button, Fl_Round_Button );
DECLARE_WIDGET( toggle_button, Fl_Toggle_Button );
DECLARE_WIDGET( toggle_light_button, Fl_Toggle_Light_Button );
DECLARE_WIDGET( toggle_round_button, Fl_Toggle_Round_Button );
DECLARE_WIDGET( text_display, Fl_Text_Display );
DECLARE_WIDGET( text_editor, Fl_Text_Editor );

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// =-=- Window Macro  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define DECLARE_WINDOW(name, type)                                                                          \
static mrb_value                                                                                            \
mrb_fltk_##name##_init(mrb_state *mrb, mrb_value self)                                                      \
{                                                                                                           \
  mrb_value *argv;                                                                                          \
  int argc;                                                                                                 \
  mrb_get_args(mrb, "*", &argv, &argc);                                                                     \
                                                                                                            \
  mrb_fltk_widget_context *context = (mrb_fltk_widget_context *) malloc( sizeof(mrb_fltk_widget_context) ); \
                                                                                                            \
  if ( !context ) mrb_raise(mrb, E_RUNTIME_ERROR, "can't alloc memory");                                    \
                                                                                                            \
  memset( context, 0, sizeof(mrb_fltk_widget_context) );                                                    \
  context->rb_instance = self;                                                                              \
  context->mrb = mrb;                                                                                       \
                                                                                                            \
  if ( arg_check("iis", argc, argv) ) {                                                                     \
    context->fl_instance = (Fl_Widget *) new type (                                                         \
      (int) mrb_fixnum( argv[0] ),                                                                          \
      (int) mrb_fixnum( argv[1] ),                                                                          \
      RSTRING_PTR( argv[2] )                                                                                \
    );                                                                                                      \
  } else if ( arg_check("iiiis", argc, argv) ) {                                                            \
    context->fl_instance = (Fl_Widget *) new type (                                                         \
      (int) mrb_fixnum( argv[0] ),                                                                          \
      (int) mrb_fixnum( argv[1] ),                                                                          \
      (int) mrb_fixnum( argv[2] ),                                                                          \
      (int) mrb_fixnum( argv[3] ),                                                                          \
      RSTRING_PTR( argv[4] )                                                                                \
    );                                                                                                      \
  } else {                                                                                                  \
    mrb_raise( mrb, E_ARGUMENT_ERROR, "invalid argument" );                                                 \
  }                                                                                                         \
                                                                                                            \
  mrb_iv_set( mrb, self, mrb_intern_cstr(mrb, "context"), mrb_obj_value(                                    \
    Data_Wrap_Struct( mrb, mrb->object_class, &fltk_widget_type, (void*) context) )                         \
  );                                                                                                        \
                                                                                                            \
  return self;                                                                                              \
}

DECLARE_WINDOW( window, Fl_Window );
DECLARE_WINDOW( double_window, Fl_Double_Window );

// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// =-=- Hidden Object Macro  -=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// TODO: Has ambiguous argument names... also what is this?
#define DECLARE_HIDDEN_OBJECT(x, y)                                       \
static mrb_value                                                          \
mrb_fltk_##x##_init(mrb_state *mrb, mrb_value self)                       \
{                                                                         \
  mrb_value arg = mrb_nil_value();                                        \
  mrb_get_args(mrb, "|o", &arg);                                          \
                                                                          \
  if ( !mrb_nil_p(arg) ) {                                                \
    if ( strcmp(mrb_obj_classname(mrb, arg), "fltk_" # y) )               \
      mrb_raise( mrb, E_RUNTIME_ERROR, "can't alloc fltk::" # x );        \
                                                                          \
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "context"), arg);          \
  } else mrb_raise(mrb, E_RUNTIME_ERROR, "can't alloc fltk::" # x);       \
                                                                          \
  return self;                                                            \
}

DECLARE_HIDDEN_OBJECT( Fl_Shared_Image, Fl_Image );
DECLARE_HIDDEN_OBJECT( Fl_Group, Fl_Widget );
DECLARE_HIDDEN_OBJECT( Fl_Box, Fl_Widget );





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

#define INHERIT_GROUP(name) \
  mrb_define_method( mrb, mrb_fltk_class##name, "begin", mrb_fltk_group_begin, ARGS_NONE() );              \
  mrb_define_method( mrb, mrb_fltk_class##name, "end", mrb_fltk_group_end, ARGS_NONE() );                  \
  mrb_define_method( mrb, mrb_fltk_class##name, "resizable", mrb_fltk_group_resizable_get, ARGS_NONE() );  \
  mrb_define_method( mrb, mrb_fltk_class##name, "resizable=", mrb_fltk_group_resizable_set, ARGS_REQ(1) ); \
  ARENA_RESTORE;

#define DEFINE_FIXNUM_PROP_READONLY(x, y, z)                                                          \
  mrb_define_method(mrb, mrb_fltk_class ## x, # z, [] (mrb_state *mrb, mrb_value self) -> mrb_value { \
    CONTEXT_SETUP(y);                                                                                 \
    return mrb_fixnum_value( ( (x *) context->fl_instance )->z() );                                   \
  }, ARGS_NONE() );

#define DEFINE_FIXNUM_PROP(x, y, z)                                                                       \
  mrb_define_method(mrb, mrb_fltk_class ## x, # z, [] (mrb_state* mrb, mrb_value self) -> mrb_value {     \
    CONTEXT_SETUP(y);                                                                                     \
    return mrb_fixnum_value( ( (x *) context->fl_instance )->z() );                                       \
  }, ARGS_NONE());                                                                                        \
  mrb_define_method(mrb, mrb_fltk_class ## x, # z "=", [] (mrb_state* mrb, mrb_value self) -> mrb_value { \
    CONTEXT_SETUP(y);                                                                                     \
    mrb_value vv;                                                                                         \
    mrb_get_args(mrb, "i", &vv);                                                                          \
    ( (x *) context->fl_instance )->z( mrb_fixnum(vv) );                                                  \
    return mrb_nil_value();                                                                               \
  }, ARGS_NONE());                                                                                        \
  ARENA_RESTORE;

#define DEFINE_STR_PROP(x, y, z)                                                                          \
  mrb_define_method(mrb, mrb_fltk_class ## x, # z, [] (mrb_state* mrb, mrb_value self) -> mrb_value {     \
    CONTEXT_SETUP(y);                                                                                     \
    const char* vv = ( (x *) context->fl_instance )->z();                                                 \
    return vv ? mrb_str_new_cstr(mrb, vv) : mrb_nil_value();                                              \
  }, ARGS_NONE());                                                                                        \
  mrb_define_method(mrb, mrb_fltk_class ## x, # z "=", [] (mrb_state* mrb, mrb_value self) -> mrb_value { \
    CONTEXT_SETUP(y);                                                                                     \
    mrb_value vv;                                                                                         \
    mrb_get_args(mrb, "S", &vv);                                                                          \
    ((x*) context->fl_instance)->z(RSTRING_PTR(vv));                                                      \
    return mrb_nil_value();                                                                               \
  }, ARGS_NONE());                                                                                        \
  ARENA_RESTORE;

#define INHERIT_INPUT_VALUE(x)                                                                  \
  mrb_define_method(mrb, mrb_fltk_class ## x, "value", mrb_fltk_input_value_get, ARGS_NONE());  \
  mrb_define_method(mrb, mrb_fltk_class ## x, "value=", mrb_fltk_input_value_set, ARGS_NONE()); \
  ARENA_RESTORE;

#define DEFINE_CLASS(x, y)                                                                                      \
  struct RClass* mrb_fltk_class ## x = mrb_define_class_under( mrb, mrb_fltk_class, # x, mrb_fltk_class ## y ); \
  mrb_define_method( mrb, mrb_fltk_class ## x, "initialize", mrb_fltk_##x##_init, ARGS_ANY() );                 \
  ARENA_RESTORE;

void
mrb_mruby_fltk_gem_init(mrb_state* mrb)
{
  
  // =-=- FLTK  -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  ARENA_SAVE;
  struct RClass* mrb_fltk_class = mrb_define_module(mrb, "FLTK");
  
  mrb_define_module_function( mrb, mrb_fltk_class, "run", mrb_fltk_run, ARGS_NONE() );
  mrb_define_module_function( mrb, mrb_fltk_class, "alert", mrb_fltk_alert, ARGS_REQ(1) );
  mrb_define_module_function( mrb, mrb_fltk_class, "ask", mrb_fltk_ask, ARGS_REQ(1) );
  mrb_define_module_function( mrb, mrb_fltk_class, "choice", mrb_fltk_choice, ARGS_REQ(4) );
  mrb_define_module_function( mrb, mrb_fltk_class, "set_fonts", mrb_fltk_set_fonts, ARGS_REQ(1) );
  mrb_define_module_function( mrb, mrb_fltk_class, "font_name", mrb_fltk_font_name, ARGS_REQ(1) );
  mrb_define_module_function( mrb, mrb_fltk_class, "file_chooser", mrb_fltk_file_chooser, ARGS_REQ(2) );
  ARENA_RESTORE;
  
  // =-=- FLTK::Image -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
  struct RClass* mrb_fltk_image_class = mrb_define_class_under(mrb, mrb_fltk_class, "Image", mrb->object_class);
  
  mrb_define_method( mrb, mrb_fltk_image_class, "initialize", mrb_fltk_image_initialize, ARGS_NONE() );
  
  DEFINE_FIXNUM_PROP_READONLY(Image, Image, w);
  DEFINE_FIXNUM_PROP_READONLY(Image, Image, h);
  DEFINE_FIXNUM_PROP_READONLY(Image, Image, d);
  DEFINE_FIXNUM_PROP_READONLY(Image, Image, ld);
  mrb_define_module_function(mrb, mrb_fltk_image_class, "release", [] (mrb_state* mrb, mrb_value self) -> mrb_value {
    CONTEXT_SETUP(Image);
    ((Fl_Shared_Image*) context->fl_instance)->release();
    mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "context"), mrb_nil_value());
    return mrb_nil_value();
  }, ARGS_REQ(1));
  mrb_define_module_function(mrb, mrb_fltk_image_class, "copy", [] (mrb_state* mrb, mrb_value self) -> mrb_value {
    CONTEXT_SETUP(Image);
    mrb_value width, height;
    mrb_get_args(mrb, "ii", &width, &height);
    Fl_Image* image = context->fl_instance->copy(mrb_fixnum(width), mrb_fixnum(height));
    if (!image) return mrb_nil_value();
    mrb_fltk_image_context* image_context =
      (mrb_fltk_image_context*) malloc(sizeof(mrb_fltk_image_context));
    if (!image_context) mrb_raise(mrb, E_RUNTIME_ERROR, "can't alloc memory");
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
  }, ARGS_REQ(1));
  
  
  
  
  DEFINE_CLASS(SharedImage, Image);
  mrb_define_module_function(mrb, mrb_fltk_shared_image_class, "get", [] (mrb_state* mrb, mrb_value self) -> mrb_value {
    mrb_value filename;
    mrb_get_args(mrb, "S", &filename);
    Fl_Image* image = (Fl_Image*) Fl_Shared_Image::get(RSTRING_PTR(filename));
    if (!image) return mrb_nil_value();
    mrb_fltk_image_context* image_context =
      (mrb_fltk_image_context*) malloc(sizeof(mrb_fltk_image_context));
    if (!image_context) mrb_raise(mrb, E_RUNTIME_ERROR, "can't alloc memory");
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
  }, ARGS_REQ(1));
  ARENA_RESTORE;

  struct RClass* mrb_fltk_widget_class = mrb_define_class_under(mrb, mrb_fltk_class, "Widget", mrb->object_class);
  mrb_define_method(mrb, mrb_fltk_widget_class, "initialize", mrb_fltk_widget_init, ARGS_ANY());
  mrb_define_method(mrb, mrb_fltk_widget_class, "redraw", [] (mrb_state* mrb, mrb_value self) -> mrb_value {
    CONTEXT_SETUP(Widget);
    context->fl_instance->redraw();
    return mrb_nil_value();
  }, ARGS_NONE());
  mrb_define_method(mrb, mrb_fltk_widget_class, "show", mrb_fltk_widget_show, ARGS_NONE());
  mrb_define_method(mrb, mrb_fltk_widget_class, "hide", mrb_fltk_widget_hide, ARGS_NONE());
  DEFINE_FIXNUM_PROP(Widget, Widget, x);
  DEFINE_FIXNUM_PROP(Widget, Widget, y);
  DEFINE_FIXNUM_PROP(Widget, Widget, w);
  DEFINE_FIXNUM_PROP(Widget, Widget, h);
  DEFINE_FIXNUM_PROP(Widget, Widget, labelfont);
  DEFINE_FIXNUM_PROP(Widget, Widget, labelsize);
  DEFINE_STR_PROP(Widget, Widget, label);
  mrb_define_method(mrb, mrb_fltk_widget_class, "box", mrb_fltk_widget_box_get, ARGS_NONE());
  mrb_define_method(mrb, mrb_fltk_widget_class, "box=", mrb_fltk_widget_box_set, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_fltk_widget_class, "image", mrb_fltk_widget_image_get, ARGS_NONE());
  mrb_define_method(mrb, mrb_fltk_widget_class, "image=", mrb_fltk_widget_image_set, ARGS_REQ(1));
  mrb_define_method(mrb, mrb_fltk_widget_class, "visible?", mrb_fltk_widget_visible, ARGS_NONE());
  mrb_define_method(mrb, mrb_fltk_widget_class, "callback", mrb_fltk_widget_callback, ARGS_OPT(1));
  ARENA_RESTORE;

  DEFINE_CLASS(ValueOutput, Widget);

  DEFINE_CLASS(Button, Widget);
  DEFINE_CLASS(CheckButton, Button);
  DEFINE_CLASS(LightButton, Button);
  DEFINE_CLASS(MenuButton, Button);
  DEFINE_CLASS(RadioButton, Button);
  DEFINE_CLASS(RadioLightButton, Button);
  DEFINE_CLASS(RadioRoundButton, Button);
  DEFINE_CLASS(RepeatButton, Button);
  DEFINE_CLASS(ReturnButton, Button);
  DEFINE_CLASS(RoundButton, Button);
  DEFINE_CLASS(ToggleButton, Button);
  DEFINE_CLASS(ToggleLightButton, Button);
  DEFINE_CLASS(ToggleRoundButton, Button);

  DEFINE_CLASS(Input, Widget);
  DEFINE_STR_PROP(Input, Widget, value);

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
  DEFINE_FIXNUM_PROP(Browser, Widget, value);
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

  DEFINE_CLASS(Box, Widget);
  DEFINE_CLASS(NoBox, Box);
  DEFINE_CLASS(FlatBox, Box);
  DEFINE_CLASS(UpBox, Box);
  DEFINE_CLASS(DownBox, Box);
  DEFINE_CLASS(ThinUpBox, Box);
  DEFINE_CLASS(ThinDownBox, Box);
  DEFINE_CLASS(EngravedBox, Box);
  DEFINE_CLASS(EmbossedBox, Box);
  DEFINE_CLASS(BorderBox, Box);
  DEFINE_CLASS(ShadowBox, Box);
  DEFINE_CLASS(RoundedBox, Box);
  DEFINE_CLASS(RShadowBox, Box);
  DEFINE_CLASS(RFlatBox, Box);
  DEFINE_CLASS(RoundUpBox, Box);
  DEFINE_CLASS(RoundDownBox, Box);
  DEFINE_CLASS(DiamondUpBox, Box);
  DEFINE_CLASS(DiamondDownBox, Box);
  DEFINE_CLASS(OvalBox, Box);
  DEFINE_CLASS(OShadowBox, Box);
  DEFINE_CLASS(OFlatBox, Box);
  DEFINE_CLASS(PlasticUpBox, Box);
  DEFINE_CLASS(PlasticDownBox, Box);
  DEFINE_CLASS(PlasticThinUpBox, Box);
  DEFINE_CLASS(PlasticThinDownBox, Box);
  DEFINE_CLASS(PlasticRoundUpBox, Box);
  DEFINE_CLASS(PlasticRoundDownBox, Box);
  DEFINE_CLASS(ClassicUpBox, Box);
  DEFINE_CLASS(ClassicDownBox, Box);
  DEFINE_CLASS(ClassicThinUpBox, Box);
  DEFINE_CLASS(ClassicThinDownBox, Box);
  DEFINE_CLASS(ClassicRoundUpBox, Box);
  DEFINE_CLASS(ClassicRoundDownBox, Box);
  DEFINE_CLASS(BorderFrame, Box);
  DEFINE_CLASS(UpFrame, Box);
  DEFINE_CLASS(DownFrame, Box);
  DEFINE_CLASS(ThinUpFrame, Box);
  DEFINE_CLASS(ThinDownFrame, Box);
  DEFINE_CLASS(EngravedFrame, Box);
  DEFINE_CLASS(EmbossedFrame, Box);
  DEFINE_CLASS(ShadowFrame, Box);
  DEFINE_CLASS(RoundedFrame, Box);
  DEFINE_CLASS(OvalFrame, Box);
  DEFINE_CLASS(PlasticUpFrame, Box);
  DEFINE_CLASS(PlasticDownFrame, Box);
  DEFINE_CLASS(ClassicUpFrame, Box);
  DEFINE_CLASS(ClassicDownFrame, Box);
  DEFINE_CLASS(ClassicThinUpFrame, Box);
  DEFINE_CLASS(ClassicThinDownFrame, Box);

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
  DEFINE_FIXNUM_PROP_READONLY(TextBuffer, TextBuffer, length);
  DEFINE_STR_PROP(TextBuffer, TextBuffer, text);
  ARENA_RESTORE;

  fltk3::register_images();
}

void
mrb_mruby_fltk3_gem_final(mrb_state* mrb)
{
}

}
 