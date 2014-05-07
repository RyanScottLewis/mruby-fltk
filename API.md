# API

## `Fl`

## Static Public Member Functions
    static int   add_awake_handler_ (Fl_Awake_Handler, void *)
       Adds an awake handler for use in awake(). 
    static void   add_check (Fl_Timeout_Handler, void *=0)
       FLTK will call this callback just before it flushes the display and waits for events. 
    static void   add_fd (int fd, int when, Fl_FD_Handler cb, void *=0)
       Adds file descriptor fd to listen to. 
    static void   add_fd (int fd, Fl_FD_Handler cb, void *=0)
       See void add_fd(int fd, int when, Fl_FD_Handler cb, void* = 0) 
    static void   add_handler (Fl_Event_Handler h)
       Install a function to parse unrecognized events. 
    static void   add_idle (Fl_Idle_Handler cb, void *data=0)
       Adds a callback function that is called every time by Fl::wait() and also makes it act as though the timeout is zero (this makes Fl::wait() return immediately, so if it is in a loop it is called repeatedly, and thus the idle fucntion is called repeatedly). 
    static void   add_timeout (double t, Fl_Timeout_Handler, void *=0)
       Adds a one-shot timeout callback. 
    static int   arg (int argc, char **argv, int &i)
       Parse a single switch from argv, starting at word i. 
    static int   args (int argc, char **argv, int &i, Fl_Args_Handler cb=0)
       Parse command line switches using the cb argument handler. 
    static void   args (int argc, char **argv)
       Parse all command line switches matching standard FLTK options only. 
    static void   awake (void *message=0)
       Sends a message pointer to the main thread, causing any pending Fl::wait() call to terminate so that the main thread can retrieve the message and any pending redraws can be processed. 
    static int   awake (Fl_Awake_Handler cb, void *message=0)
       See void awake(void* message=0). 
    static void   background (uchar, uchar, uchar)
       Changes fl_color(FL_BACKGROUND_COLOR) to the given color, and changes the gray ramp from 32 to 56 to black to white. 
    static void   background2 (uchar, uchar, uchar)
       Changes the alternative background color. 
    static Fl_Widget *   belowmouse ()
       Gets the widget that is below the mouse. 
    static void   belowmouse (Fl_Widget *)
       Sets the widget that is below the mouse. 
    static int   box_dh (Fl_Boxtype)
       Returns the height offset for the given boxtype. 
    static int   box_dw (Fl_Boxtype)
       Returns the width offset for the given boxtype. 
    static int   box_dx (Fl_Boxtype)
       Returns the X offset for the given boxtype. 
    static int   box_dy (Fl_Boxtype)
       Returns the Y offset for the given boxtype. 
    static void   cairo_autolink_context (bool alink)
       when FLTK_HAVE_CAIRO is defined and cairo_autolink_context() is true, any current window dc is linked to a current context. 
    static bool   cairo_autolink_context ()
       Gets the current autolink mode for cairo support. 
    static cairo_t *   cairo_cc ()
       Gets the current cairo context linked with a fltk window. 
    static void   cairo_cc (cairo_t *c, bool own=false)
       Sets the current cairo context to c. 
    static cairo_t *   cairo_make_current (Fl_Window *w)
       Provides a corresponding cairo context for window wi. 
    static int   check ()
       Same as Fl::wait(0). 
    static void   clear_widget_pointer (Fl_Widget const *w)
       Clears a widget pointer in the watch list. 
    static int   compose (int &del)
       Any text editing widget should call this for each FL_KEYBOARD event. 
    static void   compose_reset ()
       If the user moves the cursor, be sure to call Fl::compose_reset(). 
    static void   copy (const char *stuff, int len, int destination=0)
       Copies the data pointed to by stuff to the selection buffer (destination is 0) or the clipboard (destination is 1); len is the number of relevant bytes in stuff. 
    static void   damage (int d)
       If true then flush() will do something. 
    static int   damage ()
       If true then flush() will do something. 
    static void   default_atclose (Fl_Window *, void *)
       Default callback for window widgets. 
    static void   delete_widget (Fl_Widget *w)
       Schedules a widget for deletion at the next call to the event loop. 
    static void   display (const char *)
       Sets the X display to use for all windows. 
    static int   dnd ()
       Initiate a Drag And Drop operation. 
    static void   dnd_text_ops (int v)
       Gets or sets whether drag and drop text operations are supported. 
    static int   dnd_text_ops ()
       Gets or sets whether drag and drop text operations are supported. 
    static void   do_widget_deletion ()
       Deletes widgets previously scheduled for deletion. 
    static int   draw_box_active ()
       Determines if the current draw box is active or inactive. 
    static int   event ()
       Returns the last event that was processed. 
    static int   event_alt ()
       Returns non-zero if the Alt key is pressed. 
    static int   event_button ()
       Gets which particular mouse button caused the current event. 
    static int   event_button1 ()
       Returns non-zero if mouse button 1 is currently held down. 
    static int   event_button2 ()
       Returns non-zero if button 2 is currently held down. 
    static int   event_button3 ()
       Returns non-zero if button 3 is currently held down. 
    static int   event_buttons ()
       Returns the mouse buttons state bits; if non-zero, then at least one button is pressed now. 
    static int   event_clicks ()
       Returns non zero if we had a double click event. 
    static void   event_clicks (int i)
       Manually sets the number returned by Fl::event_clicks(). 
    static int   event_command ()
       Returns non-zero if the FL_COMMAND key is pressed, either FL_CTRL or on OSX FL_META. 
    static int   event_ctrl ()
       Returns non-zero if the Control key is pressed. 
    static void   event_dispatch (Fl_Event_Dispatch d)
       Set a new event dispatch function. 
    static Fl_Event_Dispatch   event_dispatch ()
       Return the current event dispatch function. 
    static int   event_dx ()
       Returns the current horizontal mouse scrolling associated with the FL_MOUSEWHEEL event. 
    static int   event_dy ()
       Returns the current vertical mouse scrolling associated with the FL_MOUSEWHEEL event. 
    static int   event_inside (int, int, int, int)
       Returns whether or not the mouse event is inside the given rectangle. 
    static int   event_inside (const Fl_Widget *)
       Returns whether or not the mouse event is inside a given child widget. 
    static int   event_is_click ()
       Returns non-zero if the mouse has not moved far enough and not enough time has passed since the last FL_PUSH or FL_KEYBOARD event for it to be considered a "drag" rather than a "click". 
    static void   event_is_click (int i)
       Clears the value returned by Fl::event_is_click(). 
    static int   event_key ()
       Gets which key on the keyboard was last pushed. 
    static int   event_key (int key)
       Returns true if the given key was held down (or pressed) during the last event. 
    static int   event_length ()
       Returns the length of the text in Fl::event_text(). 
    static int   event_original_key ()
       Returns the keycode of the last key event, regardless of the NumLock state. 
    static int   event_shift ()
       Returns non-zero if the Shift key is pressed. 
    static int   event_state ()
       This is a bitfield of what shift states were on and what mouse buttons were held down during the most recent event. 
    static int   event_state (int i)
       See int event_state() 
    static const char *   event_text ()
       Returns the text associated with the current event, including FL_PASTE or FL_DND_RELEASE events. 
    static int   event_x ()
       Returns the mouse position of the event relative to the Fl_Window it was passed to. 
    static int   event_x_root ()
       Returns the mouse position on the screen of the event. 
    static int   event_y ()
       Returns the mouse position of the event relative to the Fl_Window it was passed to. 
    static int   event_y_root ()
       Returns the mouse position on the screen of the event. 
    static Fl_Window *   first_window ()
       Returns the first top-level window in the list of shown() windows. 
    static void   first_window (Fl_Window *)
       Sets the window that is returned by first_window(). 
    static void   flush ()
       Causes all the windows that need it to be redrawn and graphics forced out through the pipes. 
    static Fl_Widget *   focus ()
       Gets the current Fl::focus() widget. 
    static void   focus (Fl_Widget *)
       Sets the widget that will receive FL_KEYBOARD events. 
    static void   foreground (uchar, uchar, uchar)
       Changes fl_color(FL_FOREGROUND_COLOR). 
    static void   free_color (Fl_Color i, int overlay=0)
       Frees the specified color from the colormap, if applicable. 
    static int   get_awake_handler_ (Fl_Awake_Handler &, void *&)
       Gets the last stored awake handler for use in awake(). 
    static Fl_Box_Draw_F *   get_boxtype (Fl_Boxtype)
       Gets the current box drawing function for the specified box type. 
    static unsigned   get_color (Fl_Color i)
       Returns the RGB value(s) for the given FLTK color index. 
    static void   get_color (Fl_Color i, uchar &red, uchar &green, uchar &blue)
       Returns the RGB value(s) for the given FLTK color index. 
    static const char *   get_font (Fl_Font)
       Gets the string for this face. 
    static const char *   get_font_name (Fl_Font, int *attributes=0)
       Get a human-readable string describing the family of this face. 
    static int   get_font_sizes (Fl_Font, int *&sizep)
       Return an array of sizes in sizep. 
    static int   get_key (int key)
       Returns true if the given key is held down now. 
    static void   get_mouse (int &, int &)
       Return where the mouse is on the screen by doing a round-trip query to the server. 
    static void   get_system_colors ()
       Read the user preference colors from the system and use them to call Fl::foreground(), Fl::background(), and Fl::background2(). 
    static int   gl_visual (int, int *alist=0)
       This does the same thing as Fl::visual(int) but also requires OpenGL drawing to work. 
    static Fl_Window *   grab ()
       Returns the window that currently receives all events. 
    static void   grab (Fl_Window *)
       Selects the window to grab. 
    static void   grab (Fl_Window &win)
       See grab(Fl_Window*) 
    static int   h ()
       Returns the height in pixels of the main screen work area. 
    static int   handle (int, Fl_Window *)
       Handle events from the window system. 
    static int   handle_ (int, Fl_Window *)
       Handle events from the window system. 
    static int   has_check (Fl_Timeout_Handler, void *=0)
       Returns 1 if the check exists and has not been called yet, 0 otherwise. 
    static int   has_idle (Fl_Idle_Handler cb, void *data=0)
       Returns true if the specified idle callback is currently installed. 
    static int   has_timeout (Fl_Timeout_Handler, void *=0)
       Returns true if the timeout exists and has not been called yet. 
    static int   lock ()
       The lock() method blocks the current thread until it can safely access FLTK widgets and data. 
    static Fl_Window *   modal ()
       Returns the top-most modal() window currently shown. 
    static Fl_Window *   next_window (const Fl_Window *)
       Returns the next top-level window in the list of shown() windows. 
    static bool   option (Fl_Option opt)
       FLTK library options management. 
    static void   option (Fl_Option opt, bool val)
       Override an option while the application is running. 
    static void   own_colormap ()
       Makes FLTK use its own colormap. 
    static void   paste (Fl_Widget &receiver, int source)
       Pastes the data from the selection buffer (source is 0) or the clipboard (source is 1) into receiver. 
    static void   paste (Fl_Widget &receiver)
       Backward compatibility only. 
    static Fl_Widget *   pushed ()
       Gets the widget that is being pushed. 
    static void   pushed (Fl_Widget *)
       Sets the widget that is being pushed. 
    static Fl_Widget *   readqueue ()
       All Fl_Widgets that don't have a callback defined use a default callback that puts a pointer to the widget in this queue, and this method reads the oldest widget out of this queue. 
    static int   ready ()
       This is similar to Fl::check() except this does not call Fl::flush() or any callbacks, which is useful if your program is in a state where such callbacks are illegal. 
    static void   redraw ()
       Redraws all widgets. 
    static void   release ()
       Releases the current grabbed window, equals grab(0). 
    static void   release_widget_pointer (Fl_Widget *&w)
       Releases a widget pointer from the watch list. 
    static int   reload_scheme ()
       Called by scheme according to scheme name. 
    static void   remove_check (Fl_Timeout_Handler, void *=0)
       Removes a check callback. 
    static void   remove_fd (int, int when)
       Removes a file descriptor handler. 
    static void   remove_fd (int)
       Removes a file descriptor handler. 
    static void   remove_handler (Fl_Event_Handler h)
       Removes a previously added event handler. 
    static void   remove_idle (Fl_Idle_Handler cb, void *data=0)
       Removes the specified idle callback, if it is installed. 
    static void   remove_timeout (Fl_Timeout_Handler, void *=0)
       Removes a timeout callback. 
    static void   repeat_timeout (double t, Fl_Timeout_Handler, void *=0)
       Repeats a timeout callback from the expiration of the previous timeout, allowing for more accurate timing. 
    static int   run ()
       As long as any windows are displayed this calls Fl::wait() repeatedly. 
    static int   scheme (const char *)
       Gets or sets the current widget scheme. 
    static const char *   scheme ()
       See void scheme(const char *name) 
    static int   screen_count ()
       Gets the number of available screens. 
    static void   screen_dpi (float &h, float &v, int n=0)
       Gets the screen resolution in dots-per-inch for the given screen. 
    static void   screen_work_area (int &X, int &Y, int &W, int &H, int mx, int my)
       Gets the bounding box of the work area of a screen that contains the specified screen position mx, my. 
    static void   screen_work_area (int &X, int &Y, int &W, int &H, int n)
       Gets the bounding box of the work area of the given screen. 
    static void   screen_work_area (int &X, int &Y, int &W, int &H)
       Gets the bounding box of the work area of the screen that contains the mouse pointer. 
    static void   screen_xywh (int &X, int &Y, int &W, int &H)
       Gets the bounding box of a screen that contains the mouse pointer. 
    static void   screen_xywh (int &X, int &Y, int &W, int &H, int mx, int my)
       Gets the bounding box of a screen that contains the specified screen position mx, my. 
    static void   screen_xywh (int &X, int &Y, int &W, int &H, int n)
       Gets the screen bounding rect for the given screen. 
    static void   screen_xywh (int &X, int &Y, int &W, int &H, int mx, int my, int mw, int mh)
       Gets the screen bounding rect for the screen which intersects the most with the rectangle defined by mx, my, mw, mh. 
    static int   scrollbar_size ()
       Gets the default scrollbar size used by Fl_Browser_, Fl_Help_View, Fl_Scroll, and Fl_Text_Display widgets. 
    static void   scrollbar_size (int W)
       Sets the default scrollbar size that is used by the Fl_Browser_, Fl_Help_View, Fl_Scroll, and Fl_Text_Display widgets. 
    static void   selection (Fl_Widget &owner, const char *, int len)
       Changes the current selection. 
    static Fl_Widget *   selection_owner ()
       back-compatibility only: Gets the widget owning the current selection 
    static void   selection_owner (Fl_Widget *)
       Back-compatibility only: The single-argument call can be used to move the selection to another widget or to set the owner to NULL, without changing the actual text of the selection. 
    static void   set_abort (Fl_Abort_Handler f)
       For back compatibility, sets the void Fl::fatal handler callback. 
    static void   set_atclose (Fl_Atclose_Handler f)
       For back compatibility, sets the Fl::atclose handler callback. 
    static void   set_boxtype (Fl_Boxtype, Fl_Box_Draw_F *, uchar, uchar, uchar, uchar)
       Sets the function to call to draw a specific boxtype. 
    static void   set_boxtype (Fl_Boxtype, Fl_Boxtype from)
       Copies the from boxtype. 
    static void   set_color (Fl_Color, uchar, uchar, uchar)
       Sets an entry in the fl_color index table. 
    static void   set_color (Fl_Color i, unsigned c)
       Sets an entry in the fl_color index table. 
    static void   set_font (Fl_Font, const char *)
       Changes a face. 
    static void   set_font (Fl_Font, Fl_Font)
       Copies one face to another. 
    static Fl_Font   set_fonts (const char *=0)
       FLTK will open the display, and add every fonts on the server to the face table. 
    static void   set_idle (Fl_Old_Idle_Handler cb)
       Sets an idle callback. 
    static void   set_labeltype (Fl_Labeltype, Fl_Label_Draw_F *, Fl_Label_Measure_F *)
       Sets the functions to call to draw and measure a specific labeltype. 
    static void   set_labeltype (Fl_Labeltype, Fl_Labeltype from)
       Sets the functions to call to draw and measure a specific labeltype. 
    static int   test_shortcut (Fl_Shortcut)
       Tests the current event, which must be an FL_KEYBOARD or FL_SHORTCUT, against a shortcut value (described in Fl_Button). 
    static void *   thread_message ()
       The thread_message() method returns the last message that was sent from a child by the awake() method. 
    static void   unlock ()
       The unlock() method releases the lock that was set using the lock() method. 
    static double   version ()
       Returns the compiled-in value of the FL_VERSION constant. 
    static void   visible_focus (int v)
       Gets or sets the visible keyboard focus on buttons and other non-text widgets. 
    static int   visible_focus ()
       Gets or sets the visible keyboard focus on buttons and other non-text widgets. 
    static int   visual (int)
       Selects a visual so that your graphics are drawn correctly. 
    static int   w ()
       Returns the width in pixels of the main screen work area. 
    static int   wait ()
       Waits until "something happens" and then returns. 
    static double   wait (double time)
       See int Fl::wait() 
    static void   watch_widget_pointer (Fl_Widget *&w)
       Adds a widget pointer to the widget watch list. 
    static int   x ()
       Returns the leftmost x coordinate of the main screen work area. 
    static int   y ()
       Returns the topmost y coordinate of the main screen work area. 

