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

public:

	float speed_value;

	DynArray<Point2d<float>> *path1;
	DynArray<Point2d<float>> *path2;
	DynArray<Point2d<float>> *path3;
	DynArray<Point2d<float>> *path4;
	DynArray<Point2d<float>> *path5;
	DynArray<Point2d<float>> *path6;
	unsigned int path_position;

	DynArray<DynArray<Point2d<float>>*> path_set;
	unsigned int current_path;
	bool path_found;

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

		path1 = new DynArray<Point2d<float>>;
		path1->pushBack({ 600 , 110 });
		path1->pushBack({ 550 , 35 });
		path1->pushBack({ 450 , 30 });
		path1->pushBack({ 410 , 35 });
		path1->pushBack({ 150 , 300 });
		path_set.pushBack(path1);

		path2 = new DynArray<Point2d<float>>;
		path2->pushBack({ 1050 , 11  });
		path2->pushBack({ 1025 , 125 });
		path2->pushBack({ 1000 , 140 });
		path2->pushBack({ 975 , 125 });
		path2->pushBack({ 950 , 110 });
		path2->pushBack({ 925 , 125 });
		path2->pushBack({ 900 , 140 });
		path2->pushBack({ 875 , 125 });
		path2->pushBack({ 850 , 110 });
		path2->pushBack({ 825 , 125 });
		path2->pushBack({ 800 , 140 });
		path2->pushBack({ 775 , 125 });
		path2->pushBack({ 750 , 110 });
		path2->pushBack({ 725 , 125 });
		path2->pushBack({ 700 , 140 });
		path2->pushBack({ 675 , 125 });
		path_set.pushBack(path2);

		path3 = new DynArray<Point2d<float>>;
		path3->pushBack({ 1500 , 80 });
		path3->pushBack({ 1450 , 100 });
		path3->pushBack({ 1100 , 100 });
		path_set.pushBack(path3);

		path4 = new DynArray<Point2d<float>>;
		path4->pushBack({ 1960 , 80 });
		path4->pushBack({ 1940 , 90 });
		path4->pushBack({ 1920 , 100 });
		path4->pushBack({ 1500 , 100 });
		path_set.pushBack(path4);

		path5 = new DynArray<Point2d<float>>;
		path5->pushBack({ 2275 , 170 });
		path5->pushBack({ 2165 , 120 });
		path5->pushBack({ 2120 , 80 });
		path5->pushBack({ 2165 , 40 });
		path5->pushBack({ 2210 , 80 });
		path5->pushBack({ 2080 , 160 });
		path5->pushBack({ 1800 , 160 });
		path_set.pushBack(path5);

		path6 = new DynArray<Point2d<float>>;
		path6->pushBack({ 3490 , 70 });
		path6->pushBack({ 3410 , 180 });
		path6->pushBack({ 3320 , 180 });
		path6->pushBack({ 3240 , 140 });
		path6->pushBack({ 3100 , 30 });
		path_set.pushBack(path6);

		path_found = false;
		current_path = 0;
	
		path_position = 0;
		anim.speed = 0.0f;
		speed_value = 2.0f;
		angle = 0;
		life = 50000; // In miliseconds
		graphics = texture;

		points = 200;
	}

	~BugEnemy()
	{
		for (unsigned int i = 0; i < path_set.getNumElements(); i++)
		{
			delete path_set[i];
		}
	}

	bool findPath()
	{
		DynArray<Point2d<float>> *tmp;
		for (unsigned int i = 0; i < path_set.getNumElements(); i++)
		{
			tmp = path_set[i];
			if ( (*tmp)[0].x <= position.x)
				current_path = i;
		}
		return true;
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

		if (path_found != true)
			path_found = findPath();

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

		if (position.isClosedTo((*path_set[current_path])[path_position], 1.0f ))
		{ 		
			if (path_position < (*path_set[current_path]).getNumElements() - 1)
				path_position++;
			else
				speed.x = speed.y = 0;
		}
		else
		{
			orientTo((*path_set[current_path])[path_position]);
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
