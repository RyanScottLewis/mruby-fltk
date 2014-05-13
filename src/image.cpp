// FLTK::Image#initialize(width, height, depth)
// FLTK::Image#initialize(context) # For internal use
static mrb_value
mrb_fltk_image_initialize_method( mrb_state *mrb, mrb_value self ) {
  mrb_value *argv;
  int argc;

  mrb_get_args( mrb, "*", &argv, &argc );

  if( mrb_fltk_arg_check( "o", argc, argv ) ) { // Is the context to use
    if( strcmp( mrb_obj_classname( mrb, argv[0] ), "fltk_image" ) )
      mrb_raise( mrb, E_ARGUMENT_ERROR, "invalid argument" );

    mrb_iv_set( mrb, self, mrb_intern_cstr( mrb, "context" ), argv[0] ); // Is width, height, and depth
  } else if( mrb_fltk_arg_check( "iii", argc, argv ) ) {
    CONTEXT_CREATE( image, context );
    context->fl_instance = new Fl_Image( (int)mrb_fixnum( argv[0] ), (int)mrb_fixnum( argv[1] ), (int)mrb_fixnum( argv[2] ) );
    CONTEXT_SET_INSTANCE_VARIABLE( image, context );
  }

  return self;
}

// FLTK::Image#copy(width, height)
static mrb_value
mrb_fltk_image_copy_method( mrb_state *mrb, mrb_value self ) {
  mrb_value width, height;
  mrb_get_args( mrb, "ii", &width, &height );

  CONTEXT_SETUP( image );

  Fl_Image *image = context->fl_instance->copy( (int)mrb_fixnum( width ), (int)mrb_fixnum( height ) );

  if( !image )
    return mrb_nil_value(); // TODO: Raise an error!

  CONTEXT_CREATE( image, copy_context );
  copy_context->fl_instance = image;

  mrb_value args[1];

  struct RClass *mrb_fltk_class = mrb_class_get( mrb, "FLTK" );
  struct RClass *mrb_fltk_image_class = mrb_class_ptr( mrb_const_get( mrb, mrb_obj_value( mrb_fltk_class ), mrb_intern_cstr( mrb, "Image" ) ) );

  args[0] = CONTEXT_WRAP( image, copy_context );

  return mrb_class_new_instance( mrb, 1, args, mrb_fltk_image_class );
}

void
mrb_fltk_image_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  DEFINE_CLASS( image, "Image", mrb->object_class );

  DEFINE_INSTANCE_METHOD( image, initialize, ARGS_REQ( 3 ) );
  DEFINE_INSTANCE_METHOD( image, copy, ( MRB_ARGS_REQ( 1 ) | MRB_ARGS_REQ( 3 ) ) );

  DEFINE_FIXNUM_ATTRIBUTE_READER( image, width, Fl_Image, w );
  DEFINE_FIXNUM_ATTRIBUTE_READER( image, height, Fl_Image, h );
  DEFINE_FIXNUM_ATTRIBUTE_READER( image, depth, Fl_Image, d );
  DEFINE_FIXNUM_ATTRIBUTE_READER( image, line_data_size, Fl_Image, ld );

  ARENA_RESTORE;
}
