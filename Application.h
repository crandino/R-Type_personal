#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "DList.h"

class Application
{
private:
	DList<Module*> list_modules;
	void addModule(Module*);

public:
	Application() {};
	~Application() {};

	bool init() { return true; }
	update_status update() { return UPDATE_CONTINUE; }
	bool cleanUp() { return true; }
};



#endif // !__APPLICATION_H__
