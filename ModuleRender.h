//=================================
// include guard
#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__
//=================================
// forward declared dependencies
class Application;
//=================================
// included dependencies
#include "Module.h"
#include "SDL2-2.0.3\include\SDL.h"
//=================================
// the actual class

class ModuleRender : public Module
{
public:

	SDL_Renderer *renderer;
	SDL_Rect camera;

	ModuleRender(Application*);
	~ModuleRender();

	bool init();
	update_status update();
	bool cleanUp();

	bool blit(SDL_Texture *texture, int x, int y, SDL_Rect *section, float speed = 1.0f);
	
};

#endif // !__MODULERENDER_H__