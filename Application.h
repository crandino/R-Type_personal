#ifndef __APPLICATION_H__
#define __APPLICATION_H__

class Application
{
private:

public:
	Application() {};
	~Application() {};

	bool init() { return true; }
	update_status update() { return UPDATE_ERROR; }
	bool cleanUp() { return true; }
};



#endif // !__APPLICATION_H__
