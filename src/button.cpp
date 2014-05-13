IMPLEMENT_WIDGET_INITIALIZE_METHOD( button, Fl_Button );
IMPLEMENT_WIDGET_INITIALIZE_METHOD( check_button, Fl_Check_Button );
IMPLEMENT_WIDGET_INITIALIZE_METHOD( light_button, Fl_Light_Button );
IMPLEMENT_WIDGET_INITIALIZE_METHOD( menu_button, Fl_Menu_Button );
IMPLEMENT_WIDGET_INITIALIZE_METHOD( radio_button, Fl_Radio_Button );
IMPLEMENT_WIDGET_INITIALIZE_METHOD( radio_light_button, Fl_Radio_Light_Button );
IMPLEMENT_WIDGET_INITIALIZE_METHOD( radio_round_button, Fl_Radio_Round_Button );
IMPLEMENT_WIDGET_INITIALIZE_METHOD( repeat_button, Fl_Repeat_Button );
IMPLEMENT_WIDGET_INITIALIZE_METHOD( return_button, Fl_Return_Button );
IMPLEMENT_WIDGET_INITIALIZE_METHOD( round_button, Fl_Round_Button );
IMPLEMENT_WIDGET_INITIALIZE_METHOD( toggle_button, Fl_Toggle_Button );
IMPLEMENT_WIDGET_INITIALIZE_METHOD( toggle_light_button, Fl_Toggle_Light_Button );
IMPLEMENT_WIDGET_INITIALIZE_METHOD( toggle_round_button, Fl_Toggle_Round_Button );

void
mrb_fltk_button_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  DEFINE_CLASS( button, "Button", mrb_fltk_widget_class );
  DEFINE_CLASS( check_button, "CheckButton", mrb_fltk_button_class );
  DEFINE_CLASS( light_button, "LightButton", mrb_fltk_button_class );
  DEFINE_CLASS( menu_button, "MenuButton", mrb_fltk_button_class );
  DEFINE_CLASS( radio_button, "RadioButton", mrb_fltk_button_class );
  DEFINE_CLASS( radio_light_button, "RadioLightButton", mrb_fltk_button_class );
  DEFINE_CLASS( radio_round_button, "RadioRoundButton", mrb_fltk_button_class );
  DEFINE_CLASS( repeat_button, "RepeatButton", mrb_fltk_button_class );
  DEFINE_CLASS( return_button, "ReturnButton", mrb_fltk_button_class );
  DEFINE_CLASS( round_button, "RoundButton", mrb_fltk_button_class );
  DEFINE_CLASS( toggle_button, "ToggleButton", mrb_fltk_button_class );
  DEFINE_CLASS( toggle_light_button, "ToggleLightButton", mrb_fltk_button_class );
  DEFINE_CLASS( toggle_round_button, "ToggleRoundButton", mrb_fltk_button_class );

  ARENA_RESTORE;
}
