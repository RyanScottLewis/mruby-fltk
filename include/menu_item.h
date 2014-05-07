#ifndef MENU_ITEM_H
#define MENU_ITEM_H

static mrb_value mrb_fltk_menu_item_initialize_method(mrb_state *mrb, mrb_value self);

#define DEFINE_FLTK_MENU_ITEM_CLASS()                       \
  ARENA_SAVE;                                               \
                                                            \
  DEFINE_CLASS( menu_item, "MenuItem", mrb->object_class ); \
  DEFINE_INSTANCE_METHOD( image, initialize, ARGS_NONE() ); \
                                                            \
  ARENA_RESTORE;

#endif // MENU_ITEM_H
