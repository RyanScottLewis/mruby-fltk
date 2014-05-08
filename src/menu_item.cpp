// FLTK::MenuItem#initialize(width, height, depth)
// FLTK::MenuItem#initialize(context) # For internal use
static mrb_value
mrb_fltk_menu_item_initialize_method(mrb_state *mrb, mrb_value self)
{
  CONTEXT_CREATE( menu_item, context );
  context->fl_instance = new Fl_Image ( (int) mrb_fixnum( argv[0] ), (int) mrb_fixnum( argv[1] ), (int) mrb_fixnum( argv[2] ) );
  CONTEXT_SET_INSTANCE_VARIABLE( menu_item, context );
  
  return self;
}

void
mrb_fltk_menu_item_class_init(mrb_state *mrb)
{
  ARENA_SAVE;
  
  DEFINE_CLASS( menu_item, "MenuItem", mrb->object_class );
  
  DEFINE_INSTANCE_METHOD( image, initialize, ARGS_NONE() );
  
  ARENA_RESTORE;
}
