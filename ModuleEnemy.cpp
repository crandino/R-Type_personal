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
{ }

// Load assets
bool ModuleEnemy::start()
{
	LOG("Loading enemies...");

	// Adding enemies
	addEnemy(pata, 700, 100, COLLIDER_ENEMY);
	addEnemy(pata, 650, 125, COLLIDER_ENEMY);
	addEnemy(pata, 400, 150, COLLIDER_ENEMY);

	return true;
}

bool ModuleEnemy::cleanUp()
{

	delete pata;

	doubleNode<Enemy*> *item = active.getLast();

	while (item != NULL)
	{
		delete item->data;
		item = item->previous;
	}

	active.clear();
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

			// CRZ ----
			// Proposal for frequency attacking system, CRZ
			e->time_to_attack = (SDL_GetTicks() - e->born) - (e->attacks * e->attack_frequency);
			if (SDL_TICKS_PASSED(e->time_to_attack, e->attack_frequency) == true)
			{
				app->particles->addParticle(app->particles->pata_shot, e->position.x, e->position.y + 10, COLLIDER_ENEMY_SHOT);
				e->attacks++;
			}
			// ---- CRZ
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

void ModuleEnemy::addEnemy(const Enemy &enemy, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	Enemy *e = new Enemy(enemy);
	e->born = SDL_GetTicks() + delay;
	e->position.x = x;
	e->position.y = y;

	if (collider_type != COLLIDER_NONE)
	{
		e->collider = app->collision->addCollider({ e->position.x, e->position.y, 0, 0 }, collider_type, this);
	}

	active.add(e);
}
