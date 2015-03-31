#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <Windows.h>
#include <stdio.h>

// Game Configuration
#define TITLE "R-TYPE personal project"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_SIZE 2
#define WIN_FULLSCREEN false
#define WIN_RESIZABLE false
#define WIN_BORDERLESS false
#define WIN_FULLSCREEN_DESKTOP false

#define LOG(format, ...) log(__FILE__, __LINE__, format, __VA_ARGS__);

enum update_status
{
	UPDATE_CONTINUE = 1,
	UPDATE_STOP,
	UPDATE_ERROR
};

void log(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "%s(%d) : %s\n", file, line, tmp_string);
	OutputDebugString(tmp_string2);
}

#endif // !__GLOBALS_H__
