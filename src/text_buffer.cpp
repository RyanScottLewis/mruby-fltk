static mrb_value
mrb_fltk_text_buffer_initialize_method(mrb_state *mrb, mrb_value self)
{
  CONTEXT_CREATE( text_buffer, context );
  context->fl_instance = new Fl_Text_Buffer;
  CONTEXT_SET_INSTANCE_VARIABLE( text_buffer, context );
  
  return self;
}

void
mrb_fltk_text_buffer_class_init(mrb_state *mrb)
{
  ARENA_SAVE;
  
  DEFINE_CLASS( text_buffer, "TextBuffer", mrb->object_class );
  
  DEFINE_INSTANCE_METHOD( menu_bar, initialize, ARGS_NONE() );
  
  DEFINE_FIXNUM_ATTRIBUTE_READER( text_buffer, length, Fl_Text_Buffer, length );
  
  DEFINE_STRING_ATTRIBUTE_ACCESSOR( text_buffer, text, Fl_Text_Buffer, text );
  
  ARENA_RESTORE;
}
