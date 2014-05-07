#ifndef IMAGE_H
#define IMAGE_H

static mrb_value mrb_fltk_image_initialize_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_image_copy_method(mrb_state *mrb, mrb_value self);
static mrb_value mrb_fltk_shared_image_get_method(mrb_state *mrb, mrb_value self);

#define DEFINE_FLTK_IMAGE_CLASS()                                                        \
  ARENA_SAVE;                                                                            \
                                                                                         \
  DEFINE_CLASS( image, "Image", mrb->object_class );                                     \
                                                                                         \
  DEFINE_INSTANCE_METHOD( image, initialize,    ARGS_REQ(3) );                           \
  DEFINE_INSTANCE_METHOD( image, copy,          ( MRB_ARGS_REQ(1) | MRB_ARGS_REQ(3) ) ); \
                                                                                         \
  DEFINE_FIXNUM_ATTRIBUTE_READER( image, width,          Fl_Image, w  );                 \
  DEFINE_FIXNUM_ATTRIBUTE_READER( image, height,         Fl_Image, h  );                 \
  DEFINE_FIXNUM_ATTRIBUTE_READER( image, depth,          Fl_Image, d  );                 \
  DEFINE_FIXNUM_ATTRIBUTE_READER( image, line_data_size, Fl_Image, ld );                 \
                                                                                         \
  ARENA_RESTORE;

#endif // IMAGE_H
