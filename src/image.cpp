// =-=- FLTK::Image -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// FLTK::Image#initialize(width, height, depth)
// FLTK::Image#initialize(context) # For internal use
static mrb_value
mrb_fltk_image_initialize_method(mrb_state *mrb, mrb_value self)
{
  mrb_value *argv;
  int argc;
  
  mrb_get_args( mrb, "*", &argv, &argc );
  
  if ( mrb_fltk_arg_check( "o", argc, argv ) ) { // Is the context to use
    if ( strcmp( mrb_obj_classname( mrb, argv[0] ), "fltk_image" ) ) mrb_raise( mrb, E_ARGUMENT_ERROR, "invalid argument" );
    
    mrb_iv_set( mrb, self, mrb_intern_cstr(mrb, "context"), argv[0] ); // Is width, height, and depth
  } else if ( mrb_fltk_arg_check( "iii", argc, argv ) ) {
    CONTEXT_CREATE( image, context );
    context->fl_instance = new Fl_Image ( (int) mrb_fixnum( argv[0] ), (int) mrb_fixnum( argv[1] ), (int) mrb_fixnum( argv[2] ) );
    CONTEXT_SET_INSTANCE_VARIABLE( image, context );
  }
  
  return self;
}

// FLTK::Image#copy(width, height)
static mrb_value
mrb_fltk_image_copy_method(mrb_state *mrb, mrb_value self)
{
  mrb_value width, height;
  mrb_get_args( mrb, "ii", &width, &height );
  
  CONTEXT_SETUP( image );
  
  Fl_Image *image = context->fl_instance->copy( (int) mrb_fixnum( width ), (int) mrb_fixnum( height ) );
  
  if ( !image ) return mrb_nil_value(); // TODO: Raise an error!
  
  CONTEXT_CREATE( image, copy_context );
  copy_context->fl_instance = image;
  
  mrb_value args[1];
  
  struct RClass* mrb_fltk_class = mrb_class_get(mrb, "FLTK");
  struct RClass* mrb_fltk_image_class = mrb_class_ptr( mrb_const_get( mrb, mrb_obj_value(mrb_fltk_class), mrb_intern_cstr(mrb, "Image") ) );
  
  args[0] = CONTEXT_WRAP( image, copy_context );
  
  return mrb_class_new_instance( mrb, 1, args, mrb_fltk_image_class );
}

// =-=- FLTK::SharedImage -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

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