## `Fl_Image`

### Public Member Functions
    Fl_Image   Fl_Image (int W, int H, int D)
       The constructor creates an empty image with the specified width, height, and depth.
    virtual   ~Fl_Image ()
       The destructor is a virtual method that frees all memory used by the image.
    virtual void   color_average (Fl_Color c, float i)
       The color_average() method averages the colors in the image with the FLTK color value c.
    virtual Fl_Image *   copy (int W, int H)
       The copy() method creates a copy of the specified image.
    Fl_Image *   copy ()
       The copy() method creates a copy of the specified image.
    int   count () const
       The count() method returns the number of data values associated with the image.
    int   d () const
       Returns the current image depth.
    const char *const *   data () const
       Returns a pointer to the current image data array.
    virtual void   desaturate ()
       The desaturate() method converts an image to grayscale.
    virtual void   draw (int X, int Y, int W, int H, int cx=0, int cy=0)
       Draws the image with a bounding box.
    void   draw (int X, int Y)
       Draws the image.
    int   h () const
       Returns the current image height in pixels.
    void   inactive ()
       The inactive() method calls color_average(FL_BACKGROUND_COLOR, 0.33f) to produce an image that appears grayed out.
    virtual void   label (Fl_Widget *w)
       The label() methods are an obsolete way to set the image attribute of a widget or menu item.
    virtual void   label (Fl_Menu_Item *m)
       The label() methods are an obsolete way to set the image attribute of a widget or menu item.
    int   ld () const
       Returns the current line data size in bytes.
    virtual void   uncache ()
       If the image has been cached for display, delete the cache data.
    int   w () const
       Returns the current image width in pixels.

