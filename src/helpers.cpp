static void
mrb_fltk_free( mrb_state *mrb, void *p ) {
  free( p );
}

static bool
mrb_fltk_arg_check( const char *t, int argc, mrb_value *argv ) {
  int n, l = strlen( t );

  if( l != argc )
    return false;

  for( n = 0; n < l; n++ ) {
    if( n >= argc )
      return false;
    if( t[n] == 'i' && mrb_type( argv[n] ) != MRB_TT_FIXNUM )
      return false;
    if( t[n] == 'd' && mrb_type( argv[n] ) != MRB_TT_FLOAT )
      return false;
    if( t[n] == 's' && mrb_type( argv[n] ) != MRB_TT_STRING )
      return false;
    if( t[n] == 'b' && mrb_type( argv[n] ) != MRB_TT_TRUE && mrb_type( argv[n] ) != MRB_TT_FALSE )
      return false;
  }

  return true;
}
