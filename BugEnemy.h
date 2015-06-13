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

private:

	float angle;
	float speed_value;

public:

	DynArray<float> first_position_paths;
	DynArray<Point2d<float>> path;

	unsigned int path_position;	
	unsigned int current_path;
	bool path_found;

	BugEnemy(Application *app, SDL_Texture *texture, float pos_x) : Enemy(app)
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

		// This is a dynArray with the first position of each path,
		// that will be necessary to findPath.

		first_position_paths.pushBack(600.0f);
		first_position_paths.pushBack(1050.0f);
		first_position_paths.pushBack(1500.0f);
		first_position_paths.pushBack(1960.0f); 
		first_position_paths.pushBack(2275.0f);
		first_position_paths.pushBack(3490.0f);

		// Before creating Bug enemy, findPath method will
		// look for the corresponding path, taking its x position
		// as argument.
		unsigned int path_selected = findPath(pos_x);
		path_position = 0;

		switch (path_selected)
		{
			case(1) :
			{
				// Path number 1
				path.pushBack({ 600.0f, 110.0f });
				path.pushBack({ 550.0f, 35.0f });
				path.pushBack({ 450.0f, 30.0f });
				path.pushBack({ 410.0f, 35.0f });
				path.pushBack({ 150.0f, 300.0f });
				break;
			}
			case(2) :
			{
				// Path number 2
				path.pushBack({ 1050.0f, 110.0f });
				path.pushBack({ 1025.0f, 125.0f });
				path.pushBack({ 1000.0f, 140.0f });
				path.pushBack({ 975.0f, 125.0f });
				path.pushBack({ 950.0f, 110.0f });
				path.pushBack({ 925.0f, 125.0f });
				path.pushBack({ 900.0f, 140.0f });
				path.pushBack({ 875.0f, 125.0f });
				path.pushBack({ 850.0f, 110.0f });
				path.pushBack({ 825.0f, 125.0f });
				path.pushBack({ 800.0f, 140.0f });
				path.pushBack({ 775.0f, 125.0f });
				path.pushBack({ 750.0f, 110.0f });
				path.pushBack({ 725.0f, 125.0f });
				path.pushBack({ 700.0f, 140.0f });
				path.pushBack({ 675.0f, 125.0f });
				break;
			}
			case(3) :
			{
				// Path number 3
				path.pushBack({ 1500.0f, 80.0f });
				path.pushBack({ 1450.0f, 100.0f });
				path.pushBack({ 1100.0f, 100.0f });
				break;
			}
			case(4) :
			{
				// Path number 4
				path.pushBack({ 1960.0f, 80.0f });
				path.pushBack({ 1940.0f, 90.0f });
				path.pushBack({ 1920.0f, 100.0f });
				path.pushBack({ 1500.0f, 100.0f });
				break;
			}
			case(5) :
			{
				// Path number 5
				path.pushBack({ 2275.0f, 170.0f });
				path.pushBack({ 2165.0f, 120.0f });
				path.pushBack({ 2120.0f, 80.0f });
				path.pushBack({ 2165.0f, 40.0f });
				path.pushBack({ 2210.0f, 80.0f });
				path.pushBack({ 2080.0f, 160.0f });
				path.pushBack({ 1800.0f, 160.0f });
				break;
			}
			case(6) :
			{
				// Path number 6
				path.pushBack({ 3490.0f, 70.0f });
				path.pushBack({ 3410.0f, 180.0f });
				path.pushBack({ 3320.0f, 180.0f });
				path.pushBack({ 3240.0f, 140.0f });
				path.pushBack({ 3100.0f, 30.0f });
				break;
			}
		}
		
		anim.speed = 0.0f;
		speed_value = 2.0f;
		angle = 0.0f;
		graphics = texture;

		score_points = 200;
	}

	~BugEnemy()
	{ }

	unsigned int findPath(float position_x) const
	{
		unsigned int path_selected = 0;
		for (unsigned int i = 0; i < first_position_paths.getNumElements(); i++)
		{
			if ( first_position_paths[i] <= position_x)
				path_selected = i + 1;
		}
		return path_selected;
	}

	void orientTo(const Point2d<float> &position_destiny)
	{
		// https://www.mathsisfun.com/geometry/unit-circle.html
		// It might be helpful!

		float dx = position_destiny.x - position.x;
		float dy = position_destiny.y - position.y;
		
		angle = atan(dy/dx);

		if (dx >= 0)
		{
			if (dy < 0)
				angle = 2.0f * M_PI + angle;
		}
		else
		{
			angle = M_PI + angle;
		}

		speed.x = cos(angle) * speed_value;
		speed.y = sin(angle) * speed_value;
	}

	bool update()
	{
		bool ret = true;	

		if (position.isClosedTo(path[path_position], 1.0f))
		{ 		
			if (path_position < path.getNumElements() - 1)
				path_position++;
			else
				speed.x = speed.y = 0;
		}
		else
		{
			orientTo(path[path_position]);
		}		

		position.x += speed.x;
		position.y += speed.y;

		anim.current_frame = (int)( angle * (180.0f / M_PI) / (360.0f / anim.frames.getNumElements()));

		if (collider != NULL)
		{
			SDL_Rect r = anim.peekCurrentFrame();
			collider->rect = { position.x, position.y, r.w , r.h  };
		}

		return ret;
	}

};

#endif //!__ENEMY_H__
