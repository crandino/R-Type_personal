//=================================
// included dependencies
#include "ModuleAudio.h"
#include "SDL\include\SDL.h"

#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )
//=================================
// the actual code

ModuleAudio::ModuleAudio(Application *app, bool start_enabled) : Module(app, start_enabled), music(NULL)
{ }

// Destructor
ModuleAudio::~ModuleAudio()
{ };


// Called before render is available
bool ModuleAudio::init()
{
	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s", SDL_GetError());
		ret = false;
	}

	// load support for the OGG format
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if ((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		ret = false;
	}

	// Initialize SDL_mixer
	// int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize)
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_Mixer Error: %s", Mix_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleAudio::cleanUp()
{
	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if (music != NULL)
	{
		Mix_FreeMusic(music);
	}

	doubleNode<Mix_Chunk*>* item;

	for (item = fx.getFirst(); item != NULL; item = item->next)
	{
		Mix_FreeChunk(item->data);
	}

	fx.clear();
	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	return true;
}

// Play a music file
bool ModuleAudio::playMusic(const char *path, float fade_time)
{
	if (isEnabled() == false)
		return false;

	bool ret = true;

	// We stop or fade out any music playing at the time of execution of
	// playMusic.
	if (music != NULL)
	{
		if (fade_time > 0.0f)
			// Milliseconds of time that the fade-out effect should take
			Mix_FadeOutMusic((int)(fade_time * 1000.0f));
		else
			// Stop playback of music.
			Mix_HaltMusic();
		
		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if (music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if (fade_time > 0.0f)
		{
			if (Mix_FadeInMusic(music, -1, (int)(fade_time * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			//int Mix_PlayMusic(Mix_Music *music, int loops)
			if (Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

// Load a WAV in memory
unsigned int ModuleAudio::loadFx(const char *path)
{

	unsigned int ret = 0;

	if (isEnabled() == false)
		return ret;
		
	Mix_Chunk *chunk = Mix_LoadWAV(path);

	if (chunk == NULL)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		fx.add(chunk);
		ret = fx.count();
	}

	return ret;
}

// Play a previously loaded WAV
bool ModuleAudio::playFx(unsigned int id, int repeat)
{
	if (isEnabled() == false)
		return false;

	bool ret = false;

	Mix_Chunk *chunk = NULL;

	if (fx.at(id, chunk) == true)
	{
		Mix_PlayChannel(-1, chunk, repeat);
		ret = true;
	}

	return ret;
}

bool ModuleAudio::stopAllMusic(float fade_time)
{
	if (isEnabled() == false)
		return false;

	bool ret = true;

	// We stop or fade out any music playing at the time of execution of
	// playMusic.
	if (music != NULL)
	{
		if (fade_time > 0.0f)
			// Milliseconds of time that the fade-out effect should take
			Mix_FadeOutMusic((int)(fade_time * 1000.0f));
		else
			// Stop playback of music.
			Mix_HaltMusic();

		// this call blocks until fade out is done
		Mix_FreeMusic(music);

		music = NULL;
	}

	return ret;
}
