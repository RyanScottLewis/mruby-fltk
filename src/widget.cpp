#include <mruby.h>
#include <mruby/variable.h>
#include <mruby/data.h>

#include <Fl/Fl_Widget.h>

#include "macros.h"
#include "helpers.h"

IMPLEMENT_FIXNUM_ATTRIBUTE_READER( widget, height, Fl_Widget, h );
IMPLEMENT_FIXNUM_ATTRIBUTE_READER( widget, width, Fl_Widget, w );
IMPLEMENT_FIXNUM_ATTRIBUTE_READER( widget, x, Fl_Widget, x );
IMPLEMENT_FIXNUM_ATTRIBUTE_READER( widget, y, Fl_Widget, y );
IMPLEMENT_STRING_ATTRIBUTE_READER( widget, label, Fl_Widget, label );

// void
// _mrb_fltk_widget_callback( Fl_Widget *v, void *data ) {
//   mrb_value args[2];
//
//   mrb_fltk_widget_context *context = (mrb_fltk_widget_context *)data;
//   mrb_state *mrb = context->mrb;
//   mrb_value proc = mrb_iv_get( mrb, context->rb_instance, mrb_intern_cstr( mrb, "callback" ) );
//   mrb_value value = mrb_iv_get( mrb, context->rb_instance, mrb_intern_cstr( mrb, "value" ) );
//   args[0] = context->rb_instance;
//   args[1] = value;
//
//   mrb_yield_argv( mrb, proc, 2, args );
// }

// FLTK::Widget#callback
// Gets or sets the current callback function for the widget.
// mrb_value
// mrb_fltk_widget_callback_method( mrb_state *mrb, mrb_value self ) { // TODO: Make this more Ruby-ish! And the variables are ambiguous
//   GET_DATA( fl_widget, Fl_Widget );
//
//   mrb_value b = mrb_nil_value();
//   mrb_value v = mrb_nil_value();
//
//   mrb_get_args( mrb, "&|o", &b, &v );
//
//   if( !mrb_nil_p( b ) ) {
//     mrb_iv_set( mrb, self, mrb_intern_cstr( mrb, "callback" ), b );
//     mrb_iv_set( mrb, self, mrb_intern_cstr( mrb, "value" ), v );
//
//     fl_widget->callback( _mrb_fltk_widget_callback, context );
//   }
//   return mrb_nil_value();
// }

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

// FLTK::Widget#redraw
mrb_value mrb_fltk_widget_redraw_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_widget, Fl_Widget );

  fl_widget->redraw();

  return mrb_nil_value();
}

// FLTK::Widget#show
// Makes a widget visible.
mrb_value mrb_fltk_widget_show_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_widget, Fl_Widget );

  fl_widget->show();

  return mrb_nil_value();
}

// FLTK::Widget#hide
// Makes a widget invisible.
mrb_value mrb_fltk_widget_hide_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_widget, Fl_Widget );

  fl_widget->hide();

  return mrb_nil_value();
}

// FLTK::Widget#visible?
// Returns whether a widget is visible.
mrb_value mrb_fltk_widget_visible_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_widget, Fl_Widget );

  return fl_widget->visible() ? mrb_true_value() : mrb_false_value();
}

void mrb_fltk_widget_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  struct RClass *mrb_fltk_module = mrb_class_get( mrb, "FLTK" );

  DEFINE_CLASS( widget, Widget, mrb->object_class );

  // DEFINE_INSTANCE_METHOD( widget, callback, ARGS_OPT( 1 ) );
  DEFINE_INSTANCE_METHOD( widget, redraw, ARGS_NONE() );
  DEFINE_INSTANCE_METHOD( widget, show, ARGS_NONE() );
  DEFINE_INSTANCE_METHOD( widget, hide, ARGS_NONE() );

  DEFINE_INSTANCE_METHOD_GETTER( widget, height );
  DEFINE_INSTANCE_METHOD_GETTER( widget, width );
  DEFINE_INSTANCE_METHOD_GETTER( widget, x );
  DEFINE_INSTANCE_METHOD_GETTER( widget, y );
  DEFINE_INSTANCE_METHOD_GETTER( widget, label );

  // DEFINE_FIXNUM_ATTRIBUTE_ACCESSOR( widget, box, Fl_Widget, box );
  // DEFINE_FIXNUM_ATTRIBUTE_ACCESSOR( widget, label_font, Fl_Widget, labelfont );
  // DEFINE_FIXNUM_ATTRIBUTE_ACCESSOR( widget, label_size, Fl_Widget, labelsize );

  // mrb_define_method( mrb, mrb_fltk_widget_class, "image", mrb_fltk_widget_image_getter_instance_method, ARGS_NONE() );
  // mrb_define_method( mrb, mrb_fltk_widget_class, "image=", mrb_fltk_widget_image_setter_instance_method, ARGS_REQ( 1 ) );
  mrb_define_method( mrb, mrb_fltk_widget, "visible?", mrb_fltk_widget_visible_instance_method, ARGS_NONE() ); // TODO: DEFINE_INSTANCE_QUERY_METHOD macro

  ARENA_RESTORE;
}
