#include "Actor.h"
#include "EventStore.h"
#include "GOComponentFactory.h"
#include <GameObjectFactory.h>
#include <Game.h>
#include "DestroyActorEvent.h"
#include "GetActorEvent.h"
#include "CreateActorEvent.h"
#include "MoveActorEvent.h"
GameObject* CreateTank()
{
	return new Actor();
}

bool sneaky= TheGameObjectFactory::Instance()->AddType("Actor",CreateTank);

Actor::Actor():GOCompOwner(this)//weak pointer
{
	isActive_=true;
}

Actor::~Actor()
{
}

void Actor::Update()
{
	PollEvents();
	if(isActive_)
	{
		UpdateComps();
		PollEvents();
	}
}

void Actor::SetID(int ID)
{
	ID_=ID;
}

void Actor::Draw()const
{
	if(isActive_)
	{
		DrawComps();
	}
}

void Actor::SetName(std::string& name)
{
	name_=name;
}

bool Actor::Load(File* file)
{
	std::string read;
	while(file->GetString(&read))
	{
		if(read=="Name")
		{
			file->GetString(&name_);
		}
		if(read=="Position")
		{
			file->GetCSVec3f(&transform_.pos);
		}
		if(read=="<Tags>")
		{
			while(file->GetString(&read))
			{
				if(read=="</Tags>")
				{
					break;
				}
				else
				{
					tags_.insert(read);
				}
			}
			break;
		}
	}
	isDestro_=false;
	TheEventStore::Instance()->AddID(ID_);
	TheGOComponentFactory::Instance()->LoadComponents(*this,file);
	CreateActorEventPtr create= new CreateActorEvent();
	create->createdActor=this;
	create->targetId_=0;
	EventPtr eve=create.DynamicCast(EventPtr());
	TheEventStore::Instance()->AnnounceEvent(eve);
	isActive_=true;
	return true;
}

const char* Actor::GetTypeName()const 
{
	return name_.c_str();
}

bool Actor::HasTag(std::string &tag)
{
	TagSet::iterator it=tags_.find(tag);
	if(it!=tags_.end())
	{
		return true;
	}
	return false;
}

void Actor::AddTag(std::string &tag)
{
	tags_.insert(tag);
}

void Actor::PollEvents()
{
	EventPtrList* eve=TheEventStore::Instance()->GetEvents(ID_);
	if(eve&&eve->size()>0)
	{
		for(EventPtrList::iterator it=eve->begin();
			it!=eve->end();
			++it)
		{
			if((*it)->GetEventType()==DestroyActorEvent::TYPENAME)
			{
				DestroyActorEventPtr destro = it->DynamicCast(DestroyActorEventPtr());
				assert(destro);
				if (destro->destroyActorID_==ID_)
				{
					if(isDestro_==false)
					{
					TheGame::Instance()->SafeDelete(ID_);
					isDestro_=true;
					return;
					}
				}
			}
			if((*it)->GetEventType()==MoveActorEvent::TYPENAME)
			{
				MoveActorEventPtr move=(*it).DynamicCast(MoveActorEventPtr());
				assert(move);
				if(move->GetTargetID()==ID_)
				{
				transform_.pos=move->pos_;
				}
			}
			if((*it)->GetEventType()==GetActorEvent::TYPENAME)
			{
				GetActorEventPtr get=it->DynamicCast(GetActorEventPtr());
				assert(get);
				int matches=0;
				if(get->GetTargetID()==0)
				{
					for(int i=0;i<get->tags.size();++i)
					{
						std::string reqTag=get->tags[i];
						TagSet::iterator it= tags_.find(reqTag);
						if(it!=tags_.end())
						{
							++matches;
						}
					}
					if(matches==get->tags.size())
					{
						get->SetTargetID(get->ownerID);
						get->collectedActor=this;
						EventPtr eve= get.DynamicCast(EventPtr());
						TheEventStore::Instance()->AddEvent(eve);
					}
				}
			}
		}
		for(CompMap::iterator comp=compMap_.begin();
			comp!=compMap_.end();
			++comp)
		{
			comp->second->PassEvent(eve);
		}
	}
	eve->clear();
}

void Actor::Destroy()
{
	DestroyActorEventPtr destro = new DestroyActorEvent;
	destro->destroyActorID_=ID_;
	EventPtr eve(destro);
	TheEventStore::Instance()->RemoveID(ID_);
	TheEventStore::Instance()->AnnounceEvent(eve);
	for(CompMap::iterator it=compMap_.begin();
		it!=compMap_.end();
		++it)
	{
		it->second->Destroy();
	}
	isActive_=false;
	isDestro_=true;
}

void Actor::SetParentID(int id)
{
	parentID_=id;
}

int Actor::GetParentID()
{
	return parentID_;
}