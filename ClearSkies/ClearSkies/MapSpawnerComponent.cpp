#include "MapSpawnerComponent.h"
#include "GOComponentFactory.h"
#include "DestroyActorEvent.h"
#include "GetActorEvent.h"
#include "ActorFactory.h"
#include "CollisionController.h"
#include "SphereCollider.h"
#include <AngleConvert.h>
#include <Game.h>
#include <Timer.h>
#include <assert.h>

const char* MapSpawnerComponent::TYPENAME="MapSpawnerComponent";

static GOComponent* Create()
{
	return new MapSpawnerComponent();
}

static const bool b=TheGOComponentFactory::Instance()->AddComponentFunc(MapSpawnerComponent::TYPENAME,
	Create);


void MapSpawnerComponent::Update()
{
	CheckDespawn();
	while(walls_.size()<minWallsAtOnce_)
	{
		SpawnHorizonWall();
	}
	float dt=TheTimer::Instance()->GetDt();
	for(std::list<float>::iterator it=spawnTimes_.begin();
		it!=spawnTimes_.end();
		)
	{
		(*it)-=dt;
		if((*it)<=0)
		{
			it=spawnTimes_.erase(it);
			SpawnEnemy();
			continue;
		}
		++it;
	}
}

void MapSpawnerComponent::CheckDespawn()
{
	float sqrdDespawn = horizonDespawnRange_*horizonDespawnRange_;
	for(ObjectMap::iterator it=walls_.begin();
		it!=walls_.end();
		)
	{
		Vec3f pTow =(it->second->GetCTransform()->pos-playerTransform_->pos);
		float sqrdDist =pTow.SqrLength();
		if(sqrdDist>sqrdDespawn)
		{
			DestroyActorEventPtr destro=new DestroyActorEvent();
			destro->destroyActorID_=it->second->GetID();
			destro->SetTargetID(it->second->GetID());
			EventPtr eve=destro.DynamicCast(EventPtr());
			TheEventStore::Instance()->AddEvent(eve);
			it=walls_.erase(it);
			continue;
		}
		++it;
	}
}

void MapSpawnerComponent::SpawnHorizonWall()
{
	std::string wallName;
	wallName=wallNames_[rand()%wallNames_.size()];
	Actor* wall=TheActorFactory::Instance()->Create(wallName);
	Collider* collider = dynamic_cast<Collider*>(wall->GetColliderComponent());
	assert(collider);
	do
	{
		float radY= DegToRad((rand()%359)+1);
		Vec3f dir;
		dir.x=cos(radY);
		dir.z=sin(radY);
		dir*=horizonSpawnRange_;
		dir+=playerTransform_->pos;
		wall->GetTransform()->pos=dir;
	}
	while(TheCollisionController::Instance()->TestCollision(collider));
	walls_[wall->GetID()]=wall;
	TheGame::Instance()->AddGameObject(wall->GetID(),wall);

}

void MapSpawnerComponent::SpawnWall()
{
	std::string wallName;
	wallName=wallNames_[rand()%wallNames_.size()];
	Actor* wall=TheActorFactory::Instance()->Create(wallName);
	Collider* collider = dynamic_cast<Collider*>(wall->GetColliderComponent());
	assert(collider);
	float range=horizonSpawnRange_*2;
	do
	{
		Vec3f pos;
		pos.x=(((float)rand()/(float)RAND_MAX)*range)-horizonSpawnRange_;
		pos.z=(((float)rand()/(float)RAND_MAX)*range)-horizonSpawnRange_;
		wall->GetTransform()->pos=pos;
	}
	while(TheCollisionController::Instance()->TestCollision(collider));
	walls_[wall->GetID()]=wall;
	TheGame::Instance()->AddGameObject(wall->GetID(),wall);

}
void MapSpawnerComponent::SpawnEnemy()
{
	std::string enemyName;
	enemyName=enemyNames_[rand()%enemyNames_.size()];
	Actor* enemy= TheActorFactory::Instance()->Create(enemyName);
	Collider* collider = dynamic_cast<Collider*>(enemy->GetColliderComponent());
	assert(collider);	
	do
	{
		float dist = ((float)rand()/(float)RAND_MAX)*(maxEnemySpawnRange_-minEnemySpawnRange_)+minEnemySpawnRange_;
		float radY = DegToRad((rand()%359)+1);
		Vec3f dir;
		dir.x=cos(radY);
		dir.z=sin(radY);
		dir*=dist;
		dir+=playerTransform_->pos;
		enemy->GetTransform()->pos=dir;
	}
	while(TheCollisionController::Instance()->TestCollision(collider));
	enemies_[enemy->GetID()]=enemy;
	TheGame::Instance()->AddGameObject(enemy->GetID(),enemy);
}

