DECLARE_HIDDEN_OBJECT( shared_image, image );

static mrb_value
mrb_fltk_shared_image_get_method(mrb_state *mrb, mrb_value self)
{
  mrb_value filename;
  mrb_get_args(mrb, "S", &filename);
  
  Fl_Image *image = (Fl_Image *) Fl_Shared_Image::get( RSTRING_PTR(filename) );
  
  if ( !image ) return mrb_nil_value();
  
  mrb_fltk_image_context *image_context = (mrb_fltk_image_context *) malloc( sizeof(mrb_fltk_image_context) );
  
  if ( !image_context ) mrb_raise(mrb, E_RUNTIME_ERROR, "can't alloc memory");
  
  memset( image_context, 0, sizeof(mrb_fltk_image_context) );
  image_context->rb_instance = self;
  image_context->fl_instance = image;
  
  mrb_value args[1];
  struct RClass *mrb_fltk_class = mrb_class_get( mrb, "FLTK" );
  struct RClass *mrb_fltk_image_class = mrb_class_ptr( mrb_const_get( mrb, mrb_obj_value(mrb_fltk_class), mrb_intern_cstr(mrb, "Image") ) );
  
  args[0] = mrb_obj_value(
    Data_Wrap_Struct( mrb, mrb->object_class, &fltk_image_type, (void *) image_context )
  );
  
  return mrb_class_new_instance(mrb, 1, args, mrb_fltk_image_class);
}
