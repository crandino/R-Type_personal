//=================================
// include guard
#ifndef __ENEMY_H__
#define __ENEMY_H__
//=================================
// forward declared dependencies

//=================================
// included dependencies

//=================================
// the actual class

class Enemy
{

public:

	Application *app;

	SDL_Texture *graphics;
	Point2d<int> position;
	Point2d<int> speed;
	Animation anim;
	Uint32 born;
	Uint32 life;
	bool fx_played;
	unsigned int fx;
	Collider *collider;

	// CRZ
	Uint32 time_to_attack;
	Uint32 attacks;
	Uint32 attack_frequency;
	
	Enemy(Application *parent) : app(parent), fx(0), born(0), life(0), fx_played(false), attacks(0), time_to_attack(0), collider(NULL)
	{
		position.setZero();
		speed.setZero();
	}

	Enemy(const Enemy &e) : graphics(e.graphics), anim(e.anim), position(e.position), speed(e.speed), fx_played(false)
	{
		collider = e.collider;
		attack_frequency = e.attack_frequency;
		attacks = e.attacks;
		time_to_attack = e.time_to_attack;
		fx = e.fx;
		born = e.born;
		life = e.life;
	}

	~Enemy()
	{
		if (collider)
			collider->to_delete = true;
	}

	//virtual bool start() { return true; }
	virtual bool update() { return true; }
	//virtual bool cleanUp() { return true; }
};


#endif //!__ENEMY_H__