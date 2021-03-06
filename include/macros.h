#ifndef MACROS_H
#define MACROS_H

// =-=- GC Arena Macros =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define ARENA_SAVE                   \
  int ai = mrb_gc_arena_save( mrb ); \
  if( ai == MRB_GC_ARENA_SIZE )      \
    mrb_raise( mrb, E_RUNTIME_ERROR, "arena overflow" );

#define ARENA_RESTORE mrb_gc_arena_restore( mrb, ai );

#define DEFINE_DATA_TYPE( symbol, rb_class ) static const struct mrb_data_type mrb_fltk_##symbol##_type = { #rb_class, mrb_fltk_free };
#define SETUP_DATA_TYPE( symbol ) DATA_TYPE( self ) = &mrb_fltk_##symbol##_type;
#define SETUP_DATA_POINTER( value ) DATA_PTR( self ) = value;
#define GET_DATA( variable_name, type, wrapper ) type *variable_name = (type *)DATA_PTR( wrapper );

// =-=- Class/Module Macros =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define DEFINE_CLASS( symbol, rb_class, super ) \
  struct RClass *mrb_fltk_##symbol = mrb_define_class_under( mrb, mrb_fltk_module, #rb_class, super );

// =-=- Method Macros =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#define DEFINE_MODULE_METHOD( symbol, name, arguments ) \
  mrb_define_module_function( mrb, mrb_fltk_##symbol, #name, mrb_fltk_##symbol##_##name##_module_method, arguments );

#define DEFINE_CLASS_METHOD( symbol, rb_method, arguments ) \
  mrb_define_class_method( mrb, mrb_fltk_##symbol, #rb_method, mrb_fltk_##symbol##_##rb_method##_class_method, arguments );

#define DEFINE_INSTANCE_METHOD( symbol, name, arguments ) \
  mrb_define_method( mrb, mrb_fltk_##symbol, #name, mrb_fltk_##symbol##_##name##_instance_method, arguments );

#define DEFINE_INSTANCE_METHOD_GETTER( symbol, name ) \
  mrb_define_method( mrb, mrb_fltk_##symbol, #name, mrb_fltk_##symbol##_##name##_getter_instance_method, MRB_ARGS_NONE() );

#define DEFINE_INSTANCE_METHOD_SETTER( symbol, name ) \
  mrb_define_method( mrb, mrb_fltk_##symbol, #name "=", mrb_fltk_##symbol##_##name##_setter_instance_method, MRB_ARGS_REQ( 1 ) );

#define DEFINE_INSTANCE_METHOD_ACCESSOR( symbol, name ) \
  DEFINE_INSTANCE_METHOD_GETTER( symbol, name )         \
  DEFINE_INSTANCE_METHOD_SETTER( symbol, name )

// =-=- Context Macros =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

// Used within MRuby method functions
// #define CONTEXT_WRAP( name, variable ) mrb_obj_value( Data_Wrap_Struct( mrb, mrb->object_class, &fltk_##name##_type, (void *)variable ) );

// =-=- Constant Macro =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=

#define DEFINE_FIXNUM_CONSTANT( rb_name, value, rb_module ) mrb_define_const( mrb, rb_module, #rb_name, mrb_fixnum_value( value ) );

// =-=- Fixnum Attribute Macros =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=

// Implements a reader fixnum attribute for the mrb_fltk_##name##_class Ruby class
#define IMPLEMENT_FIXNUM_ATTRIBUTE_READER( name, rb_method, fl_class, fl_method )                      \
  mrb_value mrb_fltk_##name##_##rb_method##_getter_instance_method( mrb_state *mrb, mrb_value self ) { \
    GET_DATA( fl_instance, fl_class, self );                                                           \
                                                                                                       \
    return mrb_fixnum_value( fl_instance->fl_method() );                                               \
  }

// Implements a reader fixnum attribute for the mrb_fltk_##name##_class Ruby class
// TODO: Should return nil if fl_method was nil
#define IMPLEMENT_FIXNUM_ATTRIBUTE_WRITER( name, rb_method, fl_class, fl_method )                      \
  mrb_value mrb_fltk_##name##_##rb_method##_setter_instance_method( mrb_state *mrb, mrb_value self ) { \
    GET_DATA( fl_instance, fl_class, self );                                                           \
                                                                                                       \
    mrb_value value;                                                                                   \
    mrb_get_args( mrb, "i", &value );                                                                  \
                                                                                                       \
    fl_instance->fl_method( (int)mrb_fixnum( value ) );                                                \
                                                                                                       \
    return value;                                                                                      \
  }

// Implements a reader/writer fixnum attribute on the mrb_fltk_##name##_class Ruby class
#define IMPLEMENT_FIXNUM_ATTRIBUTE_ACCESSOR( name, rb_method, fl_class, fl_method ) \
  IMPLEMENT_FIXNUM_ATTRIBUTE_READER( name, rb_method, fl_class, fl_method );        \
  IMPLEMENT_FIXNUM_ATTRIBUTE_WRITER( name, rb_method, fl_class, fl_method );

// =-=- String Attribute Macros =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=-=-=-=-=-=-=-=

// TODO: Why const char?
#define IMPLEMENT_STRING_ATTRIBUTE_READER( name, rb_method, fl_class, fl_method )                      \
  mrb_value mrb_fltk_##name##_##rb_method##_getter_instance_method( mrb_state *mrb, mrb_value self ) { \
    GET_DATA( fl_instance, fl_class, self );                                                           \
                                                                                                       \
    const char *value = fl_instance->fl_method();                                                      \
                                                                                                       \
    return value ? mrb_str_new_cstr( mrb, value ) : mrb_nil_value();                                   \
  }

#define IMPLEMENT_STRING_ATTRIBUTE_WRITER( name, rb_method, fl_class, fl_method )                      \
  mrb_value mrb_fltk_##name##_##rb_method##_setter_instance_method( mrb_state *mrb, mrb_value self ) { \
    GET_DATA( fl_instance, fl_class, self );                                                           \
                                                                                                       \
    mrb_value value;                                                                                   \
    mrb_get_args( mrb, "S", &value );                                                                  \
                                                                                                       \
    fl_instance->rb_method( RSTRING_PTR( value ) );                                                    \
                                                                                                       \
    return value;                                                                                      \
  }

// Implements a reader/writer string attribute on the mrb_fltk_##name##_class Ruby class
#define IMPLEMENT_STRING_ATTRIBUTE_ACCESSOR( name, rb_method, fl_class, fl_method ) \
  IMPLEMENT_STRING_ATTRIBUTE_READER( name, rb_method, fl_class, fl_method );        \
  IMPLEMENT_STRING_ATTRIBUTE_WRITER( name, rb_method, fl_class, fl_method );

#endif // MACROS_H
