#ifndef GROUP_H
#define GROUP_H

mrb_value mrb_fltk_group_begin_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_group_end_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_group_resizable_getter_instance_method( mrb_state *mrb, mrb_value self );
mrb_value mrb_fltk_group_resizable_setter_instance_method( mrb_state *mrb, mrb_value self );
void mrb_fltk_group_class_init( mrb_state *mrb );

#endif // GROUP_H
