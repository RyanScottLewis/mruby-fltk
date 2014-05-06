# C Macros

The macros used are to remain consistent.

## Arguments

`name` is the downcase'd, snake cased name of a class. (`my_awesome_thing`)  
`fl_class` is a FLTK class (`Fl_Widget`)

# Syntax

## Indirection/References

Indirection (`*`) and reference (`&`) operators should be prepended to the variable, not appended to the type:

    my_type *my_thing;
    my_type other_thing;
    my_thing = &other_thing;

## Functions

All functions start with `mrb_fltk_`.

### MRuby Functions

Functions which are defined on MRuby objects are named like so:

    mrb_fltk_class_name_method_name

Getter functions are appended with `_get` and setter functions are appended with `_set`:

    mrb_fltk_crazy_cowboy_horse_set
    mrb_fltk_crazy_cowboy_horse_get

### Function Definitions

    // Comment
    type
    function_name( arg_type argument_name, arg_type_pointer *argument_pointer )
    {
    }
