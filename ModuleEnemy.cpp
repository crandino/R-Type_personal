//=================================
// included dependencies
#include "Application.h"
#include "ModuleEnemy.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneSpace.h"
#include "ModuleSceneWin.h"
#include "PataEnemy.h"
//=================================
// the actual code

ModuleEnemy::ModuleEnemy(Application *app, bool start_enabled) : Module(app, start_enabled)
{ 
	pata = new PataEnemy(app);

	addEnemyClass(pata);
}

ModuleEnemy::~ModuleEnemy()
{ 
	delete pata;
}

// Load assets
bool ModuleEnemy::start()
{
	LOG("Loading enemies...");

	// Adding enemies
	addEnemy(PATA_ENEMY, 700, 100, COLLIDER_ENEMY);
	addEnemy(PATA_ENEMY, 650, 125, COLLIDER_ENEMY);
	addEnemy(PATA_ENEMY, 400, 150, COLLIDER_ENEMY);

	doubleNode<Enemy*> *item = enemy_collection.getFirst();

	while (item != NULL)
	{
		item->data->start();
		item = item->next;
	}

	return true;
}

bool ModuleEnemy::cleanUp()
{
	doubleNode<Enemy*> *item = active.getLast();

	while (item != NULL)
	{
		delete item->data;
		item = item->previous;
	}

	active.clear();

	item = enemy_collection.getLast();

	while (item != NULL)
	{
		item->data->cleanUp();
		item = item->previous;
	}

	return true;
}

// Update: draw enemies
update_status ModuleEnemy::update()
{
	doubleNode<Enemy*>* tmp = active.getFirst();
	doubleNode<Enemy*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		Enemy *e = tmp->data;
		tmp_next = tmp->next;

		if (e->update() == false)
		{
			delete e;
			active.del(tmp);
		}
		else if (SDL_GetTicks() >= e->born)
		{
			app->renderer->blit(e->graphics, e->position.x, e->position.y, &(e->anim.getCurrentFrame()));
			if (e->fx_played == false)
			{
				e->fx_played = true;
				app->audio->playFx(e->fx);
			}
		}
		tmp = tmp_next;
	}
		
	return UPDATE_CONTINUE;
}

void ModuleEnemy::onCollision(Collider *col1, Collider *col2)
{ 
	doubleNode<Enemy*> *item = active.getFirst();
	while (item != NULL && item->data->collider != col1)
		item = item->next;

	if (item != NULL)
	{
		app->particles->addParticle(app->particles->explosion, col1->rect.x, col1->rect.y);
		delete item->data;
		active.del(item);
	}

	/*if (!app->particles->pata_explosion.anim.finished()){
		app->fade->fadeToBlack(app->scene, app->scene_win, 3.0f);*/
}

void ModuleEnemy::addEnemy(enemy_types type, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Enemy *e = NULL;

	switch (type)
	{
	case(PATA_ENEMY) : e = new PataEnemy(app);
		break;
	}

	e->born = SDL_GetTicks() + delay;
	e->position.x = x;
	e->position.y = y;

	if (collider_type != COLLIDER_NONE)
	{
		e->collider = app->collision->addCollider({ e->position.x, e->position.y, 0, 0 }, collider_type, this);
	}

	if (e != NULL)
		active.add(e);
}
