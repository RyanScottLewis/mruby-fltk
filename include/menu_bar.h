#ifndef MENU_BAR_H
#define MENU_BAR_H

static mrb_value mrb_fltk_menu_bar_initialize_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_menu_bar_add_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_menu_bar_menu_method( mrb_state *mrb, mrb_value self );
void mrb_fltk_menu_bar_class_init( mrb_state *mrb );

#endif // MENU_BAR_H
