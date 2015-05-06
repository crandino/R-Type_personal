//=================================
// include guard
#ifndef __MODULEENEMY_H__
#define __MODULEENEMY_H__
//=================================
// forward declared dependencies
class PataEnemy;
//=================================
// included dependencies
#include "Module.h"
#include "ModuleCollision.h"
#include "Animation.h"
#include "Point2d.h"
#include "DList.h"

#include "Enemy.h"
//=================================
// the actual class

class ModuleEnemy : public Module
{

private:

	DList<Enemy*> active;
	DList<Enemy*> enemy_collection;

public:

	// List of enemies
	// Level 1
	PataEnemy *pata;

	// Level 2

	ModuleEnemy(Application *app, bool start_enabled = true);
	~ModuleEnemy();

	bool start();
	update_status update();
	bool cleanUp();
	void onCollision(Collider *col1, Collider *col2);
	
	void addEnemy(Enemy *e, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0);	
	void addEnemyClass(Enemy *enemy_class)
	{
		enemy_collection.add(enemy_class);
	}

};

#endif //!__MODULEENEMY_H__ 