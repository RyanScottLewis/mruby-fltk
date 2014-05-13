IMPLEMENT_WINDOW_INITIALIZE_METHOD( window, Fl_Window );

// FLTK::Window#show
static mrb_value
mrb_fltk_window_show_method( mrb_state *mrb, mrb_value self ) {
  CONTEXT_SETUP( widget );

  ( (Fl_Window *)context->fl_instance )->show();

  return mrb_nil_value();
}

void
mrb_fltk_window_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  DEFINE_CLASS( window, "Window", mrb_fltk_widget_class );

  DEFINE_INSTANCE_METHOD( window, initialize, ARGS_ANY() );
  DEFINE_INSTANCE_METHOD( window, show, ARGS_OPT( 1 ) );

  DEFINE_GROUP_INSTANCE_METHODS( window );

  ARENA_RESTORE;
}
