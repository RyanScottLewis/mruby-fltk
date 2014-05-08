#ifndef SHARED_IMAGE_H
#define SHARED_IMAGE_H

static mrb_value mrb_fltk_shared_initialize_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_shared_image_get_method(mrb_state *mrb, mrb_value self);
void mrb_fltk_shared_image_class_init(mrb_state *mrb);

#endif // SHARED_IMAGE_H
