#ifndef TEXT_EDITOR_H
#define TEXT_EDITOR_H

#define DEFINE_FLTK_TEXT_EDITOR_CLASS()                                   \
  ARENA_SAVE;                                                             \
                                                                          \
  DEFINE_CLASS( text_editor, "TextEditor", mrb_fltk_text_display_class ); \
                                                                          \
  ARENA_RESTORE;

#endif // TEXT_EDITOR_H
