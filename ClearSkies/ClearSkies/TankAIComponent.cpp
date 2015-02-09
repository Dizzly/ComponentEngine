#include "TankAIComponent.h"
#include "GetActorEvent.h"
#include "EventStore.h"
#include <assert.h>
#include <AngleConvert.h>
#include <Plane.h>
#include "GOComponentFactory.h"
#include "CollisionController.h"
#include "PlayerControllerEvent.h"
#include "PlayerDeathEvent.h"
#include "PlayerSpawnEvent.h"
#include <Timer.h>
#include <gl/glut.h>

const char* TankAIComponent::TYPENAME="TankAIComponent";

static GOComponent* Create()
{
	return new TankAIComponent;
}

static const bool b=TheGOComponentFactory::Instance()->AddComponentFunc(TankAIComponent::TYPENAME,
	Create);

TankAIComponent::TankAIComponent()
{
	aggro_=false;
	lockOn_=false;
	sleep_=false;
}

void TankAIComponent::Draw()const
{

}

void TankAIComponent::Update()
{
	float test=(playerTransform_->pos-parentTransform_->pos).Length();
	if(sleepTimer_>0&&sleep_)
	{
		// if asleep then lets couunt down till we can wake up
		sleepTimer_-=TheTimer::Instance()->GetDt();
	}
	else
	{
		sleep_=false;
	}
	if(lockOnTimer_>=0&&!lockOn_)
	{	
		//if were not locked on, and the timer started
		lockOnTimer_-=TheTimer::Instance()->GetDt();
		if(lockOnTimer_<0)
		{
			//try to lock on
			lockOn_=true;
		}
	}
	if(aggro_==false&&test<agroRange_)
	{
		//a one time agro test
		aggro_=true;
	}
	if(aggro_)
	{
		//when they are aware of the player
		float yRad=DegToRad(parentTransform_->rot.y);
		Vec3f forwards;
		forwards.x=cos(yRad);
		forwards.z=sin(yRad);
		if(!sleep_)
		{
			//and not sleeping
			Vec3f pos=parentTransform_->pos;
			target_=pos+forwards*10;
			Vec3f up=parentTransform_->pos;
			up.y+=1;
			//define a plane for use on player position clasification
			Plane p(parentTransform_->pos,pos+forwards,up);
			int i=p.ClassifyPoint(playerTransform_->pos);
			//here were getting infront or behind the plane, which faces down the middle
			PlayerControllerEventPtr ctrl=new PlayerControllerEvent;
			ctrl->SetTargetID(parent_->GetID());
			Vec3f toPlayer = playerTransform_->pos-parentTransform_->pos;
			float angle=RadToDeg(acos((forwards.Dot(toPlayer))/(forwards.Length()*toPlayer.Length())));
			//and if the angle is within the lock on range. 
			//I cant compare floats, so this will never be an exact lock in on the player
			bool stop=false;
			if(angle<1)
			{
				if(lockOnTimer_<=0)
				{
					lockOnTimer_=lockTime_;
				}
				stop=true;
			}
			else
			{

			}
			if(!lockOn_)
			{
				if(i!=2)
				{
					if(i==INFRONT_PLANE)
					{
						ctrl->right_=2;
						ctrl->left_=0;
					}
					else if(i==BEHIND_PLANE)
					{
						ctrl->left_=2;
						ctrl->right_=0;
					}
				}
			}
			if(stop)
			{
				ctrl->right_=0;
				ctrl->left_=0;
			}
			if(lockOn_)
			{
				ctrl->fire_=true;
				sleep_=true;
				sleepTimer_=sleepTime_;
				lockOn_=false;
			}
			EventPtr eve=ctrl.DynamicCast(EventPtr());
			TheEventStore::Instance()->AddEvent(eve);
		}

	}
}

void TankAIComponent::Destroy()
{

}

void TankAIComponent::PostInit()
{
	parentTransform_=parent_->GetTransform();
	GetActorEventPtr get=new GetActorEvent;
	get->ownerID=parent_->GetID();
	get->tags.push_back("Player");
	get->collectedActor=0;
	EventPtr eve=get.DynamicCast(EventPtr());
	TheEventStore::Instance()->AnnounceEvent(eve);
	aggro_=false;
}
bool TankAIComponent::Load(GOComponentLO* loadComp)
{
return false;
}
bool TankAIComponent::Load(File& file)
{
	std::string read;
	bool ar=false,sleep=false,lock=false;
	// loop until the end of class is reached
	while(file.GetString(&read))
	{
		if(read=="AggroRange")
		{
			file.GetFloat(&agroRange_);
			ar=true;
		}
		if(read=="SleepTime")
		{
			file.GetFloat(&sleepTime_);
			sleep=true;
		}
		if(read=="LockTime")
		{
			file.GetFloat(&lockTime_);
			lock=true;
		}
		if(read=="/TankAIComponent")
		{
			break;
		}
	}
	aggro_=false;
	lockOn_=false;
	sleep_=false;
	return ar&&sleep&&lock;
}

void TankAIComponent::PassEvent(EventPtrList* eve)
{
	for(EventPtrList::iterator it=eve->begin();
		it!=eve->end();
		++it)
	{
		if((*it)->GetEventType()==GetActorEvent::TYPENAME)
		{
			GetActorEventPtr get=it->DynamicCast(GetActorEventPtr());
			assert(get);
			if(get->GetTargetID()==parent_->GetID())
			{
				// after aquiring the player, get their transform for our checks
				playerTransform_=get->collectedActor->GetTransform();
			}
		}
		if((*it)->GetEventType()==PlayerDeathEvent::TYPENAME)
		{
			//when the player dies, loose agro and lock, give them a chance
			PlayerDeathEventPtr death=it->DynamicCast(PlayerDeathEventPtr());
			aggro_=false;
			sleep_=false;
			lockOn_=false;
		}
	}
}

const char* TankAIComponent::GetTypeName()const
{
	return TYPENAME;
}