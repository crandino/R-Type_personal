//=================================
// include guard
#ifndef __MODULEINTERFACE_H__
#define __MODULEINTERFACE_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Module.h"
#include "SDL\include\SDL.h"
//=================================
// the actual class

class ModuleInterface : public Module
{
public:

	SDL_Texture *img_life;
	SDL_Texture *img_beam;
	SDL_Texture *img_hi;
	SDL_Texture *img_numbers_interface;
	SDL_Texture *img_bar;
	unsigned int fx;

	int position_interface;
	int speed_interface;

	ModuleInterface(Application *app, bool start_enabled = true);
	~ModuleInterface();

	bool start();
	update_status update();
	bool cleanUp();

};

#endif // !__MODULEINTERFACE_H__