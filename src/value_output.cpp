IMPLEMENT_WIDGET_INITIALIZE_METHOD( value_output, Fl_Value_Output );

void
mrb_fltk_value_output_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  DEFINE_CLASS( value_output, "ValueOutput", mrb_fltk_widget_class );

  ARENA_RESTORE;
}
