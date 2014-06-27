#ifndef NATIVE_FILE_CHOOSER_H
#define NATIVE_FILE_CHOOSER_H

#include <mruby/data.h>

#include "helpers.h"
#include "macros.h"

DEFINE_DATA_TYPE( native_file_chooser, NativeFileChooser );

void mrb_fltk_native_file_chooser_class_init( mrb_state *mrb );

#endif // NATIVE_FILE_CHOOSER_H