## `Fl_Shared_Image`

### Public Member Functions

    virtual void   color_average (Fl_Color c, float i)
       The color_average() method averages the colors in the image with the FLTK color value c. 
    virtual Fl_Image *   copy (int W, int H)
       The copy() method creates a copy of the specified image. 
    Fl_Image *   copy ()
       The copy() method creates a copy of the specified image. 
    virtual void   desaturate ()
       The desaturate() method converts an image to grayscale. 
    virtual void   draw (int X, int Y, int W, int H, int cx, int cy)
       Draws the image with a bounding box. 
    void   draw (int X, int Y)
       Draws the image. 
    const char *   name ()
       Returns the filename of the shared image. 
    int   refcount ()
       Returns the number of references of this shared image. 
    void   release ()
       Releases and possibly destroys (if refcount <=0) a shared image. 
    void   reload ()
       Reloads the shared image from disk. 
    virtual void   uncache ()
       If the image has been cached for display, delete the cache data. 

### Static Public Member Functions

    static void   add_handler (Fl_Shared_Handler f)
       Adds a shared image handler, which is basically a test function for adding new formats. 
    static Fl_Shared_Image *   find (const char *n, int W=0, int H=0)
       Finds a shared image from its named and size specifications. 
    static Fl_Shared_Image *   get (const char *n, int W=0, int H=0)
       Find or load an image that can be shared by multiple widgets. 
    static Fl_Shared_Image **   images ()
       Returns the Fl_Shared_Image* array. 
    static int   num_images ()
       Returns the total number of shared images in the array. 
    static void   remove_handler (Fl_Shared_Handler f)
       Removes a shared image handler. 

