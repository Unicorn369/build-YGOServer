// Copyright (C) 2005-2006 Etienne Petitjean
// Copyright (C) 2007-2012 Christian Stehno
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in Irrlicht.h

#import "AppDelegate.h"

#ifdef _IRR_COMPILE_WITH_OSX_DEVICE_

@implementation AppDelegate

- (id)initWithDevice:(irr::CIrrDeviceMacOSX *)device
{
	self = [super init];
	if (self) _device = device;
	return (self);
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	_quit = FALSE;
}

- (void)orderFrontStandardAboutPanel:(id)sender
{
	[NSApp orderFrontStandardAboutPanel:sender];
}

- (void)unhideAllApplications:(id)sender
{
	[NSApp unhideAllApplications:sender];
}

- (void)hide:(id)sender
{
	[NSApp hide:sender];
}

- (void)hideOtherApplications:(id)sender
{
	[NSApp hideOtherApplications:sender];
}

- (void)terminate:(id)sender
{
	_quit = TRUE;
}

- (void)windowWillClose:(id)sender
{
	_quit = TRUE;
}

- (NSSize)windowWillResize:(NSWindow *)window toSize:(NSSize)proposedFrameSize
{
	if (_device->isResizable())
		return proposedFrameSize;
	else
		return [window frame].size;
}

- (void)windowDidResize:(NSNotification *)aNotification
{
	NSWindow	*window;
	NSRect		frame;

	window = [aNotification object];
	frame = [window frame];
	_device->setResize((int)frame.size.width,(int)frame.size.height);
}

- (BOOL)isQuit
{
	return (_quit);
}

- (void)keyDown:(NSEvent *)event
{
	[self interpretKeyEvents:@[event]];
}

- (void)insertText:(id)string
{
	[self setString: @""];
	if ([string isKindOfClass:[NSAttributedString class]])
	{
		_device->handleInputEvent([[string string] UTF8String]);
	}
	else
	{
		_device->handleInputEvent([string UTF8String]);
	}
}

- (void)doCommandBySelector:(SEL)selector
{
	_device->processKeyEvent();
}

- (void)paste:(id)sender
{
	// TODO: pass the pasted string. Now we discard it otherwise it will be kept in the editbox.
	[self setString: @""];
}

@end

#endif // _IRR_COMPILE_WITH_OSX_DEVICE_
