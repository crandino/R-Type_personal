//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Application.h"
#include "ModuleSceneSpace.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInterface.h"
#include "ModuleEnemy.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
//=================================
// the actual code

const SDL_Rect& scale(const SDL_Rect& rect)
{
	SDL_Rect *tmp = new SDL_Rect(rect);
	tmp->x *= SCALE_FACTOR;
	tmp->y *= SCALE_FACTOR;
	tmp->w *= SCALE_FACTOR;
	tmp->h *= SCALE_FACTOR;
	return *tmp;
}

ModuleSceneSpace::ModuleSceneSpace(Application *app, bool start_enabled) : Module(app, start_enabled)
{
	boundary_level = NULL;
}

ModuleSceneSpace::~ModuleSceneSpace()
{ }

// Load assets
bool ModuleSceneSpace::start()
{
	LOG("Loading space scene");

	boundary_level = app->textures->load("Sprites/boundary_level.png");

	app->player->enable();
	app->game_interface->enable();
	app->collision->enable();
	app->enemy->enable();
	app->particles->enable();	
	app->audio->playMusic("Music/Level1.ogg", 1.0f);

	// Speeds added
	scroll_player_speed = (int)(0.5 * SCALE_FACTOR); //0.333f;
	// Map speed IMPORTANT!
	scroll_camera_speed = (int)(0.5 * SCALE_FACTOR); //1.75f;

	left_limit = (10 * SCALE_FACTOR);
	right_limit = (SCREEN_WIDTH - 32) * SCALE_FACTOR;

	app->renderer->camera.x = app->renderer->camera.y = 0;

	// Wall collider
	app->collision->addCollider(scale({    0,  224, 3930,  16 }), COLLIDER_WALL);
	app->collision->addCollider(scale({  142,  192,   64,  32 }), COLLIDER_WALL);
	app->collision->addCollider(scale({  206,  208,   64,  16 }), COLLIDER_WALL);
	app->collision->addCollider(scale({  592,  208,   64,  16 }), COLLIDER_WALL);
	app->collision->addCollider(scale({ 1232,  208,   64,  16 }), COLLIDER_WALL);
	app->collision->addCollider(scale({  720,  192,   64,  32 }), COLLIDER_WALL);
	app->collision->addCollider(scale({ 1376,   16,  112,  80 }), COLLIDER_WALL);
	app->collision->addCollider(scale({ 1376,  144,  112,  80 }), COLLIDER_WALL);
	app->collision->addCollider(scale({ 1376,    0,  560,  16 }), COLLIDER_WALL);
	app->collision->addCollider(scale({ 1680,   16,   64,  16 }), COLLIDER_WALL);

	return true;
}

// Unload assets
bool ModuleSceneSpace::cleanUp()
{
	LOG("Unloading space scene");

	app->textures->unload(boundary_level);
	app->player->disable();
	app->game_interface->disable();
	app->enemy->disable();
	app->particles->disable();
	app->collision->disable();
	app->audio->stopAllMusic(0.1f);
	return true;
}

// Update: draw background
update_status ModuleSceneSpace::update()
{
	// Move camera forward
	app->player->position.x += scroll_player_speed;
	app->renderer->camera.x -= scroll_camera_speed;
	left_limit += scroll_player_speed;
	right_limit += scroll_player_speed;

	// Draw everything
	app->renderer->blit(boundary_level, 0, 0, NULL);

	return UPDATE_CONTINUE;
}