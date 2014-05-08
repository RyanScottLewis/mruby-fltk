DECLARE_WIDGET( text_editor, Fl_Text_Editor );

void
mrb_fltk_text_editor_class_init(mrb_state *mrb)
{
  ARENA_SAVE;
  
  DEFINE_CLASS( text_editor, "TextEditor", mrb_fltk_text_display_class );
  
  ARENA_RESTORE;
}
