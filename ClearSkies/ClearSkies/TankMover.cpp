#include "TankMover.h"
#include <AngleConvert.h>
#include "PlayerControllerEvent.h"
#include "PlayerDeathEvent.h"
#include "PlayerSpawnEvent.h"
#include "CollisionEvent.h"
#include "GOComponentFactory.h"
#include <Game.h>
#include <Timer.h>
const char* TankMover::TYPENAME="TankMover";

static GOComponent* Create()
{
	return new TankMover();
}

static bool cheater = TheGOComponentFactory::Instance()->AddComponentFunc(TankMover::TYPENAME,
	Create);


void TankMover::Draw()const 
{}

void TankMover::Destroy()
{}

void TankMover::Update()
{
	if(isActive_)
	{
		//typical move conditions
		float yRad=DegToRad(parentTransform_->rot.y);
		oldPos_=parentTransform_->pos;
		if(fKey_)
		{
			//forwards
			Vec3f move=parentTransform_->pos;
			move.x+=cos(yRad)*fSpeed_*TheTimer::Instance()->GetDt();
			move.z+=sin(yRad)*fSpeed_*TheTimer::Instance()->GetDt();
			parentTransform_->pos=move;
		}
		if(bKey_)
		{
			//backwards
			Vec3f move=parentTransform_->pos;
			move.x-=cos(yRad)*bSpeed_*TheTimer::Instance()->GetDt();
			move.z-=sin(yRad)*bSpeed_*TheTimer::Instance()->GetDt();
			parentTransform_->pos=move;
		}
		if(lKey_)
		{
			//left turn, but slow if the player is moving forwards, backwards
			if(fKey_||bKey_)
			{
				parentTransform_->rot.y-=(turnSpeed_/2)*TheTimer::Instance()->GetDt();
			}
			else
			{
				parentTransform_->rot.y-=turnSpeed_*TheTimer::Instance()->GetDt();
			}
		}
		if(rKey_)
		{
			if(fKey_||bKey_)
			{
				parentTransform_->rot.y+=(turnSpeed_/2)*TheTimer::Instance()->GetDt();;
			}
			else
			{
				parentTransform_->rot.y+=turnSpeed_*TheTimer::Instance()->GetDt();
			}
		}
	}
}

bool TankMover::Load(GOComponentLO* loadComp)
{
return false;
}

bool TankMover::Load(File& file)
{
	fKey_=false;
	rKey_=false;
	bKey_=false;
	lKey_=false;
	std::string read; 
	bool fSpeed=false,bSpeed=false,turnSpeed=false;
	while(file.GetString(&read))
	{
		if(read=="ForwardsSpeed")
		{
			file.GetFloat(&fSpeed_);
			fSpeed=true;
		}
		if(read=="BackwardsSpeed")
		{
			file.GetFloat(&bSpeed_);
			bSpeed=true;
		}
		if(read=="TurnSpeed")
		{
			file.GetFloat(&turnSpeed_);
			turnSpeed=true;
		}
		if(read=="/TankMover")
		{
			break;
		}
	}
	return fSpeed&&bSpeed&&turnSpeed;
}

const char* TankMover::GetTypeName()const
{
	return TYPENAME;
}

void TankMover::PassEvent(EventPtrList* eve)
{
	for(EventPtrList::iterator it=eve->begin(); it!=eve->end();
		++it)
	{
		if((*it)->GetEventType()==PlayerControllerEvent::TYPENAME)
		{
			PlayerControllerEventPtr event= it->DynamicCast(PlayerControllerEventPtr());
			if(event)
			{
				if(event->forwards_!=1)
				{
					fKey_=(event->forwards_);
				}
				if(event->left_!=1)
				{
					lKey_=(event->left_);
				}
				if(event->right_!=1)
				{
					rKey_=(event->right_);
				}
				if(event->backwards_!=1)
				{
					bKey_=(event->backwards_);
				}

			}
		}
		if((*it)->GetEventType()==PlayerDeathEvent::TYPENAME)
		{
			PlayerDeathEventPtr death= (*it).DynamicCast(PlayerDeathEventPtr());
			if (death->deathID_==parent_->GetID())
			{
				isActive_=false;
			}
		}
		if((*it)->GetEventType()==PlayerSpawnEvent::TYPENAME)
		{
			PlayerSpawnEventPtr death= (*it).DynamicCast(PlayerSpawnEventPtr());
			if (death->spawnID_==parent_->GetID())
			{
				isActive_=true;
			}
		}
		if((*it)->GetEventType()==CollisionEvent::TYPENAME)
		{
			CollisionEventPtr bumpy=(*it).DynamicCast(CollisionEventPtr());
			GameObject* go=TheGame::Instance()->GetGameObject(bumpy->collider->GetParentID());
			if(go->HasTag(std::string("Wall")))
			{
				Bump();
			}
		}
	}
}

void TankMover::PostInit()
{
	parentTransform_ = parent_->GetTransform();
}

void TankMover::Bump()
{
	parentTransform_->pos=oldPos_;
}