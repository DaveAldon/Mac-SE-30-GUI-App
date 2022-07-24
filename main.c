// Reference to the .rsrc file ID
#define GUI_IMAGE_ID 128

short quitting = 0;

void draw_window(void);

int 
main()
{
	// Counter-clockwise, reverse of CSS
	Rect win_bounds = { 50, 30, 0, 0 };
	
	WindowPtr win;
	char title[] = "GUI App Example";
	
	// If we use a Pascal string, we need to structure it like this
	//Str255 title = "\pOur app";
	
	// These are all initializations of built-in libraries we need from MacTrap, etc.
	InitGraf(&thePort);
	InitFonts();
	FlushEvents(everyEvent, 0);
	InitWindows();
	InitMenus();
	TEInit();
	InitDialogs(0);
	InitCursor();
	MaxApplZone();
	
	win_bounds.right = screenBits.bounds.right - 30;
	win_bounds.bottom = screenBits.bounds.bottom - 10;
	
	// Definition of our new window. CtoPstr converts our C char to a Pascal title
	win = NewWindow(0L, &win_bounds, CtoPstr(title), true, 
		documentProc, (WindowPtr)-1L, true, 0);
		
	if(!win)
		ExitToShell();
		
	SetPort(win);
		
	draw_window();
		
	while(!quitting) {
		EventRecord event;
		WindowPtr event_win;
		short event_in;
		
		WaitNextEvent(everyEvent, &event, 10L, 0);
		event_in = FindWindow(event.where, &event_win);
		
		switch(event.what) {
			case mouseDown:
				switch (event_in) {
					case inSysWindow:
						SystemClick(&event, event_win);
						break;
					case inDrag:
                        // Handles dragging the window
						DragWindow(event_win, event.where, &screenBits.bounds);
						break;
					case inGoAway:
                        // Handles if you click and hold on the close button, but drag away, cancelling the action
						if(TrackGoAway(event_win, event.where))
							quitting = 1;
						break;		
				}
				break;
			case updateEvt:
				BeginUpdate(event_win);
				// tells the system that you're going to redraw the window
				draw_window();
				EndUpdate(event_win);
				break;
		}
	}
}

void
draw_window(void) {
	// Handles are a pointer to a pointer.
	// You get a pointer to memory, but memory can move around. The data for pic
	// will move around, such as with new memory allocation, or defragmentation
	PicHandle pic;
	Rect pic_rect = { 0 };
	
	pic = GetPicture(GUI_IMAGE_ID);
	if(!pic) {
		quitting = 1;
		return;
		// We could also call ExitToShell here, but this ends the function more cleanly
	}
	
	// Windows don't actually exist, you're just drawing wherever the window's coordinates happen to be.
	// Coords are relative to the port
	
	pic_rect.right = (**(pic)).picFrame.right;
	pic_rect.bottom = (**(pic)).picFrame.bottom;
	
	DrawPicture(pic, &pic_rect);
}
