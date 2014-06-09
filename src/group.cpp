#include <mruby.h>
#include <mruby/variable.h>
#include <mruby/data.h>
#include <mruby/string.h>

#include <Fl/Fl_Group.h>

#include "macros.h"
#include "helpers.h"
#include "widget.h"
#include "group.h"

// FLTK::Group#initialize
mrb_value mrb_fltk_group_initialize_instance_method( mrb_state *mrb, mrb_value self ) {
  SETUP_DATA_TYPE( group );

  mrb_value *argv;
  int argc;
  Fl_Group *fl_group;

  mrb_get_args( mrb, "*", &argv, &argc );

  if( mrb_fltk_arg_check( "iiii", argc, argv ) ) { // x, y, width, height
    fl_group = new Fl_Group( (int)mrb_fixnum( argv[0] ), (int)mrb_fixnum( argv[1] ), (int)mrb_fixnum( argv[2] ), (int)mrb_fixnum( argv[3] ) );
  } else if( mrb_fltk_arg_check( "iiiis", argc, argv ) ) { // x, y, width, height, title
    fl_group = new Fl_Group( (int)mrb_fixnum( argv[0] ), (int)mrb_fixnum( argv[1] ), (int)mrb_fixnum( argv[2] ), (int)mrb_fixnum( argv[3] ), RSTRING_PTR( argv[4] ) );
  } else {
    mrb_raise( mrb, E_ARGUMENT_ERROR, "invalid argument" ); // TODO: Error should show valid arguments

    return mrb_nil_value(); // NOTE: Won't reach here but shut's up compiler warnings
  }

  SETUP_DATA_POINTER( fl_group );

  Fl_Group::current( 0 ); // Prevent new widgets from being added to a group

  return self;
}

// FLTK::Group#add(widget)
// The widget is removed from its current group (if any) and then added to the end of this group.
mrb_value mrb_fltk_group_add_instance_method( mrb_state *mrb, mrb_value self ) {
  // TODO: Segfault when adding anything to
  GET_DATA( fl_group, Fl_Group, self );

  mrb_value mrb_widget;
  mrb_get_args( mrb, "o", &mrb_widget );

  // TODO: Raise error unless is a FLTK::Widget
  GET_DATA( fl_widget, Fl_Widget, mrb_widget );

  fl_group->add( fl_widget );

  mrb_iv_set( mrb, mrb_widget, mrb_intern_cstr( mrb, "parent" ), self );

  return self;
}

// FLTK::Group#begin
// mrb_value mrb_fltk_group_begin_instance_method( mrb_state *mrb, mrb_value self ) {
//   GET_DATA( fl_group, Fl_Group, self );
//
//   mrb_value block = mrb_nil_value();
//
//   mrb_get_args( mrb, "&", &block );
//
//   if( !mrb_nil_p( block ) ) {
//     mrb_value args[1];
//
//     args[0] = self;
//
//     fl_group->begin();
//     mrb_yield_argv( mrb, block, 1, args );
//     fl_group->end();
//   } else {
//     fl_group->begin();
//   }
//
//   return mrb_nil_value();
// }

// FLTK::Group#end
// mrb_value mrb_fltk_group_end_instance_method( mrb_state *mrb, mrb_value self ) {
//   GET_DATA( fl_group, Fl_Group, self );
//
//   fl_group->end();
//
//   return mrb_nil_value();
// }

// FLTK::Group#resizable // TODO TODO TODO TODO: Should perform like #add
mrb_value mrb_fltk_group_resizable_getter_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_group, Fl_Group, self );

  Fl_Widget *fl_widget = fl_group->resizable();

  struct RClass *mrb_fltk_module = mrb_class_get( mrb, "FLTK" );
  struct RClass *mrb_fltk_widget_class = mrb_class_get_under( mrb, mrb_fltk_module, "Widget" );

  return mrb_obj_value( Data_Wrap_Struct( mrb, mrb_fltk_widget_class, &mrb_fltk_widget_type, (void *)fl_widget ) );
}

// FLTK::Group#resizable=(widget)
// Set the resizing box for the group
mrb_value mrb_fltk_group_resizable_setter_instance_method( mrb_state *mrb, mrb_value self ) {
  GET_DATA( fl_group, Fl_Group, self );

  mrb_value mrb_widget;
  mrb_get_args( mrb, "o", &mrb_widget );

  // TODO: Raise error unless is a FLTK::Widget
  GET_DATA( fl_widget, Fl_Widget, mrb_widget );

  fl_group->resizable( fl_widget );

  return mrb_widget;
}

void mrb_fltk_group_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  struct RClass *mrb_fltk_module = mrb_class_get( mrb, "FLTK" );
  struct RClass *mrb_fltk_widget_class = mrb_class_get_under( mrb, mrb_fltk_module, "Widget" );

  DEFINE_CLASS( group, Group, mrb_fltk_widget_class );

  DEFINE_INSTANCE_METHOD( group, initialize, ARGS_ANY() );
  DEFINE_INSTANCE_METHOD( group, add, MRB_ARGS_REQ( 1 ) );
  // DEFINE_INSTANCE_METHOD( group, begin, MRB_ARGS_NONE() | MRB_ARGS_BLOCK() );
  // DEFINE_INSTANCE_METHOD( group, end, MRB_ARGS_NONE() );
  DEFINE_INSTANCE_METHOD_ACCESSOR( group, resizable );

  ARENA_RESTORE;
}
