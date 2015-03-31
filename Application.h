#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "DList.h"
//#include "Globals.h"
#include "Module.h"
#include "ModuleWindow.h"

class Application
{
private:

	DList<Module*> list_modules;
	void addModule(Module*);

public:
	
	ModuleWindow *window;

	Application();
	~Application();

	bool init();
	update_status update();
	bool cleanUp();
};

#endif // !__APPLICATION_H__
