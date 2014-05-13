IMPLEMENT_HIDDEN_OBJECT_INITIALIZE_METHOD( group, widget );

// FLTK::Group#begin
static mrb_value
mrb_fltk_group_begin_method( mrb_state *mrb, mrb_value self ) {
  CONTEXT_SETUP( widget );

  mrb_value block = mrb_nil_value();

  mrb_get_args( mrb, "&", &block );

  if( !mrb_nil_p( block ) ) {
    mrb_value args[1];

    args[0] = self;

    ( (Fl_Group *)context->fl_instance )->begin();
    mrb_yield_argv( mrb, block, 1, args );
    ( (Fl_Group *)context->fl_instance )->end();
  } else {
    ( (Fl_Group *)context->fl_instance )->begin();
  }

  return mrb_nil_value();
}

// FLTK::Group#end
static mrb_value
mrb_fltk_group_end_method( mrb_state *mrb, mrb_value self ) {
  CONTEXT_SETUP( widget );

  ( (Fl_Group *)context->fl_instance )->end();

  return mrb_nil_value();
}

// FLTK::Group#resizable
static mrb_value
mrb_fltk_group_resizable_get_method( mrb_state *mrb, mrb_value self ) {
  CONTEXT_SETUP( widget );

  struct RClass *mrb_fltk_class = mrb_class_get( mrb, "FLTK" );
  struct RClass *mrb_fltk_widget_class = mrb_class_ptr( mrb_const_get( mrb, mrb_obj_value( mrb_fltk_class ), mrb_intern_cstr( mrb, "Widget" ) ) );

  mrb_value args[1];

  args[0] = mrb_obj_value(
    Data_Wrap_Struct( mrb, mrb->object_class, &fltk_widget_type, (void *)( (Fl_Group *)context->fl_instance )->resizable() ) );

  return mrb_class_new_instance( mrb, 1, args, mrb_fltk_widget_class );
}

// FLTK::Group#resizable=(widget)
// Set the resizing box for the group
static mrb_value
mrb_fltk_group_resizable_set_method( mrb_state *mrb, mrb_value self ) {
  CONTEXT_SETUP( widget );

  mrb_value arg;
  mrb_get_args( mrb, "o", &arg );

  mrb_value arg_value_context = mrb_iv_get( mrb, arg, mrb_intern_cstr( mrb, "context" ) );

  mrb_fltk_widget_context *arg_context;
  Data_Get_Struct( mrb, arg_value_context, &fltk_widget_type, arg_context );

  ( (Fl_Group *)context->fl_instance )->resizable( arg_context->fl_instance );

  return mrb_nil_value();
}

void
mrb_fltk_group_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  DEFINE_CLASS( group, "Group", mrb_fltk_widget_class );
  DEFINE_GROUP_INSTANCE_METHODS( group );

  ARENA_RESTORE;
}
