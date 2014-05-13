IMPLEMENT_WINDOW_INITIALIZE_METHOD( double_window, Fl_Double_Window );

void
mrb_fltk_double_window_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  DEFINE_CLASS( double_window, "DoubleWindow", mrb_fltk_window_class );

  ARENA_RESTORE;
}
