#ifndef BUTTON_H
#define BUTTON_H

static mrb_value mrb_fltk_button_initialize_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_check_button_initialize_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_light_button_initialize_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_menu_button_initialize_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_radio_button_initialize_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_radio_light_button_initialize_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_radio_round_button_initialize_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_repeat_button_initialize_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_return_button_initialize_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_round_button_initialize_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_toggle_button_initialize_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_toggle_light_button_initialize_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_toggle_round_button_initialize_method(mrb_state *mrb, mrb_value self);

#define DEFINE_FLTK_BUTTON_CLASSES()                                               \
  ARENA_SAVE;                                                                      \
                                                                                   \
  DEFINE_CLASS( button,              "Button",            mrb_fltk_widget_class ); \
  DEFINE_CLASS( check_button,        "CheckButton",       mrb_fltk_button_class ); \
  DEFINE_CLASS( light_button,        "LightButton",       mrb_fltk_button_class ); \
  DEFINE_CLASS( menu_button,         "MenuButton",        mrb_fltk_button_class ); \
  DEFINE_CLASS( radio_button,        "RadioButton",       mrb_fltk_button_class ); \
  DEFINE_CLASS( radio_light_button,  "RadioLightButton",  mrb_fltk_button_class ); \
  DEFINE_CLASS( radio_round_button,  "RadioRoundButton",  mrb_fltk_button_class ); \
  DEFINE_CLASS( repeat_button,       "RepeatButton",      mrb_fltk_button_class ); \
  DEFINE_CLASS( return_button,       "ReturnButton",      mrb_fltk_button_class ); \
  DEFINE_CLASS( round_button,        "RoundButton",       mrb_fltk_button_class ); \
  DEFINE_CLASS( toggle_button,       "ToggleButton",      mrb_fltk_button_class ); \
  DEFINE_CLASS( toggle_light_button, "ToggleLightButton", mrb_fltk_button_class ); \
  DEFINE_CLASS( toggle_round_button, "ToggleRoundButton", mrb_fltk_button_class ); \
                                                                                   \
  ARENA_RESTORE;

#endif // BUTTON_H