## `Fl_Widget`

### Public Member Functions
    void   _clear_fullscreen ()
    void   _set_fullscreen ()
    void   activate ()
       Activates the widget. 
    unsigned int   active () const
       Returns whether the widget is active. 
    int   active_r () const
       Returns whether the widget and all of its parents are active. 
    Fl_Align   align () const
       Gets the label alignment. 
    void   align (Fl_Align alignment)
       Sets the label alignment. 
    long   argument () const
       Gets the current user data (long) argument that is passed to the callback function. 
    void   argument (long v)
       Sets the current user data (long) argument that is passed to the callback function. 
    virtual class Fl_Gl_Window *   as_gl_window ()
       Returns an Fl_Gl_Window pointer if this widget is an Fl_Gl_Window. 
    virtual Fl_Group *   as_group ()
       Returns an Fl_Group pointer if this widget is an Fl_Group. 
    virtual Fl_Window *   as_window ()
       Returns an Fl_Window pointer if this widget is an Fl_Window. 
    Fl_Boxtype   box () const
       Gets the box type of the widget. 
    void   box (Fl_Boxtype new_box)
       Sets the box type for the widget. 
    Fl_Callback_p   callback () const
       Gets the current callback function for the widget. 
    void   callback (Fl_Callback *cb, void *p)
       Sets the current callback function for the widget. 
    void   callback (Fl_Callback *cb)
       Sets the current callback function for the widget. 
    void   callback (Fl_Callback0 *cb)
       Sets the current callback function for the widget. 
    void   callback (Fl_Callback1 *cb, long p=0)
       Sets the current callback function for the widget. 
    unsigned int   changed () const
       Checks if the widget value changed since the last callback. 
    void   clear_changed ()
       Marks the value of the widget as unchanged. 
    void   clear_damage (uchar c=0)
       Clears or sets the damage flags. 
    void   clear_output ()
       Sets a widget to accept input. 
    void   clear_visible ()
       Hides the widget. 
    void   clear_visible_focus ()
       Disables keyboard focus navigation with this widget. 
    Fl_Color   color () const
       Gets the background color of the widget. 
    void   color (Fl_Color bg)
       Sets the background color of the widget. 
    void   color (Fl_Color bg, Fl_Color sel)
       Sets the background and selection color of the widget. 
    Fl_Color   color2 () const
       For back compatibility only. 
    void   color2 (unsigned a)
       For back compatibility only. 
    int   contains (const Fl_Widget *w) const
       Checks if w is a child of this widget. 
    void   copy_label (const char *new_label)
       Sets the current label. 
    void   copy_tooltip (const char *text)
       Sets the current tooltip text. 
    uchar   damage () const
       Returns non-zero if draw() needs to be called. 
    void   damage (uchar c)
       Sets the damage bits for the widget. 
    void   damage (uchar c, int x, int y, int w, int h)
       Sets the damage bits for an area inside the widget. 
    int   damage_resize (int, int, int, int)
       Internal use only. 
    void   deactivate ()
       Deactivates the widget. 
    Fl_Image *   deimage ()
       Gets the image that is used as part of the widget label. 
    const Fl_Image *   deimage () const
    void   deimage (Fl_Image *img)
       Sets the image to use as part of the widget label. 
    void   deimage (Fl_Image &img)
       Sets the image to use as part of the widget label. 
    void   do_callback ()
       Calls the widget callback. 
    void   do_callback (Fl_Widget *o, long arg)
       Calls the widget callback. 
    void   do_callback (Fl_Widget *o, void *arg=0)
       Calls the widget callback. 
    virtual void   draw ()=0
       Draws the widget. 
    void   draw_label (int, int, int, int, Fl_Align) const
       Draws the label in an arbitrary bounding box with an arbitrary alignment. 
    int   h () const
       Gets the widget height. 
    virtual int   handle (int event)
       Handles the specified event. 
    virtual void   hide ()
       Makes a widget invisible. 
    Fl_Image *   image ()
       Gets the image that is used as part of the widget label. 
    const Fl_Image *   image () const
    void   image (Fl_Image *img)
       Sets the image to use as part of the widget label. 
    void   image (Fl_Image &img)
       Sets the image to use as part of the widget label. 
    int   inside (const Fl_Widget *wgt) const
       Checks if this widget is a child of wgt. 
    const char *   label () const
       Gets the current label text. 
    void   label (const char *text)
       Sets the current label pointer. 
    void   label (Fl_Labeltype a, const char *b)
       Shortcut to set the label text and type in one call. 
    Fl_Color   labelcolor () const
       Gets the label color. 
    void   labelcolor (Fl_Color c)
       Sets the label color. 
    Fl_Font   labelfont () const
       Gets the font to use. 
    void   labelfont (Fl_Font f)
       Sets the font to use. 
    Fl_Fontsize   labelsize () const
       Gets the font size in pixels. 
    void   labelsize (Fl_Fontsize pix)
       Sets the font size in pixels. 
    Fl_Labeltype   labeltype () const
       Gets the label type. 
    void   labeltype (Fl_Labeltype a)
       Sets the label type. 
    void   measure_label (int &ww, int &hh) const
       Sets width ww and height hh accordingly with the label size. 
    unsigned int   output () const
       Returns if a widget is used for output only. 
    Fl_Group *   parent () const
       Returns a pointer to the parent widget. 
    void   parent (Fl_Group *p)
       Internal use only - "for hacks only". 
    void   position (int X, int Y)
       Repositions the window or widget. 
    void   redraw ()
       Schedules the drawing of the widget. 
    void   redraw_label ()
       Schedules the drawing of the label. 
    virtual void   resize (int x, int y, int w, int h)
       Changes the size or position of the widget. 
    Fl_Color   selection_color () const
       Gets the selection color. 
    void   selection_color (Fl_Color a)
       Sets the selection color. 
    void   set_changed ()
       Marks the value of the widget as changed. 
    void   set_output ()
       Sets a widget to output only. 
    void   set_visible ()
       Makes the widget visible. 
    void   set_visible_focus ()
       Enables keyboard focus navigation with this widget. 
    virtual void   show ()
       Makes a widget visible. 
    void   size (int W, int H)
       Changes the size of the widget. 
    int   take_focus ()
       Gives the widget the keyboard focus. 
    unsigned int   takesevents () const
       Returns if the widget is able to take events. 
    int   test_shortcut ()
       Returns true if the widget's label contains the entered '&x' shortcut. 
    const char *   tooltip () const
       Gets the current tooltip text. 
    void   tooltip (const char *text)
       Sets the current tooltip text. 
    uchar   type () const
       Gets the widget type. 
    void   type (uchar t)
       Sets the widget type. 
    void *   user_data () const
       Gets the user data for this widget. 
    void   user_data (void *v)
       Sets the user data for this widget. 
    unsigned int   visible () const
       Returns whether a widget is visible. 
    void   visible_focus (int v)
       Modifies keyboard focus navigation. 
    unsigned int   visible_focus ()
       Checks whether this widget has a visible focus. 
    int   visible_r () const
       Returns whether a widget and all its parents are visible. 
    int   w () const
       Gets the widget width. 
    Fl_When   when () const
       Returns the conditions under which the callback is called. 
    void   when (uchar i)
       Sets the flags used to decide when a callback is called. 
    Fl_Window *   window () const
       Returns a pointer to the primary Fl_Window widget. 
    int   x () const
       Gets the widget position in its window. 
    int   y () const
       Gets the widget position in its window. 
    virtual   ~Fl_Widget ()
       Destroys the widget. 

### Static Public Member Functions

    static void   default_callback (Fl_Widget *cb, void *d)
       Sets the default callback for all widgets. 
    static unsigned int   label_shortcut (const char *t)
       Returns the Unicode value of the '&x' shortcut in a given text. 
    static int   test_shortcut (const char *, const bool require_alt=false)
       Returns true if the given text t contains the entered '&x' shortcut. 
