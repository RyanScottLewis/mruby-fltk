#include <mruby.h>
#include <mruby/data.h>
#include <mruby/string.h>

#include <Fl/Fl_Pack.h>

#include "macros.h"
#include "helpers.h"
#include "group.h"
#include "pack.h"

// FLTK::Pack#initialize
mrb_value mrb_fltk_pack_initialize_instance_method( mrb_state *mrb, mrb_value self ) {
  SETUP_DATA_TYPE( pack );

  mrb_value *argv;
  int argc;
  Fl_Pack *fl_pack;

  mrb_get_args( mrb, "*", &argv, &argc );

  if( mrb_fltk_arg_check( "iiii", argc, argv ) ) { // x, y, width, height
    fl_pack = new Fl_Pack( (int)mrb_fixnum( argv[0] ), (int)mrb_fixnum( argv[1] ), (int)mrb_fixnum( argv[2] ), (int)mrb_fixnum( argv[3] ) );
  } else if( mrb_fltk_arg_check( "iiiis", argc, argv ) ) { // x, y, width, height, label
    fl_pack = new Fl_Pack( (int)mrb_fixnum( argv[0] ), (int)mrb_fixnum( argv[1] ), (int)mrb_fixnum( argv[2] ), (int)mrb_fixnum( argv[3] ), RSTRING_PTR( argv[4] ) );
  } else {
    mrb_raise( mrb, E_ARGUMENT_ERROR, "invalid argument" ); // TODO: Error should show valid arguments

    return mrb_nil_value(); // NOTE: Won't reach here but shut's up compiler warnings
  }

  SETUP_DATA_POINTER( fl_pack );

  return self;
}

void mrb_fltk_pack_class_init( mrb_state *mrb ) {
  ARENA_SAVE;

  struct RClass *mrb_fltk_module = mrb_class_get( mrb, "FLTK" );
  struct RClass *mrb_fltk_group_class = mrb_class_get_under( mrb, mrb_fltk_module, "Group" );

  DEFINE_CLASS( pack, Pack, mrb_fltk_group_class );

  DEFINE_INSTANCE_METHOD( pack, initialize, ARGS_ANY() );

  ARENA_RESTORE;
}
