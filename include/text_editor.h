#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

static mrb_value mrb_fltk_text_editor_initialize_method(mrb_state *mrb, mrb_value self);

#define DEFINE_FLTK_TEXT_EDITOR_CLASS()                                   \
  ARENA_SAVE;                                                             \
                                                                          \
  DEFINE_CLASS( text_editor, "TextEditor", mrb_fltk_text_display_class ); \
                                                                          \
  ARENA_RESTORE;

#endif // TEXT_EDITOR_H
