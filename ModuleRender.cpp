//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "ModuleRender.h"
//=================================
// the actual class

ModuleRender::ModuleRender(Application *app) : Module(app)
{
	renderer = NULL;
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;
}

// Destructor
ModuleRender::~ModuleRender()
{
}

bool ModuleRender::init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if (VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(app->window->window, -1, flags);

	if (renderer == NULL)
	{
		LOG("Renderer could not be created! SDL_Error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

update_status ModuleRender::update()
{
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	return UPDATE_CONTINUE;
}

bool ModuleRender::cleanUp()
{
	LOG("Destroying renderer");

	// Destroy window
	if (renderer != NULL)
		SDL_DestroyRenderer(renderer);

	return true;
}

//Blit to screen
bool ModuleRender::blit(SDL_Texture *texture, int x, int y, SDL_Rect *section, float speed)
{
	return true;
}