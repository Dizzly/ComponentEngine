#include "LifetimeComponent.h"
#include "GOComponentFactory.h"
#include "DestroyActorEvent.h"
#include <Timer.h>
#include <assert.h>
#include "GOComponentFactory.h"
const char* LifetimeComponent::TYPENAME="LifetimeComponent";
const char* LifetimeComponentLO::TYPENAME="LifetimeComponentLO";

LifetimeComponentLO::~LifetimeComponentLO()
{}
LifetimeComponentLO::LifetimeComponentLO()
{
engageTimer=false;
loadMaxTime=false;
maxTime=0;
}
const char* LifetimeComponentLO::GetTypeName()const
{
return TYPENAME;
}

static GOComponent* Create()
{
	return new LifetimeComponent();
}
static const bool hidden = TheGOComponentFactory::Instance()->AddComponentFunc(LifetimeComponent::TYPENAME,
	Create);

LifetimeComponent::LifetimeComponent()
{
	parentID_=0;
	timer_=0;
	maxTime_=0;
}

void LifetimeComponent::Draw()const
{

}

void LifetimeComponent::Update()
{
	if(isTimeing_)
	{
	timer_-=TheTimer::Instance()->GetDt();
	}
	if(timer_<=0)
	{
		DestroyActorEventPtr destro= new DestroyActorEvent();
		destro->destroyActorID_=parentID_;
		destro->SetTargetID(parentID_);
		EventPtr eve=destro.DynamicCast(EventPtr());
		TheEventStore::Instance()->AddEvent(eve);
		isActive_=false;
	}
}

void LifetimeComponent::Destroy()
{}

void LifetimeComponent::PostInit()
{
	parentID_=parent_->GetID();
}

bool LifetimeComponent::Load(GOComponentLO* compLoad)
{
	LifetimeComponentLO* life=NULL;
	if(compLoad->GetTypeName()==LifetimeComponentLO::TYPENAME)
	{
	life=dynamic_cast<LifetimeComponentLO*>(compLoad);
	}
	assert(life);
	if(life)
	{
		isTimeing_=life->engageTimer;
		if(life->loadMaxTime)maxTime_=life->maxTime;
		return true;
	}
	return false;
}

bool LifetimeComponent::Load(File& file)
{
	std::string read;
	isTimeing_=false;
	while(file.GetString(&read))
	{
		if(read=="Lifetime")
		{
			float f;
			file.GetFloat(&f);
			if(f==0)
			{
			isTimeing_=false;
			}
			maxTime_=f;
			isTimeing_=true;
		}
		if(read=="/LifetimeComponent")
		{
		break;
		}
	}
	timer_=maxTime_;
	shouldDraw_=false;
	return true;
}

const char* LifetimeComponent::GetTypeName()const
{
	return TYPENAME;
}

void LifetimeComponent::PassEvent(EventPtrList* eve)
{
	
}