#include <stdlib.h>

#include <mruby.h>
#include <mruby/variable.h>
#include <mruby/data.h>
#include <mruby/string.h>

#include <Fl/Fl_Widget.h>

#include "macros.h"
#include "helpers.h"
#include "widget.h"
#include "group.h"

// FLTK::Widget#align
// FLTK::Widget#align=(value)
IMPLEMENT_FIXNUM_ATTRIBUTE_ACCESSOR( widget, align, Fl_Widget, align );

// For FLTK::Widget#callback
typedef struct {
  mrb_state *mrb;
  mrb_value self;
} mrb_fltk_widget_callback_context;

// For FLTK::Widget#callback
void mrb_fltk_widget_callback_function( Fl_Widget *fl_widget, void *data ) {
  mrb_fltk_widget_callback_context *context = (mrb_fltk_widget_callback_context *)data;
  mrb_state *mrb = context->mrb;
  mrb_value self = context->self;

  mrb_value block = mrb_iv_get( mrb, self, mrb_intern_cstr( mrb, "callback" ) );

  mrb_funcall_with_block( mrb, self, mrb_intern_cstr( mrb, "instance_eval" ), 0, NULL, block );
}

// FLTK::Widget#callback
// Gets or sets the current callback function for the widget.
mrb_value mrb_fltk_widget_callback_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_widget, Fl_Widget, self );

  mrb_value block = mrb_nil_value();

  mrb_get_args( mrb, "&", &block );

  if( !mrb_nil_p( block ) ) {
    // TODO: Free the existing context struct if it already exists?
    mrb_iv_set( mrb, self, mrb_intern_cstr( mrb, "callback" ), block );

    mrb_fltk_widget_callback_context *context = (mrb_fltk_widget_callback_context *)malloc( sizeof( mrb_fltk_widget_callback_context ) );
    context->mrb = mrb;
    context->self = self;

    fl_widget->callback( mrb_fltk_widget_callback_function, context );
  } else {
    block = mrb_iv_get( mrb, self, mrb_intern_cstr( mrb, "callback" ) );
  }

  return block;
}

// FLTK::Widget#height
IMPLEMENT_FIXNUM_ATTRIBUTE_READER( widget, height, Fl_Widget, h );

// FLTK::Widget#image
// Gets the image that is used as part of the widget label.
// mrb_value
// mrb_fltk_widget_image_get_method( mrb_state *mrb, mrb_value self ) {
//   CONTEXT_SETUP( widget );
//
//   struct RClass *mrb_fltk_class, *mrb_fltk_image_class;
//
//   mrb_fltk_class = mrb_class_get( mrb, "FLTK" );
//   mrb_fltk_image_class = mrb_class_ptr( mrb_const_get( mrb, mrb_obj_value( mrb_fltk_class ), mrb_intern_cstr( mrb, "Image" ) ) );
//
//   mrb_value args[1];
//   args[0] = mrb_obj_value(
//     Data_Wrap_Struct( mrb, mrb->object_class, &fltk_image_type, (void *)context->fl_instance->image() ) );
//
//   return mrb_class_new_instance( mrb, 1, args, mrb_fltk_image_class );
// }

// FLTK::Widget#image=(image)
// Sets the image to use as part of the widget label. Must be a FLTK::Image
// mrb_value
// mrb_fltk_widget_image_set_method( mrb_state *mrb, mrb_value self ) { // TODO: Must be a FLTK::Image
//   CONTEXT_SETUP( widget );
//
//   mrb_value image;
//   mrb_get_args( mrb, "o", &image );
//
//   if( !mrb_nil_p( image ) ) {
//     mrb_value image_value_context;
//     mrb_fltk_image_context *image_context;
//
//     image_value_context = mrb_iv_get( mrb, image, mrb_intern_cstr( mrb, "context" ) );
//     Data_Get_Struct( mrb, image_value_context, &fltk_image_type, image_context );
//
//     context->fl_instance->image( (Fl_Image *)image_context->fl_instance );
//   } else {
//     context->fl_instance->image( NULL ); // TODO Raise Error!
//   }
//
//   return mrb_nil_value();
// }

// FLTK::Widget#hide
// Makes a widget invisible.
mrb_value mrb_fltk_widget_hide_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_widget, Fl_Widget, self );

  fl_widget->hide();

  return self;
}

// FLTK::Widget#label
// FLTK::Widget#label=(value)
IMPLEMENT_STRING_ATTRIBUTE_ACCESSOR( widget, label, Fl_Widget, label );

