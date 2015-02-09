#include "DefaultBullet.h"
#include <Game.h>
#include <Timer.h>
#include <assert.h>
#include "DestroyActorEvent.h"
#include "EventStore.h"
#include "GOComponentFactory.h"
#include <AngleConvert.h>
#include "CollisionEvent.h"

#include <gl/glut.h>
const char* DefaultBullet::TYPENAME="DefaultBullet";
static GOComponent* Create()
{
	return new DefaultBullet();
}

static const bool b= TheGOComponentFactory::Instance()->AddComponentFunc(DefaultBullet::TYPENAME,
	Create);

DefaultBullet::DefaultBullet()
{
	timer_=0;
}

void DefaultBullet::SetOwner(int id)
{
	ownerID_=id;
}

const char* DefaultBullet::GetTypeName()const
{
	return TYPENAME;
}

void DefaultBullet::Update()
{
	float dt=TheTimer::Instance()->GetDt();
	float yRad=DegToRad(parentTransform_->rot.y);
	Vec3f move=parentTransform_->pos;
	move.x+=cos(yRad)*(speed_*dt);
	move.z+=sin(yRad)*(speed_*dt);
	parentTransform_->pos=move;

	timer_+=TheTimer::Instance()->GetDt();
	if(timer_>lifetime_)
	{
		//runs until its lifetime is up, or until it hits something
		DestroyActorEventPtr destro=new DestroyActorEvent();
		destro->SetTargetID(parent_->GetID());
		destro->destroyActorID_=parent_->GetID();
		EventPtr eve=destro.DynamicCast(EventPtr());
		TheEventStore::Instance()->AddEvent(eve);
	}

}

void DefaultBullet::Draw()const
{
	

}

void DefaultBullet::Destroy()
{

}
bool DefaultBullet::Load(GOComponentLO* loadComp)
{
return false;
}
bool DefaultBullet::Load(File& file)
{
	std::string read;
	bool speed=false, lifetime=false;
	while(file.GetString(&read))
	{
		if(read=="Speed")
		{
			file.GetFloat(&speed_);
			speed=true;
		}
		if(read=="Lifetime")
		{
			file.GetFloat(&lifetime_);
			lifetime=true;
		}
		if(read=="/DefaultBullet")
		{
			break;
		}
	}
	return speed&&lifetime;
}

void DefaultBullet::PassEvent(EventPtrList* eve)
{
	for(EventPtrList::iterator it=eve->begin();
		it!=eve->end();
		++it)
	{
		if((*it)->GetEventType()==CollisionEvent::TYPENAME)
		{
			CollisionEventPtr bumpy = (*it).DynamicCast(CollisionEventPtr());
			GameObject* g=TheGame::Instance()->GetGameObject(bumpy->collider->GetParentID());
			if(g->HasTag(std::string("Wall")) || (g->HasTag(std::string("Enemy"))&& g->GetID()!=ownerID_))
			{
				//its lifetime is over, its hit an object that it should collide with
				timer_=lifetime_+1;
			}
		}
	}
}

void DefaultBullet::PostInit()
{
	parentTransform_=parent_->GetTransform();
}