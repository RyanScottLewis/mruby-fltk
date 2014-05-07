#ifndef MENU_BAR_H
#define MENU_BAR_H

static mrb_value mrb_fltk_menu_bar_add_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_menu_bar_menu_method(mrb_state *mrb, mrb_value self);

#define DEFINE_FLTK_MENU_BAR_CLASS()                              \
  ARENA_SAVE;                                                     \
                                                                  \
  DEFINE_CLASS( menu_bar, "MenuBar",  mrb_fltk_menu_item_class ); \
                                                                  \
  DEFINE_INSTANCE_METHOD( menu_bar, add,  ARGS_REQ(1) );          \
  DEFINE_INSTANCE_METHOD( menu_bar, menu, ARGS_NONE() );          \
                                                                  \
  ARENA_RESTORE;

#endif // MENU_BAR_H