void MapSpawnerComponent::Draw()const
{

}

void MapSpawnerComponent::Destroy()
{

}
void MapSpawnerComponent::PostInit()
{
	for(int i=0;i<maxEnemiesAtOnce_;++i)
	{
		spawnTimes_.push_back(((rand()/RAND_MAX)*(maxEnemyRespawnTime_-minEnemyRespawnTime_))+minEnemyRespawnTime_);
	}
	shouldDraw_=false;

	for(int i=0;i<minWallsAtOnce_;++i)
	{
		SpawnWall();
	}
	if(parent_->HasTag(std::string("Player")))
	{
		playerTransform_=parent_->GetCTransform();
	}
	else
	{
		GetActorEventPtr get = new GetActorEvent();
		get->ownerID=parent_->GetID();
		get->tags.push_back("Player");
		get->collectedActor=0;
		EventPtr eve=get.DynamicCast(EventPtr());
		TheEventStore::Instance()->AnnounceEvent(eve);
	}

	return;
}

void MapSpawnerComponent::PassEvent(EventPtrList* eve)
{
	for (EventPtrList::iterator it=eve->begin();
		it!=eve->end();
		++it)
	{
		if((*it)->GetEventType()==DestroyActorEvent::TYPENAME)
		{
			DestroyActorEventPtr destro = it->DynamicCast(DestroyActorEventPtr());
			ObjectMap::iterator find=enemies_.find(destro->destroyActorID_);
			if(find!=enemies_.end())
			{
				enemies_.erase(find);
				spawnTimes_.push_back(((rand()/RAND_MAX)*(maxEnemyRespawnTime_-minEnemyRespawnTime_))+minEnemyRespawnTime_);
			}
		}
		if((*it)->GetEventType()==GetActorEvent::TYPENAME)
		{
			GetActorEventPtr getty= it->DynamicCast(GetActorEventPtr());
			if(getty->GetTargetID()==parent_->GetID())
			{
				playerTransform_=getty->collectedActor->GetCTransform();
			}
		}
	}
}
bool MapSpawnerComponent::Load(GOComponentLO* loadComp)
{
return false;
}
bool MapSpawnerComponent::Load(File& file)
{
	std::string read;
	bool minESpawn=false,maxESpawn=false;
	bool maxE=false, minW=false;
	bool spawnRange=false, despawnRange=false;
	bool minESpawnRange=false, maxESpawnRange=false;
	while(file.GetString(&read))
	{
		if(read=="/MapSpawnerComponent")
		{
			break;
		}
		if(read=="EnemyName")
		{
			std::string name;
			file.GetString(&name);
			enemyNames_.push_back(name);
		}
		if(read=="WallName")
		{
			std::string name;
			file.GetString(&name);
			wallNames_.push_back(name);
		}
		if(read=="MinEnemySpawnRange")
		{
			minESpawnRange=file.GetFloat(&minEnemySpawnRange_);
		}
		if(read=="MaxEnemySpawnRange")
		{
			maxESpawnRange=file.GetFloat(&maxEnemySpawnRange_);
		}
		if(read=="MinEnemyRespawnTime")
		{
			minESpawn=file.GetFloat(&minEnemyRespawnTime_);
		}
		if(read=="MaxEnemyRespawnTime")
		{
			maxESpawn=file.GetFloat(&maxEnemyRespawnTime_);
		}
		if(read=="MaxEnemies")
		{
			maxE=file.GetInteger(&maxEnemiesAtOnce_);
		}
		if(read=="MinWalls")
		{
			minW=file.GetInteger(&minWallsAtOnce_);
		}
		if(read=="WallSpawnRange")
		{
			spawnRange=file.GetFloat(&horizonSpawnRange_);
		}
		if(read=="WallDespawnRange")
		{
			despawnRange=file.GetFloat(&horizonDespawnRange_);
		}
	}
	if(maxEnemyRespawnTime_<minEnemyRespawnTime_)
	{
		maxEnemyRespawnTime_=minEnemyRespawnTime_;
	}
	if(maxEnemySpawnRange_<minEnemySpawnRange_)
	{
		maxEnemySpawnRange_=minEnemySpawnRange_;
	}
	return (minESpawn&&maxESpawn&&maxE&&minW&&spawnRange&&despawnRange);
}

const char* MapSpawnerComponent::GetTypeName()const
{
	return TYPENAME;
}