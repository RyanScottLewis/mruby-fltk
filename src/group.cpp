#include <mruby.h>
#include <mruby/data.h>

#include <Fl/Fl_Group.h>

#include "macros.h"
#include "helpers.h"
#include "widget.h"
#include "group.h"

// FLTK::Group#begin
mrb_value mrb_fltk_group_begin_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_group, Fl_Group );

  mrb_value block = mrb_nil_value();

  mrb_get_args( mrb, "&", &block );

  if( !mrb_nil_p( block ) ) {
    mrb_value args[1];

    args[0] = self;

    fl_group->begin();
    mrb_yield_argv( mrb, block, 1, args );
    fl_group->end();
  } else {
    fl_group->begin();
  }

  return mrb_nil_value();
}

// FLTK::Group#end
mrb_value mrb_fltk_group_end_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_group, Fl_Group );

  fl_group->end();

  return mrb_nil_value();
}

// FLTK::Group#resizable
mrb_value mrb_fltk_group_resizable_getter_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_group, Fl_Group );

  Fl_Widget *fl_widget = fl_group->resizable();

  struct RClass *mrb_fltk_module = mrb_class_get( mrb, "FLTK" );
  struct RClass *mrb_fltk_widget_class = mrb_class_get_under( mrb, mrb_fltk_module, "Widget" );

  return mrb_obj_value( Data_Wrap_Struct( mrb, mrb_fltk_widget_class, &mrb_fltk_widget_type, (void *)fl_widget ) );
}

// FLTK::Group#resizable=(widget)
// Set the resizing box for the group
mrb_value mrb_fltk_group_resizable_setter_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_group, Fl_Group );

  mrb_value mrb_widget;
  mrb_get_args( mrb, "o", &mrb_widget );

  // TODO: Raise error unless is a FLTK::Widget

  Fl_Widget *fl_widget;
  Data_Get_Struct( mrb, mrb_widget, &mrb_fltk_widget_type, fl_widget );

  fl_group->resizable( fl_widget );

  return mrb_widget;
}

void mrb_fltk_group_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  struct RClass *mrb_fltk_module = mrb_class_get( mrb, "FLTK" );
  struct RClass *mrb_fltk_widget_class = mrb_class_get_under( mrb, mrb_fltk_module, "Widget" );

  DEFINE_CLASS( group, Group, mrb_fltk_widget_class );

  DEFINE_INSTANCE_METHOD( group, begin, MRB_ARGS_NONE() | MRB_ARGS_BLOCK() );
  DEFINE_INSTANCE_METHOD( group, end, MRB_ARGS_NONE() );

  DEFINE_INSTANCE_METHOD_ACCESSOR( group, resizable );

  ARENA_RESTORE;
}
