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
		//Bug frames
		anim.frames.pushBack({ 0, 0, 32, 32 });
		anim.frames.pushBack({ 32, 0, 32, 32 });
		anim.frames.pushBack({ 64, 0, 32, 32 });
		anim.frames.pushBack({ 96, 0, 32, 32 });
		anim.frames.pushBack({ 128, 0, 32, 32 });
		anim.frames.pushBack({ 160, 0, 32, 32 });
		anim.frames.pushBack({ 192, 0, 32, 32 });
		anim.frames.pushBack({ 224, 0, 32, 32 });
		anim.frames.pushBack({ 256, 0, 32, 32 });
		anim.frames.pushBack({ 288, 0, 32, 32 });
		anim.frames.pushBack({ 320, 0, 32, 32 });
		anim.frames.pushBack({ 352, 0, 32, 32 });
		anim.frames.pushBack({ 384, 0, 32, 32 });
		anim.frames.pushBack({ 416, 0, 32, 32 });
		anim.frames.pushBack({ 448, 0, 32, 32 });
		anim.frames.pushBack({ 480, 0, 32, 32 });

		path.pushBack({ 5.0f, 5.0f });
	
		anim.speed = 0.0f;
		speed.x = -1;
		speed.y = 0;
		life = 18000; // In miliseconds
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
		{
			if (anim.finished())
				ret = false;
		}		

		position.x += speed.x;
		speed.y = -sin(0.05 * position.x);
		position.y += speed.y;

		// CRZ --- Method to orient the animation.
		float theta = atan(speed.y / speed.x);

		if (speed.x >= 0)
		{
			if (speed.y < 0)
				theta = 2 * M_PI + theta;
		}
		else
		{
			if (speed.y >= 0)
				theta = M_PI + theta;
			else
				theta = M_PI + theta;
		}

		theta = theta * (180 / M_PI);
		anim.current_frame = (int)(theta / (360.0f / 16.0f));
		// CRZ ---	

		if (collider != NULL)
		{
			SDL_Rect r = anim.peekCurrentFrame();
			collider->rect = { position.x, position.y, r.w, r.h };
		}

		return ret;
	}

};

#endif //!__ENEMY_H__
