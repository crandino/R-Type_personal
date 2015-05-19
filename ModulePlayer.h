//=================================
// include guard
#ifndef __MODULEPOINT2D_H__
#define __MODULEPOINT2D_H__
//=================================
// forward declared dependencies
//=================================
// included dependencies
#include "Module.h"
#include "Animation.h"
#include "Point2d.h"
//=================================
// the actual class

class ModulePlayer : public Module
{
public:

	SDL_Texture *graphics;
	Collider *collider;
	Animation *current_animation;
	Animation idle;
	Animation idle_to_upward;
	Animation upward_to_idle;
	Animation idle_to_downward;
	Animation downward_to_idle;
	Animation explosion;
	Point2d<int> position;
	int speed;

	// CRZ ----
	DynArray<Animation*> animation_set;
	bool active;
	// ---- CRZ

	//DTM
	// OJO!!! Aqu� no...
	unsigned int lives = 2;

	ModulePlayer(Application *app, bool start_enabled = true);
	~ModulePlayer();

	bool start();
	update_status update();
	bool cleanUp();
	void onCollision(Collider *col1, Collider *col2);

};

#endif // !__MODULEPOINT2D_H__