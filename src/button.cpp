DECLARE_WIDGET( button,              Fl_Button );
DECLARE_WIDGET( check_button,        Fl_Check_Button );
DECLARE_WIDGET( light_button,        Fl_Light_Button );
DECLARE_WIDGET( menu_button,         Fl_Menu_Button );
DECLARE_WIDGET( radio_button,        Fl_Radio_Button );
DECLARE_WIDGET( radio_light_button,  Fl_Radio_Light_Button );
DECLARE_WIDGET( radio_round_button,  Fl_Radio_Round_Button );
DECLARE_WIDGET( repeat_button,       Fl_Repeat_Button );
DECLARE_WIDGET( return_button,       Fl_Return_Button );
DECLARE_WIDGET( round_button,        Fl_Round_Button );
DECLARE_WIDGET( toggle_button,       Fl_Toggle_Button );
DECLARE_WIDGET( toggle_light_button, Fl_Toggle_Light_Button );
DECLARE_WIDGET( toggle_round_button, Fl_Toggle_Round_Button );

void
mrb_fltk_button_class_init(mrb_state *mrb)
{
  ARENA_SAVE;
  
  DEFINE_CLASS( button,              "Button",            mrb_fltk_widget_class );
  DEFINE_CLASS( check_button,        "CheckButton",       mrb_fltk_button_class );
  DEFINE_CLASS( light_button,        "LightButton",       mrb_fltk_button_class );
  DEFINE_CLASS( menu_button,         "MenuButton",        mrb_fltk_button_class );
  DEFINE_CLASS( radio_button,        "RadioButton",       mrb_fltk_button_class );
  DEFINE_CLASS( radio_light_button,  "RadioLightButton",  mrb_fltk_button_class );
  DEFINE_CLASS( radio_round_button,  "RadioRoundButton",  mrb_fltk_button_class );
  DEFINE_CLASS( repeat_button,       "RepeatButton",      mrb_fltk_button_class );
  DEFINE_CLASS( return_button,       "ReturnButton",      mrb_fltk_button_class );
  DEFINE_CLASS( round_button,        "RoundButton",       mrb_fltk_button_class );
  DEFINE_CLASS( toggle_button,       "ToggleButton",      mrb_fltk_button_class );
  DEFINE_CLASS( toggle_light_button, "ToggleLightButton", mrb_fltk_button_class );
  DEFINE_CLASS( toggle_round_button, "ToggleRoundButton", mrb_fltk_button_class );
  
  ARENA_RESTORE;
  
}
