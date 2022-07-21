short quitting = 0;

int 
main()
{
	// Counter-clockwise, reverse of CSS
	Rect win_bounds = { 50, 30, 0, 0 };
	
	WindowPtr win;
	char title[] = "Our app";
	
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
	win_bounds.bottom = screenBits.bounds.bottom - 30;
	
	// Definition of our new window. CtoPstr converts our C char to a Pascal title
	win = NewWindow(0L, &win_bounds, CtoPstr(title), true, 
		documentProc, (WindowPtr)-1L, true, 0);
		
	if(!win)
		ExitToShell();
		
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
						DragWindow(event_win, event.where, &screenBits.bounds);
						break;
					case inGoAway:
						if(TrackGoAway(event_win, event.where))
							quitting = 1;
						break;		
				}
				break;
		}
	}
}
