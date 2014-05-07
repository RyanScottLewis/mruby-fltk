#ifndef SHARED_IMAGE_H
#define SHARED_IMAGE_H

static mrb_value mrb_fltk_shared_image_get_method(mrb_state *mrb, mrb_value self);

#define DEFINE_FLTK_SHARED_IMAGE_CLASS()                             \
  ARENA_SAVE;                                                        \
                                                                     \
  DEFINE_CLASS( shared_image, "SharedImage", mrb_fltk_image_class ); \
                                                                     \
  DEFINE_CLASS_METHOD( shared_image, get, ARGS_REQ(1) );             \
                                                                     \
  ARENA_RESTORE;

#endif // SHARED_IMAGE_H
