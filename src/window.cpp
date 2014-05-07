// FLTK::Window#show
static mrb_value
mrb_fltk_window_show_method(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP(widget);
  
  ( (Fl_Window *) context->fl_instance )->show();
  
  return mrb_nil_value();
}
