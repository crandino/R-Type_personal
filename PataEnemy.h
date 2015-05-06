//=================================
// include guard
#ifndef __PATAENEMY_H__
#define __PATAENEMY_H__
//=================================
// forward declared dependencies

//=================================
// included dependencies
#include "Enemy.h"
//=================================
// the actual class

class PataEnemy : public Enemy
{

public:

	PataEnemy(Application *app) : Enemy(app)
	{
		//Pata-pata frames
		anim.frames.pushBack({ 5, 6, 21, 24 });
		anim.frames.pushBack({ 38, 6, 21, 24 });
		anim.frames.pushBack({ 71, 6, 21, 24 });
		anim.frames.pushBack({ 104, 6, 21, 24 });
		anim.frames.pushBack({ 137, 6, 21, 24 });
		anim.frames.pushBack({ 170, 6, 21, 24 });
		anim.frames.pushBack({ 203, 6, 21, 24 });
		anim.frames.pushBack({ 236, 6, 21, 24 });
		anim.speed = 0.1f;
		speed.x = -1;
		speed.y = 0;
		life = 12000;
		attack_frequency = 2000; // In miliseconds	
	}

	PataEnemy(PataEnemy *e) : Enemy(e)
	{ }

	~PataEnemy()
	{ }

	bool start()
	{
		LOG("Loading sprite for Pata-pata");
		graphics = app->textures->load("Sprites/Pata_pata.png");

		return true;
	}

	bool cleanUp()
	{
		LOG("Unloading sprite for Pata-pata");
		app->textures->unload(graphics);

		return true;
	}

	bool update()
	{
		bool ret = true;

		if (life > 0)
		{
			if ((SDL_GetTicks() - born) > life)
				ret = false;
		}
		else
			if (anim.finished())
				ret = false;

		position.x += speed.x;
		position.y += speed.y;

		// CRZ ----
		// Proposal for frequency attacking system, CRZ
		time_to_attack = (SDL_GetTicks() - born) - (attacks * attack_frequency);
		if (SDL_TICKS_PASSED(time_to_attack, attack_frequency) == true)
		{
			app->particles->addParticle(app->particles->pata_shot, position.x, position.y + 10, COLLIDER_ENEMY_SHOT);
			attacks++;
		}
		// ---- CRZ

		if (collider != NULL)
		{
			SDL_Rect r = anim.peekCurrentFrame();
			collider->rect = { position.x, position.y, r.w, r.h };
		}

		return ret;
	}

};

#endif //!__ENEMY_H__
