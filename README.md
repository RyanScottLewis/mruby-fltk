# MRuby FLTK

[FLTK](http://www.fltk.org/index.php) 1.3.2 GUI binding, built for MRuby 1.0.0.

1.3.2 is the latest stable version of FLTK.

Lots of code was borrowed from [mattn/mruby-fltk3](https://github.com/mattn/mruby-fltk3).

> NOTE: Not yet released!  
> **Do not use until it is on the list of [MRuby Gems](http://www.mruby.org/libraries/) and this notice is gone.**

## Method Names

A few method names have been renamed to make them less ambiguous such as renaming ambiguous methods like `w` and `h` to `width` and `height`
or to make them more Ruby-ish such as renaming `labelfont` to `label_font`.

## Class List

### Implemented

Note that not all classes are fully implemented yet.
This means that not all of their public member functions have been mapped to instance methods on the Ruby side.
In the same light, not all of their static public member functions have been mapped to class methods.

    C                     | Ruby                   | Fully Implemented?
    ----------------------|------------------------|--------------------
    Fl                    | FLTK (module)          | 
    Fl_Box                | FLTK::Box              | 
    Fl_Button             | FLTK::Button           | 
    Fl_Check_Button       | FLTK::CheckButton      | 
    Fl_Double_Window      | FLTK::DoubleWindow     | 
    Fl_File_Chooser       | FLTK::FileChooser      | 
    Fl_Image              | FLTK::Image            | 
    Fl_Input              | FLTK::Input            | 
    Fl_Light_Button       | FLTK::LightButton      | 
    Fl_Menu               | FLTK::Menu             | 
    Fl_Menu_Bar           | FLTK::MenuBar          | 
    Fl_Menu_Button        | FLTK::MenuButton       | 
    Fl_Radio_Button       | FLTK::RadioButton      | 
    Fl_Radio_Light_Button | FLTK::RadioLightButton | 
    Fl_Radio_Round_Button | FLTK::RadioRoundButton | 
    Fl_Repeat_Button      | FLTK::RepeatButton     | 
    Fl_Return_Button      | FLTK::ReturnButton     | 
    Fl_Round_Button       | FLTK::RoundButton      | 
    Fl_Select_Browser     | FLTK::SelectBrowser    | 
    Fl_Shared_Image       | FLTK::SharedImage      | 
    Fl_Text_Display       | FLTK::TextDisplay      | 
    Fl_Text_Editor        | FLTK::TextEditor       | 
    Fl_Toggle_Button      | FLTK::ToggleButton     | 
    Fl_Value_Output       | FLTK::ValueOutput      | 
    Fl_Window             | FLTK::Window           | 

### Unimplemented

    Fl_Adjuster
    Fl_Bitmap
    Fl_BMP_Image
    Fl_Browser
    Fl_Cairo_State
    Fl_Cairo_Window
    Fl_Chart
    FL_CHART_ENTRY
    Fl_Check_Browser
    Fl_Choice
    Fl_Clock
    Fl_Clock_Output
    Fl_Color_Chooser
    Fl_Counter
    Fl_Device
    Fl_Device_Plugin
    Fl_Dial
    Fl_Display_Device
    Fl_End
    Fl_File_Browser
    Fl_File_Icon
    Fl_File_Input
    Fl_Fill_Dial
    Fl_Fill_Slider
    Fl_Float_Input
    Fl_Fontdesc
    Fl_Font_Descriptor
    Fl_FormsBitmap
    Fl_FormsPixmap
    Fl_Free
    Fl_GDI_Graphics_Driver
    Fl_GDI_Printer_Graphics_Driver
    Fl_GIF_Image
    Fl_Glut_Bitmap_Font
    Fl_Glut_StrokeChar
    Fl_Glut_StrokeFont
    Fl_Glut_StrokeStrip
    Fl_Glut_StrokeVertex
    Fl_Glut_Window
    Fl_Gl_Choice
    Fl_Gl_Window
    Fl_Graphics_Driver
    Fl_Graphics_Driver::matrix
    Fl_Group
    Fl_Help_Block
    Fl_Help_Dialog
    Fl_Help_Font_Stack
    Fl_Help_Font_Style
    Fl_Help_Link
    Fl_Help_Target
    Fl_Help_View
    Fl_Hold_Browser
    Fl_Hor_Fill_Slider
    Fl_Hor_Nice_Slider
    Fl_Hor_Slider
    Fl_Hor_Value_Slider
    Fl_Input_Choice
    Fl_Int_Input
    Fl_JPEG_Image
    Fl_Label
    Fl_Line_Dial
    Fl_Mac_App_Menu
    Fl_Menu_Item
    Fl_Menu_Window
    Fl_Multiline_Input
    Fl_Multiline_Output
    Fl_Multi_Browser
    Fl_Multi_Label
    Fl_Native_File_Chooser
    Fl_Nice_Slider
    Fl_Output
    Fl_Overlay_Window
    Fl_Pack
    Fl_Paged_Device
    Fl_Paged_Device::page_format
    Fl_Pixmap
    Fl_Plugin
    Fl_Plugin_Manager
    Fl_PNG_Image
    Fl_PNM_Image
    Fl_Positioner
    Fl_PostScript_File_Device
    Fl_PostScript_Graphics_Driver
    Fl_PostScript_Printer
    Fl_Preferences
    Fl_Preferences::Entry
    Fl_Preferences::Name
    Fl_Printer
    Fl_Progress
    Fl_Quartz_Graphics_Driver
    Fl_RGB_Image
    Fl_Roller
    Fl_Round_Clock
    Fl_Scroll
    Fl_Scrollbar
    Fl_Secret_Input
    Fl_Select_Browser
    Fl_Simple_Counter
    Fl_Single_Window
    Fl_Slider
    Fl_Spinner
    Fl_Surface_Device
    Fl_System_Printer
    Fl_Sys_Menu_Bar
    Fl_Table
    Fl_Table_Row
    Fl_Tabs
    Fl_Text_Buffer
    Fl_Text_Display::Style_Table_Entry
    Fl_Text_Editor::Key_Binding
    Fl_Text_Selection
    Fl_Tile
    Fl_Tiled_Image
    Fl_Timer
    Fl_Tooltip
    Fl_Tree
    Fl_Tree_Item
    Fl_Tree_Item_Array
    Fl_Tree_Prefs
    Fl_Valuator
    Fl_Value_Input
    Fl_Value_Slider
    Fl_Widget
    Fl_Widget_Tracker
    Fl_Wizard
    Fl_XBM_Image
    Fl_XColor
    Fl_Xlib_Graphics_Driver
    Fl_XPM_Image
    IActiveIMMApp
    XUtf8FontStruct

Feel free to fork, implement, and send a pull request for any of these widgets!

## TODO

* The unimplemented list, obviously.
* Example utilizing all implemented classes.
* Tests! How to test?
* Macro for `( (Fl_Class_Name *) context->fl_instance )`
* Macro for `if ( strcmp( mrb_obj_classname(mrb, argv[0]), "fltk_widget" ) ) mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid argument")`

## Contributing

* Check out the latest master to make sure the feature hasn't been implemented or the bug hasn't been fixed yet
* Check out the issue tracker to make sure someone already hasn't requested it and/or contributed it
* Fork the project
* Start a feature/bugfix branch
* Commit and push until you are happy with your contribution
* Make sure to add tests for it. This is important so I don't break it in a future version unintentionally.
* YARD

## Copyright

Copyright © 2014 Ryan Scott Lewis <ryanscottlewis@lewis-software.com>.

The MIT License (MIT) - See [LICENSE](LICENSE) for further details.
