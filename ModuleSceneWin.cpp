//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneWin.h"

//=================================
// the actual class

ModuleSceneWin::ModuleSceneWin(Application *app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	fx = 0;

}

ModuleSceneWin::~ModuleSceneWin()
{ }

// Load assets
bool ModuleSceneWin::start()
{
	LOG("Loading Win assets");
	bool ret = true;

	graphics = app->textures->load("Images/Win.png");
	//fx = app->audio->loadFx("Sounds/Coin.ogg");
	app->renderer->camera.x = app->renderer->camera.y = 0;
	return ret;
}

// Delete assets
bool ModuleSceneWin::cleanUp()
{
	LOG("Unloading Win scene");

	app->textures->unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleSceneWin::update()
{
	// Draw everything
	app->renderer->blit(graphics, 0.f, 0.f, NULL);

	if (app->input->keyboard_enabled == true)
	{
		if (app->input->getKey(SDL_SCANCODE_SPACE) == KEY_UP)
		{
			app->fade->fadeToBlack(this, app->scene_intro, 3.0f);
		}
	}

	return UPDATE_CONTINUE;
}