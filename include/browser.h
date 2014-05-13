#ifndef BROWSER_H
#define BROWSER_H

// =-=- FLTK::Browser -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=--=

static mrb_value mrb_fltk_browser_initialize_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_browser_add_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_browser_column_widths_get_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_browser_column_widths_set_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_browser_icon_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_browser_load_method( mrb_state *mrb, mrb_value self );
static mrb_value mrb_fltk_browser_text_method( mrb_state *mrb, mrb_value self );
void mrb_fltk_browser_class_init( mrb_state *mrb );

// =-=- FLTK::SelectBrowser -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-==-=-=
// TODO: Seperate file

static mrb_value mrb_fltk_select_browser_initialize_method( mrb_state *mrb, mrb_value self );
void mrb_fltk_select_browser_class_init( mrb_state *mrb );

#endif // BROWSER_H
