// include guard
#ifndef __MISSILEPLAYERSHOT_H__
#define __MISSILEPLAYERSHOT_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Weapons.h"
#include "ModuleEnemy.h"
#include "Enemy.h"
#include <math.h>
//=================================
// the actual class

class MissilePlayerShot : public Weapons
{

public:

	Point2d<int> prop_position;
	SDL_Texture *propulsion;
	Animation prop_anim;
	INT32 target_delay;
	Enemy *target_enemy;
	bool targeting;
	bool target_fixed;
	float angle;

	MissilePlayerShot(Application *app, SDL_Texture *missile_texture, SDL_Texture *propulsion_texture) : Weapons(app)
	{
		graphics = missile_texture;
		propulsion = propulsion_texture;

		//Missile frames
		anim.frames.pushBack({ 108, 12, 12, 12 });
		anim.frames.pushBack({ 96, 12, 12, 12 });
		anim.frames.pushBack({ 84, 12, 12, 12 });
		anim.frames.pushBack({ 72, 12, 12, 12 });
		anim.frames.pushBack({ 60, 12, 12, 12 });
		anim.frames.pushBack({ 48, 12, 12, 12 });
		anim.frames.pushBack({ 36, 12, 12, 12 });
		anim.frames.pushBack({ 24, 12, 12, 12 });
		anim.frames.pushBack({ 12, 12, 12, 12 });
		anim.frames.pushBack({ 0, 12, 12, 12 });
		anim.frames.pushBack({ 0, 0, 12, 12 });
		anim.frames.pushBack({ 12, 0, 12, 12 });
		anim.frames.pushBack({ 24, 0, 12, 12 });
		anim.frames.pushBack({ 36, 0, 12, 12 });
		anim.frames.pushBack({ 48, 0, 12, 12 });
		anim.frames.pushBack({ 60, 0, 12, 12 });
		anim.frames.pushBack({ 72, 0, 12, 12 });
		anim.frames.pushBack({ 84, 0, 12, 12 });
		anim.frames.pushBack({ 96, 0, 12, 12 });
		anim.frames.pushBack({ 108, 0, 12, 12 });
		anim.speed = 0.5f;
		current_animation = &anim;

		//Propulsor frames
		prop_anim.frames.pushBack({ 0, 0, 14, 12 });
		prop_anim.frames.pushBack({ 14, 0, 14, 12 });
		prop_anim.frames.pushBack({ 28, 0, 12, 12 });
		prop_anim.frames.pushBack ({ 42, 0, 14, 12 });
		prop_anim.speed = 0.8f;		

		life = 10000;
		target_delay = 1000;
		targeting = false;
		target_fixed = false;
		type = MISSILE_PLAYER_SHOT;
		power = 1;
		speed.x = 2 * SCALE_FACTOR;
		speed.y = 0 * SCALE_FACTOR;
		angle = 0.0f;
	}

	~MissilePlayerShot()
	{ }

	void orientTo()
	{
		doubleNode<Enemy*> *item_enemy = app->enemy->active.getFirst();
		target_enemy = NULL;
		float min_distance = 1000000;
		float distance = min_distance;

		// The missiles look for the closer enemy
		if (target_fixed != true)
		{
			while (item_enemy != NULL)
			{
				distance = position.distanceTo(item_enemy->data->position);
				if (distance < min_distance) // && item_enemy->data != app->particles->active_missiles.getLast()->previous->data->target_enemy
				{
					min_distance = distance;
					target_enemy = item_enemy->data;
				}
				item_enemy = item_enemy->next;
				target_fixed = true;
			}
		}


		if (target_enemy != NULL)
		{
			float dx = target_enemy->position.x - position.x;
			float dy = target_enemy->position.y - position.y;

			angle = atan(dy / dx);

			if (dx >= 0)
			{
				if (dy < 0)
					angle = 2.0f * M_PI + angle;
			}
			else
			{
				angle = M_PI + angle;
			}

			int speed_value = 3 * SCALE_FACTOR;

			speed.x = (int)(cos(angle) * speed_value);
			speed.y = (int)(sin(angle) * speed_value);
		}
	}

	bool update()
	{
		bool ret = true;

		// We calculate the correct position of the missile propulsion, 
		// following the missile itself;
		int radius = 6 * SCALE_FACTOR;

		prop_position.x = (position.x) - (cos(angle) * radius);
		prop_position.y = (position.y) - (sin(angle) * radius);
		app->renderer->blit(propulsion, prop_position.x, prop_position.y, &(prop_anim.getCurrentFrame()));


		if (life > 0)
		{
			if ((SDL_GetTicks() - born) > life)
				ret = false;
		}
		else
			if (anim.finished())
				ret = false;

		if (SDL_GetTicks() - born > target_delay )
			targeting = true;
		
		if (targeting == true)
			orientTo();

		position.x += speed.x;
		position.y += speed.y;

		current_animation->current_frame = (int)(angle * (180.0f / M_PI) / (360.0f / current_animation->frames.getNumElements()));

		if (collider != NULL)
		{
			SDL_Rect r = current_animation->peekCurrentFrame();
			collider->rect = { position.x, position.y, r.w * SCALE_FACTOR, r.h * SCALE_FACTOR };
		}

		return ret;
	}

};

#endif //!__MISSILEPLAYERSHOT_H__