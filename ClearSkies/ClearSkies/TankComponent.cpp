#include "TankComponent.h"
#include "Actor.h"
#include <Game.h>
#include <assert.h>
#include "GOComponentFactory.h"
#include <AngleConvert.h>
#include "DestroyActorEvent.h"
#include <Timer.h>
#include "PlayState.h"
#include "PlayerDeathEvent.h"
#include "PlayerSpawnEvent.h"
#include "MoveActorEvent.h"
#include <AudioManager.h>
const char* TankComponent::TYPENAME="TankComponent";

static GOComponent* Create()
{
	return new TankComponent();
}

static const bool shadow = TheGOComponentFactory::Instance()->AddComponentFunc(TankComponent::TYPENAME,
	Create);

void TankComponent::Draw()const
{

}

void TankComponent::PostInit()
{
	PlayerSpawnEventPtr spawn= new PlayerSpawnEvent();
	//let everybody know we've been made
	spawn->spawnID_=(parent_->GetID());
	spawn->livesLeft_=lives_;
	EventPtr eve= spawn.DynamicCast(EventPtr());
	TheEventStore::Instance()->AnnounceEvent(eve);
}


void TankComponent::Update()
{
	if(hit_)
	{
		//if the tank has been hit
		spawnTimer_-=TheTimer::Instance()->GetDt();
		if(spawnTimer_<=0)
		{
			if(spawnDistance_==0)
			{
				//assume here they want to move to a specific position
				MoveActorEventPtr posMove= new MoveActorEvent();
				posMove->pos_=spawnPosition_;
				posMove->SetTargetID(parent_->GetID());
				EventPtr eve= posMove.DynamicCast(EventPtr());
				TheEventStore::Instance()->AddEvent(eve);
			}
			else
			{
				// this moves  the player in a random direction, by the spawn distance
				Vec3f pos;
				float yRad=DegToRad((int)(rand()%360)+1);
				pos.x=cos(yRad);
				pos.z=sin(yRad);
				pos*=spawnDistance_;
				pos+=parent_->GetTransform()->pos;

				// and then move us to that position
				MoveActorEventPtr move= new MoveActorEvent();
				move->pos_=pos;
				move->SetTargetID(parent_->GetID());
				EventPtr eve= move.DynamicCast(EventPtr());
				TheEventStore::Instance()->AddEvent(eve);
			}
			PlayerSpawnEventPtr spawn= new PlayerSpawnEvent();
			spawn->spawnID_=(parent_->GetID());
			spawn->livesLeft_=lives_;
			EventPtr eve= spawn.DynamicCast(EventPtr());
			TheEventStore::Instance()->AnnounceEvent(eve);
			hit_=false;
		}
	}
}

void TankComponent::Destroy()
{

}

bool TankComponent::Load(GOComponentLO* loadComp)
{
return false;
}
bool TankComponent::Load(File& file)
{
	std::string read;
	bool lives=false, hitTimer=false, 
		spawnTime=false, spawnPlace=false,
		deathSound=false;
	
	while(file.GetString(&read))
	{
		if(read=="Lives")
		{
			file.GetInteger(&lives_);
			lives=true;
		}
		if(read=="HitTimer")
		{
			file.GetFloat(&hitTimer_);
			hitTimer=true;
		}
		if(read=="RespawnDelay")
		{
			file.GetFloat(&spawnTime_);
			spawnTime=true;
		}
		if(read=="SpawnDistance")
		{
			file.GetFloat(&spawnDistance_);
			spawnPosition_=Vec3f();
			spawnPlace=true;
		}
		if(read=="SpawnPosition")
		{
			file.GetCSVec3f(&spawnPosition_);
			spawnDistance_=0;
			spawnPlace=true;
		}
		if(read=="/TankComponent")
		{
			break;
		}
		if(read=="DeathSound")
		{
			deathSound=file.GetString(&deathSound_);
		}
		if(read=="SpawningSound")
		{
			file.GetString(&spawningSound_);
		}
	}
	if(!spawnPlace&&lives_==0)
	{
		spawnPlace=true;
	}
	hit_=false;
	timer_=0;
	spawnTimer_=0;
	return lives&&hitTimer&&spawnTime&&spawnPlace&&deathSound;
}

const char* TankComponent::GetTypeName()const
{
	return TYPENAME;
}

void TankComponent::PassEvent(EventPtrList* eve)
{
	for(EventPtrList::iterator it=eve->begin();
		it!=eve->end();
		++it)
	{
		if((*it)->GetEventType()==CollisionEvent::TYPENAME)
		{
			CollisionEventPtr col=it->DynamicCast(CollisionEventPtr());
			if(col)
			{
				HandleCollision(*col);
			}
		}
	}
}

void TankComponent::HandleCollision(CollisionEvent& col)
{
	int colID=col.collider->GetParentID();
	GameObject* g = TheGame::Instance()->GetGameObject(colID);
	Actor* a=dynamic_cast<Actor*>(g);
	assert(a);
	if(a->HasTag(std::string("Bullet")))
	{
		Actor* parent=dynamic_cast<Actor*>(parent_);
		if(parent->HasTag(std::string("Player"))&&a->HasTag(std::string("EnemyBullet"))||
			parent->HasTag(std::string("Enemy"))&&a->HasTag(std::string("PlayerBullet")))
		{
			if(!hit_)
			{
				--lives_;
				hit_=true;
				TheAudioManager::Instance()->PlaySoundFromTag(deathSound_);
				if(lives_<0)
				{
					int parentID=parent_->GetID();
					DestroyActorEventPtr destro = new DestroyActorEvent;
					destro->SetTargetID(parentID);
					destro->destroyActorID_=parentID;
					EventPtr eve(destro);
					TheEventStore::Instance()->AddEvent(eve);
					if(parent->HasTag(std::string("Player")))
					{
						lives_=0;
						ThePlayState::Instance()->GameOver();
					}
				}
				else
				{
					if(spawningSound_.size())
					{
						TheAudioManager::Instance()->PlaySoundFromTag(spawningSound_,3);
					}
					spawnTimer_=spawnTime_;
					PlayerDeathEventPtr death= new PlayerDeathEvent();
					death->deathID_=parent_->GetID();
					EventPtr eve=death.DynamicCast(EventPtr());
					TheEventStore::Instance()->AnnounceEvent(eve);
				}
			}
		}
	}
}