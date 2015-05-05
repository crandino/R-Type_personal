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
		graphics = app->textures->load("Sprites/Pata_pata.png");
	}

	PataEnemy(const PataEnemy &e) : Enemy(e)
	{ }

	~PataEnemy()
	{ 
		LOG("Unloading particles");
		app->textures->unload(graphics);
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

		if (collider != NULL)
		{
			SDL_Rect r = anim.peekCurrentFrame();
			collider->rect = { position.x, position.y, r.w, r.h };
		}

		return ret;
	}

};

#endif //!__ENEMY_H__
