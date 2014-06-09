#ifndef PACK_H
#define PACK_H

#include <mruby/data.h>

#include "helpers.h"
#include "macros.h"

DEFINE_DATA_TYPE( pack, Pack );

void mrb_fltk_pack_class_init( mrb_state *mrb );

#endif // PACK_H
