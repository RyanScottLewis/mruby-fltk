IMPLEMENT_WIDGET_INITIALIZE_METHOD( text_display, Fl_Text_Display );

static mrb_value
mrb_fltk_text_display_buffer_get_method( mrb_state *mrb, mrb_value self ) {
  CONTEXT_SETUP( widget );

  struct RClass *mrb_fltk_class = mrb_class_get( mrb, "FLTK" );
  struct RClass *mrb_fltk_text_buffer_class = mrb_class_ptr( mrb_const_get( mrb, mrb_obj_value( mrb_fltk_class ), mrb_intern_cstr( mrb, "TextBuffer" ) ) );

  Fl_Text_Buffer *fl_text_buffer = (Fl_Text_Buffer *) context->fl_instance )->buffer();

  mrb_value args[1];
  args[0] = CONTEXT_WRAP( text_buffer, fl_text_buffer );

  return mrb_class_new_instance( mrb, 1, args, mrb_fltk_text_buffer_class );
}

static mrb_value
mrb_fltk_text_display_buffer_set_method( mrb_state *mrb, mrb_value self ) {
  mrb_value text_buffer;
  mrb_get_args( mrb, "o", &text_buffer );

  // TODO: Raise error unless argument is a FLTK::TextBuffer

  CONTEXT_SETUP( widget );

  mrb_value text_buffer_context_value = mrb_iv_get( mrb, text_buffer, mrb_intern_cstr( mrb, "context" ) ); // Get @context from the given argument

  // Unwrap the argument's @buffer into the object's context struct
  mrb_fltk_text_buffer_context *text_buffer_context;
  Data_Get_Struct( mrb, text_buffer_context_value, &mrb_fltk_text_buffer_type, text_buffer_context );

  ( (Fl_Text_Display *)context->fl_instance )->buffer( text_buffer_context->fl_instance ); // Set this context's Fl class's buffer attribute to the argument's Fl class

  return mrb_nil_value();
}

void
mrb_fltk_text_display_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  DEFINE_CLASS( text_display, "TextDisplay", mrb_fltk_group_class );

  mrb_define_method( mrb, mrb_fltk_text_display_class, "buffer", mrb_fltk_text_display_buffer_get_method, ARGS_NONE() );
  mrb_define_method( mrb, mrb_fltk_text_display_class, "buffer=", mrb_fltk_text_display_buffer_set_method, ARGS_REQ( 1 ) );

  ARENA_RESTORE;
}
