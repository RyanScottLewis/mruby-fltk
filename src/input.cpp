DECLARE_WIDGET( input, Fl_Input );

void
mrb_fltk_input_class_init(mrb_state *mrb)
{
  ARENA_SAVE;
  
  DEFINE_CLASS( input, "Input", mrb_fltk_widget_class );
  
  DEFINE_STRING_ATTRIBUTE_ACCESSOR( input, value, Fl_Widget, value );
    
  ARENA_RESTORE;
}
