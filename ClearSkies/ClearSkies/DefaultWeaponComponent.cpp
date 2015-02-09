#include "DefaultWeaponComponent.h"
#include "PlayerControllerEvent.h"
#include <assert.h>
#include "ActorFactory.h"
#include "DefaultBullet.h"
#include "GOComponentFactory.h"
#include "DestroyActorEvent.h"
#include "PlayerDeathEvent.h"
#include "PlayerSpawnEvent.h"
#include <AudioManager.h>
#include <Game.h>
const char* DefaultWeaponComponent::TYPENAME="DefaultWeaponComponent";

GOComponent* Create()
{
	return new DefaultWeaponComponent();
}

static const bool b=TheGOComponentFactory::Instance()->AddComponentFunc(DefaultWeaponComponent::TYPENAME,
	Create);

void DefaultWeaponComponent::Update()
{

}

void DefaultWeaponComponent::Draw()const
{
	//could have a mesh to draw..
}

void DefaultWeaponComponent::Destroy()
{

}
bool DefaultWeaponComponent::Load(GOComponentLO* loadComp)
{
	return false;
}
bool DefaultWeaponComponent::Load(File& file)
{
	std::string read;
	bool max=false,sound=false;
	while(file.GetString(&read))
	{
		if(read=="MaxBulletsOut")
		{
			// the maximum possible bullets out at once
			file.GetInteger(&maxBulletsOut_);
			max=true;
		}
		if(read=="FireSound")
		{
			sound=file.GetString(&fireSound_);
		}
		if(read=="/DefaultWeaponComponent")
		{
			break;
		}
	}
	return max&&sound;
}

void DefaultWeaponComponent::PassEvent(EventPtrList* eve)
{
	for(EventPtrList::iterator it=eve->begin();
		it!=eve->end();
		++it)
	{
		if((*it)->GetEventType()==PlayerControllerEvent::TYPENAME)
		{
			PlayerControllerEventPtr ctrl=it->DynamicCast(PlayerControllerEventPtr());
			assert(ctrl);
			//recives a fire event
			if(ctrl->fire_==1)
			{
				Fire();
			}
		}
		if((*it)->GetEventType()==PlayerDeathEvent::TYPENAME)
		{
			PlayerDeathEventPtr death= (*it).DynamicCast(PlayerDeathEventPtr());
			//if the player is dead then he cant fire
			if (death->deathID_==parent_->GetID())
			{
				isActive_=false;
			}
		}
		if((*it)->GetEventType()==PlayerSpawnEvent::TYPENAME)
		{
			PlayerSpawnEventPtr death= (*it).DynamicCast(PlayerSpawnEventPtr());
			//and when he comes back, re inable
			if (death->spawnID_==parent_->GetID())
			{
				isActive_=true;
			}
		}
		if((*it)->GetEventType()==DestroyActorEvent::TYPENAME)
		{
			DestroyActorEventPtr destro=it->DynamicCast(DestroyActorEventPtr());
			assert(destro);
			if(bulletIDs.size()>0)
			{
				//if we have some bullets out, check for its ID
				for(BulletIDs::iterator it=bulletIDs.begin();
					it!=bulletIDs.end();
					++it)
				{
					if(destro->destroyActorID_==(*it))
					{
						bulletIDs.erase(it);
						break;
					}
				}
			}
		}
	}
}

void DefaultWeaponComponent::Fire()
{
	if(isActive_)
	{
		if(bulletIDs.size()<(unsigned int)maxBulletsOut_)
		{
			Actor* bullet= TheActorFactory::Instance()->Create(std::string(DefaultBullet::TYPENAME));
			Actor* a=dynamic_cast<Actor*>(parent_);
			if(a->HasTag(std::string("Player")))
			{
				//if its a player then its a player bullet, thats all fine
				bullet->AddTag(std::string("PlayerBullet"));
			}
			else
			{
				bullet->AddTag(std::string("EnemyBullet"));
			}
			bulletIDs.push_back(bullet->GetID());
			//give the bullet our current transform, which it will use as its direction
			Transform* t=bullet->GetTransform();
			(*t)=(*parentTransform_);
			GOComponent* g =bullet->GetGOComponent(std::string(DefaultBullet::TYPENAME));
			DefaultBullet* deb=dynamic_cast<DefaultBullet*>(g);
			deb->SetOwner(parent_->GetID());
			TheGame::Instance()->AddGameObject(bullet->GetID(),bullet);
			TheAudioManager::Instance()->PlaySoundFromTag(fireSound_);
		}
	}
}

const char* DefaultWeaponComponent::GetTypeName()const
{
	return TYPENAME;
}

void DefaultWeaponComponent::PostInit()
{
	parentTransform_=parent_->GetTransform();
}