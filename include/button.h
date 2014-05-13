#ifndef BUTTON_H
#define BUTTON_H

static mrb_value mrb_fltk_button_initialize_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_check_button_initialize_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_light_button_initialize_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_menu_button_initialize_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_radio_button_initialize_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_radio_light_button_initialize_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_radio_round_button_initialize_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_repeat_button_initialize_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_return_button_initialize_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_round_button_initialize_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_toggle_button_initialize_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_toggle_light_button_initialize_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_toggle_round_button_initialize_method( mrb_state *mrb, mrb_value self );
void mrb_fltk_button_class_init( mrb_state *mrb );

#endif // BUTTON_H
