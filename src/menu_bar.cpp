DECLARE_WIDGET( menu_bar, Fl_Menu_Bar );

// FLTK::MenuBar#add(caption, shortcut, &callback) 
static mrb_value
mrb_fltk_menu_bar_add_method(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP( widget );
  
  mrb_value block, caption, shortcut;
  block = mrb_nil_value();
  
  mrb_get_args(mrb, "&Si", &block, &caption, &shortcut);
  ( (Fl_Menu_Bar *) context->fl_instance)->add( RSTRING_PTR(caption), mrb_fixnum(shortcut), [] (Fl_Widget *widget) {
    // TODO: If block given, call block yielding the given widget
  });
  
  return mrb_nil_value();
}

// FLTK::MenuBar#menu
static mrb_value
mrb_fltk_menu_bar_menu_method(mrb_state *mrb, mrb_value self)
{
  CONTEXT_SETUP( widget );
  
  struct RClass *mrb_fltk_class = mrb_class_get( mrb, "FLTK" );
  struct RClass *mrb_fltk_menu_item_class = mrb_class_ptr( mrb_const_get( mrb, mrb_obj_value(mrb_fltk_class), mrb_intern_cstr( mrb, "MenuItem" ) ) );
  
  Fl_Menu_Item *fl_menu_item = (Fl_Menu_Item *) context->fl_instance )->menu();
  
  mrb_value args[1];
  args[0] = CONTEXT_WRAP( menu_item, fl_menu_item );
  
  return mrb_class_new_instance( mrb, 1, args, mrb_fltk_menu_item_class );
}
