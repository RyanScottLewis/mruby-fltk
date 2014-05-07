#ifndef TEXT_BUFFER_H
#define TEXT_BUFFER_H

static mrb_value mrb_fltk_text_buffer_initialize_method(mrb_state *mrb, mrb_value self);

#define DEFINE_FLTK_TEXT_BUFFER_CLASS()                                          \
  ARENA_SAVE;                                                                    \
                                                                                 \
  DEFINE_CLASS( text_buffer, "TextBuffer", mrb->object_class );                  \
                                                                                 \
  DEFINE_INSTANCE_METHOD( menu_bar, initialize, ARGS_NONE() );                   \
                                                                                 \
  DEFINE_FIXNUM_ATTRIBUTE_READER( text_buffer, length, Fl_Text_Buffer, length ); \
                                                                                 \
  DEFINE_STRING_ATTRIBUTE_ACCESSOR( text_buffer, text, Fl_Text_Buffer, text );   \
                                                                                 \
  ARENA_RESTORE;

#endif // TEXT_BUFFER_H
