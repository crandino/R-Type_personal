//=================================
// include guard
#ifndef __BUGENEMY_H__
#define __BUGENEMY_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Enemy.h"
#include <math.h>
//=================================
// the actual class

class BugEnemy : public Enemy
{

public:

	BugEnemy(Application *app, SDL_Texture *texture) : Enemy(app)
	{
		//Pata-pata frames
		anim.frames.pushBack({ 5, 6, 21, 24 });
	
		anim.speed = 0.1f;
		speed.x = -1;
		speed.y = 0;
		life = 12000; // In miliseconds
		attack_frequency = 2000; // In miliseconds
		graphics = texture;
	}

	~BugEnemy()
	{ }

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
		speed.y = -sin(0.05 * position.x);
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
