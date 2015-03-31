#ifndef __MODULE_H__
#define __MODULE_H__

class Module
{
public:
	Module() {};

	virtual bool init() { return true; }
	virtual update_status update() { return UPDATE_CONTINUE; }
	virtual bool cleanUp() { return true; }

};

#endif // !__MODULE_H__
