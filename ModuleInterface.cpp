//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Application.h"
#include "ModuleSceneSpace.h"
#include "ModulePlayer.h"
#include "ModuleInterface.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "BasicPlayerShot.h"
//=================================
// the actual code

ModuleInterface::ModuleInterface(Application *app, bool start_enabled) : Module(app, start_enabled)
{
	// From numbers_points animation
	numbers_points.frames.pushBack({ 0, 0, 8, 7 });
	numbers_points.frames.pushBack({ 8, 0, 8, 7 });
	numbers_points.frames.pushBack({ 16, 0, 8, 7 });
	numbers_points.frames.pushBack({ 24, 0, 8, 7 });
	numbers_points.frames.pushBack({ 32, 0, 8, 7 });
	numbers_points.frames.pushBack({ 40, 0, 8, 7 });
	numbers_points.frames.pushBack({ 48, 0, 8, 7 });
	numbers_points.frames.pushBack({ 56, 0, 8, 7 });
	numbers_points.frames.pushBack({ 64, 0, 8, 7 });
	numbers_points.frames.pushBack({ 72, 0, 8, 7 });
	numbers_points.speed = 0.0f;
	numbers_points.loop = false;
}

ModuleInterface::~ModuleInterface()
{ }

// Load assets
bool ModuleInterface::start()
{
	LOG("Loading Interface");

	img_life = app->textures->load("Sprites/Life.png");
	img_beam = app->textures->load("Sprites/Beam.png");
	img_p1 = app->textures->load("Sprites/P1.png");
	img_hi = app->textures->load("Sprites/HighScore.png");
	img_numbers_interface = app->textures->load("Sprites/NumbersInterface.png");
	img_bar = app->textures->load("Sprites/ShotBar.png");
	charge_beam = app->textures->load("Sprites/BeamFill.png");

	return true;
}

// Unload assets
bool ModuleInterface::cleanUp()
{
	LOG("Unloading Interface");

	app->textures->unload(img_life);
	app->textures->unload(img_beam);
	app->textures->unload(img_p1);
	app->textures->unload(img_hi);
	app->textures->unload(img_numbers_interface);
	app->textures->unload(img_bar);
	app->textures->unload(charge_beam);

	return true;
}

// Update: draw background
update_status ModuleInterface::update()
{
	for (unsigned int i = 1; i <= app->player->lifes; i++)
		app->renderer->blit(img_life, app->scene->origin + (8 * i), 241.0f, NULL);
	
	app->renderer->blit(img_beam, app->scene->origin + 92.0f, 241.0f, NULL);
	app->renderer->blit(img_bar, app->scene->origin + 138.0f, 241.0f, NULL);
	app->renderer->blit(img_p1, app->scene->origin + 32.0f, 250.0f, NULL);
	app->renderer->blit(img_hi, app->scene->origin + 156.0f, 249.0f, NULL);

	//Beam rectangle to charge
	if (app->player->charging == true)
	{	
		Uint32 now = SDL_GetTicks();
		unsigned int max_beam = (now - app->player->start_charging) * 128 / 1200;
		if (max_beam > 128) { max_beam = 128;}
		for (unsigned int i = 0; i < max_beam; i++)
			app->renderer->blit(charge_beam, app->scene->origin + (141 + i), 243.0f, NULL);
	}

	print_score(app->scene->origin);
	
	return UPDATE_CONTINUE;
}

void ModuleInterface::print_score(float origin_pos_x)
{
	// Score calculation. The method calculates each number on the whole number: units, tens, hundreds, thousands and tens thousands.

	float pos_y = 250.0f;
	float number_width = 9.0f;
	origin_pos_x += 78.0f;	

	// Printing tens_thousands..
	if (app->player->player_points > 9999)
	{
		numbers_points.current_frame = (app->player->player_points / 10000) % 10;
		app->renderer->blit(img_numbers_interface, origin_pos_x, pos_y, &(numbers_points.getCurrentFrame()));
		origin_pos_x += number_width;
	}

	// Printing thousands...
	if (app->player->player_points > 999)
	{
		numbers_points.current_frame = (app->player->player_points / 1000) % 10;
		app->renderer->blit(img_numbers_interface, origin_pos_x, pos_y, &(numbers_points.getCurrentFrame()));
		origin_pos_x += number_width;
	}

	// Printing hundreds...
	if (app->player->player_points > 99)
	{
		numbers_points.current_frame = (app->player->player_points / 100) % 10;
		app->renderer->blit(img_numbers_interface, origin_pos_x, pos_y, &(numbers_points.getCurrentFrame()));
		origin_pos_x += number_width;
	}

	// Printing tens...
	if (app->player->player_points > 9)
	{
		numbers_points.current_frame = (app->player->player_points / 10) % 10;
		app->renderer->blit(img_numbers_interface, origin_pos_x, pos_y, &(numbers_points.getCurrentFrame()));
		origin_pos_x += number_width;
	}

	// Printing units
	numbers_points.current_frame = app->player->player_points % 10;
	app->renderer->blit(img_numbers_interface, origin_pos_x, pos_y, &(numbers_points.getCurrentFrame()));

}