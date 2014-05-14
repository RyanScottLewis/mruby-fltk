#ifndef HELPERS_H
#define HELPERS_H

void mrb_fltk_free( mrb_state *mrb, void *p );
bool mrb_fltk_arg_check( const char *t, int argc, mrb_value *argv );

#endif // HELPERS_H
