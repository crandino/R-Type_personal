//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "ModuleSceneIntro.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleSceneSpace.h"

//=================================
// the actual class

ModuleSceneIntro::ModuleSceneIntro(Application *app, bool start_enabled) : Module(app, start_enabled)
{
	intro = NULL;
	numbers = NULL;
	fx = 0;

	// From numbers_coins animation
	numbers_coins.frames.pushBack({ 0.0f, 0.0f, 8, 7 });
	numbers_coins.frames.pushBack({ 8.0f, 0.0f, 8, 7 });
	numbers_coins.frames.pushBack({ 16.0f, 0.0f, 8, 7 });
	numbers_coins.frames.pushBack({ 24.0f, 0.0f, 8, 7 });
	numbers_coins.frames.pushBack({ 32.0f, 0.0f, 8, 7 });
	numbers_coins.frames.pushBack({ 40.0f, 0.0f, 8, 7 });
	numbers_coins.frames.pushBack({ 48.0f, 0.0f, 8, 7 });
	numbers_coins.frames.pushBack({ 56.0f, 0.0f, 8, 7 });
	numbers_coins.frames.pushBack({ 64.0f, 0.0f, 8, 7 });
	numbers_coins.frames.pushBack({ 72.0f, 0.0f, 8, 7 });
	numbers_coins.speed = 0.0f;
	numbers_coins.loop = false;

	press_space_glow.frames.pushBack({ 0.0f, 0.0f, 160, 7 });
	press_space_glow.frames.pushBack({ 0.0f, 8.0f, 160, 7 });
	press_space_glow.frames.pushBack({ 0.0f, 16.0f, 160, 7 });
	press_space_glow.frames.pushBack({ 0.0f, 24.0f, 160, 7 });
	press_space_glow.frames.pushBack({ 0.0f, 32.0f, 160, 7 });
	press_space_glow.frames.pushBack({ 0.0f, 32.0f, 160, 7 });
	press_space_glow.frames.pushBack({ 0.0f, 32.0f, 160, 7 });
	press_space_glow.frames.pushBack({ 0.0f, 32.0f, 160, 7 });
	press_space_glow.frames.pushBack({ 0.0f, 32.0f, 160, 7 });
	press_space_glow.frames.pushBack({ 0.0f, 32.0f, 160, 7 });
	press_space_glow.frames.pushBack({ 0.0f, 40.0f, 160, 7 });
	press_space_glow.frames.pushBack({ 0.0f, 48.0f, 160, 7 });
	press_space_glow.frames.pushBack({ 0.0f, 56.0f, 160, 7 });
	press_space_glow.frames.pushBack({ 0.0f, 0.0f, 160, 7 });
	press_space_glow.speed = 0.15f;
	press_space_glow.loop = true;
}

ModuleSceneIntro::~ModuleSceneIntro()
{ }

// Load assets
bool ModuleSceneIntro::start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	app->input->keyboard_enabled = true;

	intro = app->textures->load("Images/IntroTuned2.png");
	numbers = app->textures->load("Sprites/NumbersBlue.png");
	press_space_to_start = app->textures->load("Images/PressSpaceToStartBlack.png");

	app->audio->playMusic("Music/Intro.ogg", 0.0f);
	fx = app->audio->loadFx("Sounds/Coin.ogg");

	app->renderer->camera.x = app->renderer->camera.y = 0.0f;
	numbers_coins.current_frame = app->coins;

	//DTM ANIMATION
	ticks = 0;
	seconds = 0;

	rects[10] = { 0.0f, 0.0f, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE }; // full screen rect

	for (unsigned int i = 0; i < 6; i++)
	{
		rects[i] = { 420.0f * SCREEN_SIZE, 76.0f * SCREEN_SIZE, 56 * SCREEN_SIZE, 56 * SCREEN_SIZE };
	}
	source_rects[0] = { 9.0f, 3.0f, 74, 75 };
	source_rects[1] = { 92.0f, 27.0f, 70, 75 };
	source_rects[2] = { 153.0f, 3.0f, 74, 75 };
	source_rects[3] = { 227.0f, 3.0f, 87, 75 };
	source_rects[4] = { 314.0f, 3.0f, 82, 75 };
	source_rects[5] = { 396.0f, 3.0f, 65, 75 };

	title = app->textures->load("Images/RtypeLogo.png");

	return ret;
}

// Delete assets
bool ModuleSceneIntro::cleanUp()
{
	LOG("Unloading Intro scene");

	app->textures->unload(intro);
	app->textures->unload(numbers);
	app->textures->unload(press_space_to_start);
	app->textures->unload(title);

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::update()
{
	// start animation
	if (ticks < 216) //420)
	{
		if (ticks < 80) // move letters to the left
		{
			for (unsigned int i = 7; i > 0; i--)
			{
				rects[i - 1].x -= 5.0f * SCREEN_SIZE;

				SDL_RenderCopy(app->renderer->renderer, title, &source_rects[i - 1], &rects[i - 1]);
			}
		}

		else if (ticks < 100) // small pause
		{
			for (unsigned int i = 7; i > 0; i--)
			{
				SDL_RenderCopy(app->renderer->renderer, title, &source_rects[i - 1], &rects[i - 1]);
			}
		}

		else if (ticks < 156) // move letters to the right
		{
			for (unsigned int i = 7; i > 0; i--)
			{
				rects[i - 1].x += (i - 1.0f)  * SCREEN_SIZE;

				SDL_RenderCopy(app->renderer->renderer, title, &source_rects[i - 1], &rects[i - 1]);
			}
		}
		else if (ticks < 216) // move letters to the right
		{
			for (unsigned int i = 7; i > 0; i--)
			{
				rects[i - 1].y += SCREEN_SIZE;

				SDL_RenderCopy(app->renderer->renderer, title, &source_rects[i - 1], &rects[i - 1]);
			}
		}

		// update ticks counter
		ticks++;
	}

	else
	{
		// Draw everything
		app->renderer->blit(intro, 0.0f, 0.0f, NULL);
		if (app->coins > 0)
			app->renderer->blit(press_space_to_start, 200.0f, 97.0f, &(press_space_glow.getCurrentFrame()));

		// Coins visualization
		unsigned int units = app->coins % 10;
		numbers_coins.current_frame = units;
		app->renderer->blit(numbers, 348.0f, 113.0f, &(numbers_coins.getCurrentFrame()));

		unsigned int tens = (app->coins / 10) % 10;
		numbers_coins.current_frame = tens;
		app->renderer->blit(numbers, 340.0f, 113.0f, &(numbers_coins.getCurrentFrame()));


		if (app->input->keyboard_enabled == true)
		{
			if (app->input->getKey(SDL_SCANCODE_SPACE) == KEY_UP && app->coins > 0)
			{
				app->input->keyboard_enabled = false;
				app->coins--;
				app->fade->fadeToBlack(this, app->scene, 3.0f);

			}
			if (app->input->getKey(SDL_SCANCODE_C) == KEY_UP && app->coins < 99)
			{
				app->audio->playFx(fx);
				app->coins++;
				numbers_coins.current_frame = app->coins;
			}
		}
	}
	return UPDATE_CONTINUE;
}

