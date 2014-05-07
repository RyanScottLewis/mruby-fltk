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
mrb_fltk_widget_callback_method(mrb_state *mrb, mrb_value self)
{ // TODO: Make this more Ruby-ish! And the variables are ambiguous
  CONTEXT_SETUP( widget );
  
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

// FLTK::Widget#hide
// Makes a widget invisible.
static mrb_value
mrb_fltk_widget_hide_method(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP( widget );
  context->fl_instance->hide();
  
  return mrb_nil_value();
}

// FLTK::Widget#image
// Gets the image that is used as part of the widget label.
static mrb_value
mrb_fltk_widget_image_get_method(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP( widget );
  
  struct RClass *mrb_fltk_class, *mrb_fltk_image_class;
  
  mrb_fltk_class = mrb_class_get( mrb, "FLTK" );
  mrb_fltk_image_class = mrb_class_ptr( mrb_const_get( mrb, mrb_obj_value(mrb_fltk_class), mrb_intern_cstr(mrb, "Image") ) );
  
  mrb_value args[1];
  args[0] = mrb_obj_value(
    Data_Wrap_Struct(mrb, mrb->object_class, &fltk_image_type, (void*) context->fl_instance->image() )
  );
  
  return mrb_class_new_instance( mrb, 1, args, mrb_fltk_image_class );
}

// FLTK::Widget#image=(image)
// Sets the image to use as part of the widget label. Must be a FLTK::Image
static mrb_value
mrb_fltk_widget_image_set_method(mrb_state *mrb, mrb_value self)
{ // TODO: Must be a FLTK::Image
  CONTEXT_SETUP( widget );
  
  mrb_value image;
  mrb_get_args( mrb, "o", &image );
  
  if ( !mrb_nil_p(image) ) {
    mrb_value image_value_context;
    mrb_fltk_image_context *image_context;
    
    image_value_context = mrb_iv_get( mrb, image, mrb_intern_cstr(mrb, "context") );
    Data_Get_Struct( mrb, image_value_context, &fltk_image_type, image_context );
    
    context->fl_instance->image( (Fl_Image *) image_context->fl_instance );
  } else {
    context->fl_instance->image( NULL ); // TODO Raise Error!
  }
  
  return mrb_nil_value();
}

// FLTK::Widget#redraw
static mrb_value
mrb_fltk_widget_redraw_method(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP( widget );
  context->fl_instance->redraw();
  
  return mrb_nil_value();
}

// FLTK::Widget#show
// Makes a widget visible.
static mrb_value
mrb_fltk_widget_show_method(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP( widget );
  context->fl_instance->show();
  
  return mrb_nil_value();
}

// FLTK::Widget#visible?
// Returns whether a widget is visible.
static mrb_value
mrb_fltk_widget_visible_method(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP( widget );
  
  return context->fl_instance->visible() ? mrb_true_value() : mrb_false_value();
}
