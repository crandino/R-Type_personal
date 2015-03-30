#include <Windows.h>
#include <stdio.h>
#include "Globals.h"

#include "SDL2-2.0.3\include\SDL.h"

// pragma is an exclusive extension of Visual Studio,
// so it only works on here. 
#pragma comment( lib, "SDL2-2.0.3/lib/x86/SDL2.lib")
#pragma comment( lib, "SDL2-2.0.3/lib/x86/SDL2main.lib")

/* Setting up SDL configuration. On Project Properties
Configuration Propertires/VC++ Directories:
->Include directories: $(ProjectDir)SDL2-2.0.3\include
->Library directories: $(ProjectDir)SDL2-2.0.3\lib\x86
Linker/Input/Additional Dependencies, include
$(ProjectDir)SDL2-2.0.3/lib/x86/SDL2.lib
$(ProjectDir)SDL2-2.0.3/lib/x86/SDL2main.lib
Linker/Input/System/Subsystem/ choose
Windows (/SUBSYSTEM:WINDOWS)
*/

enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};


int main(int argc, char** argv)
{
	LOG("Starting game '%s'...", TITLE);
	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	
	return 0;
}