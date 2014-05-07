static mrb_value
mrb_fltk_text_buffer_initialize_method(mrb_state *mrb, mrb_value self)
{
  CONTEXT_CREATE( text_buffer, context );
  context->fl_instance = new Fl_Text_Buffer;
  CONTEXT_SET_INSTANCE_VARIABLE( text_buffer, context );
  
  return self;
}
