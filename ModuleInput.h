//=================================
// include guard
#ifndef __MODULEINPUT_H__
#define __MODULEINPUT_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Module.h"
#include "SDL2-2.0.3\include\SDL.h"
//=================================
// the actual class

class ModuleInput : public Module
{
public:

	const Uint8 *keyboard;

	ModuleInput(Application*);
	~ModuleInput();

	bool init();
	update_status preUpdate();
	bool cleanUp();

};

#endif // !__MODULEINPUT_H__