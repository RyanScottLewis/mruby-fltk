#ifndef GROUP_H
#define GROUP_H

static mrb_value mrb_fltk_group_initialize_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_group_begin_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_group_end_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_group_resizable_get_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_group_resizable_set_method( mrb_state *mrb, mrb_value self );
void mrb_fltk_group_class_init( mrb_state *mrb );

// TODO: USe DEFINE method macros
#define DEFINE_GROUP_INSTANCE_METHODS( name )                                                                \
  mrb_define_method( mrb, mrb_fltk_##name##_class, "begin", mrb_fltk_group_begin, ARGS_NONE() );             \
  mrb_define_method( mrb, mrb_fltk_##name##_class, "end", mrb_fltk_group_end, ARGS_NONE() );                 \
  mrb_define_method( mrb, mrb_fltk_##name##_class, "resizable", mrb_fltk_group_resizable_get, ARGS_NONE() ); \
  mrb_define_method( mrb, mrb_fltk_##name##_class, "resizable=", mrb_fltk_group_resizable_set, ARGS_REQ( 1 ) );

#endif // GROUP_H