// FLTK::Widget#label_font
// FLTK::Widget#label_font=(value)
IMPLEMENT_FIXNUM_ATTRIBUTE_ACCESSOR( widget, label_font, Fl_Widget, labelfont );

// FLTK::Widget#label_size
// FLTK::Widget#label_size=(value)
IMPLEMENT_FIXNUM_ATTRIBUTE_ACCESSOR( widget, label_size, Fl_Widget, labelsize );

// FLTK::Widget#parent
// Returns the parent widget
mrb_value mrb_fltk_widget_parent_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_widget, Fl_Widget, self ); // TODO: Needed?

  return mrb_iv_get( mrb, self, mrb_intern_cstr( mrb, "parent" ) );
}

// FLTK::Widget#redraw
mrb_value mrb_fltk_widget_redraw_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_widget, Fl_Widget, self );

  fl_widget->redraw();

  return self;
}

// FLTK::Widget#show
// Makes a widget visible.
mrb_value mrb_fltk_widget_show_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_widget, Fl_Widget, self );

  fl_widget->show();

  return self;
}

// FLTK::Widget#take_focus
// Gives the widget the keyboard focus.
mrb_value mrb_fltk_widget_take_focus_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_widget, Fl_Widget, self );

  fl_widget->take_focus();

  return self;
}

// FLTK::Widget#visible?
// Returns whether a widget is visible.
mrb_value mrb_fltk_widget_visible_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_widget, Fl_Widget, self );

  return fl_widget->visible() ? mrb_true_value() : mrb_false_value();
}

// FLTK::Widget#when
// Returns the conditions under which the callback is called.
// FLTK::Widget#when=(value)
// Sets the flags used to decide when a callback is called.
IMPLEMENT_FIXNUM_ATTRIBUTE_ACCESSOR( widget, when, Fl_Widget, when );

// FLTK::Widget#width
IMPLEMENT_FIXNUM_ATTRIBUTE_READER( widget, width, Fl_Widget, w );

// FLTK::Widget#x
IMPLEMENT_FIXNUM_ATTRIBUTE_READER( widget, x, Fl_Widget, x );

// FLTK::Widget#y
IMPLEMENT_FIXNUM_ATTRIBUTE_READER( widget, y, Fl_Widget, y );

void mrb_fltk_widget_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  struct RClass *mrb_fltk_module = mrb_class_get( mrb, "FLTK" );

  DEFINE_CLASS( widget, Widget, mrb->object_class );

  DEFINE_INSTANCE_METHOD_ACCESSOR( widget, align );
  // DEFINE_FIXNUM_ATTRIBUTE_ACCESSOR( widget, box, Fl_Widget, box );
  DEFINE_INSTANCE_METHOD( widget, callback, ARGS_OPT( 1 ) );
  DEFINE_INSTANCE_METHOD_GETTER( widget, height );
  DEFINE_INSTANCE_METHOD( widget, hide, ARGS_NONE() );
  DEFINE_INSTANCE_METHOD_ACCESSOR( widget, label );
  DEFINE_INSTANCE_METHOD_ACCESSOR( widget, label_font );
  DEFINE_INSTANCE_METHOD_ACCESSOR( widget, label_size );
  // DEFINE_FIXNUM_ATTRIBUTE_ACCESSOR( widget, label_size, Fl_Widget, labelsize );
  DEFINE_INSTANCE_METHOD( widget, parent, ARGS_NONE() );
  DEFINE_INSTANCE_METHOD( widget, redraw, ARGS_NONE() );
  DEFINE_INSTANCE_METHOD( widget, show, ARGS_NONE() );
  DEFINE_INSTANCE_METHOD( widget, take_focus, ARGS_NONE() );
  mrb_define_method( mrb, mrb_fltk_widget, "visible?", mrb_fltk_widget_visible_instance_method, ARGS_NONE() ); // TODO: DEFINE_INSTANCE_QUERY_METHOD macro
  DEFINE_INSTANCE_METHOD_ACCESSOR( widget, when );
  DEFINE_INSTANCE_METHOD_GETTER( widget, width );
  DEFINE_INSTANCE_METHOD_GETTER( widget, x );
  DEFINE_INSTANCE_METHOD_GETTER( widget, y );

  // mrb_define_method( mrb, mrb_fltk_widget_class, "image", mrb_fltk_widget_image_getter_instance_method, ARGS_NONE() );
  // mrb_define_method( mrb, mrb_fltk_widget_class, "image=", mrb_fltk_widget_image_setter_instance_method, ARGS_REQ( 1 ) );

  ARENA_RESTORE;
}
