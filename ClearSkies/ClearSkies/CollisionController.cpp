#include "CollisionController.h"
#include <ReportError.h>
#include <algorithm>
#include "CollisionEvent.h"
#include <Game.h>
#include <LineSegment.h>
#include <list>

CollisionController::CollisionController()
{

}

void CollisionController::AddCollider(Collider* c)
{
	colliders_[c->GetCollisionGroup()].push_back(c);
}



bool CollisionController::RaycastTest(Vec3f& start, Vec3f& dir,int ID,std::string tag)
{
	//create a "fake" ray to start with
	LineSegment ray(start,start+(dir*1000));
	// for each collision group
	for(ColliderMap::iterator it=colliders_.begin();
		it!=colliders_.end();
		++it)
	{
		//and each collider in that group
		for(ColliderList::iterator cIt=it->second.begin();
			cIt!=it->second.end();
			++cIt)
		{
			//if its not the thing casting the ray
			if((*cIt)->GetParentID()!=ID)
			{
				//check for ray function 
				RayCastCheckFuncs::iterator check= rayFuncs_.find((*cIt)->GetTypeName());
				if(check!=rayFuncs_.end())
				{
					if(check->second((*cIt),&ray))
					{
						
						if(tag.size()>0)
						{
							GameObject* g=TheGame::Instance()->GetGameObject((*cIt)->GetParentID());
							if(g->HasTag(tag))
							{
								return true;
							}
						}
						else
						{
							return true;
						}

					}
				}
				else
				{
					ReportError("Collision Check function missing between"+
						std::string((*cIt)->GetTypeName())+" and rays");
					return false;
				}

			}
		}
	}
	return false;
}

bool CollisionController::TestCollision(const Collider* collider)
{
	// a one use function that returns if the collider currently collides with anything.
	// this does not produce a collision event, and so can be used for theory checking
	ColliderMap::iterator c = colliders_.find(collider->GetCollisionGroup());
	for(ColliderList::iterator it=c->second.begin();
		it!=c->second.end();
		++it)
	{
		TypePair pair((*it)->GetTypeName(),collider->GetTypeName());
		CheckFuncs::iterator checkIt=collisionFuncs_.find(pair);
		if(collider==(*it))
		{
			continue;
		}
		if(checkIt==collisionFuncs_.end())
		{
			ReportError("Collision Check function missing between"+
				std::string((*it)->GetTypeName())+" and "+std::string(collider->GetTypeName()));
		}
		if(checkIt->second((*it),collider))
		{
			return true;
		}
	}
	return false;
}

void CollisionController::CheckCollisions()
{
	// same layout as the raycast function
	// for each group
	for(ColliderMap::iterator it=colliders_.begin();
		it!=colliders_.end();
		++it)
	{
		//for each collider
		for(ColliderList::iterator cIt=it->second.begin();
			cIt!=it->second.end();
			++cIt)
		{
			//check the collision function both ways
			ColliderList::iterator cIty=cIt;
			++cIty;
			for(;
				cIty!=it->second.end();
				++cIty)
			{
				TypePair pair((*cIt)->GetTypeName(),(*cIty)->GetTypeName());
				CheckFuncs::iterator checkIt=collisionFuncs_.find(pair);
				if(checkIt==collisionFuncs_.end())
				{
					ReportError("Collision Check function missing between"+
						std::string((*cIt)->GetTypeName())+" and "+std::string((*cIty)->GetTypeName()));
				}
				if(checkIt->second((*cIt),(*cIty)))
				{
					//and if there is a collision send a collision event to both participentss
					int parent1=(*cIt)->GetParentID();
					int parent2=(*cIty)->GetParentID();

					CollisionEventPtr col1= new CollisionEvent();
					CollisionEventPtr col2= new CollisionEvent();
					col1->collider=*cIt;

					col1->SetTargetID(parent2);
					col1->coltype=TheGame::Instance()->GetGameObject(parent2)->GetTypeName();

					col2->collider=*cIty;
					col2->SetTargetID(parent1);
					col2->coltype=TheGame::Instance()->GetGameObject(parent1)->GetTypeName();

					EventPtr eve1(col1);
					EventPtr eve2(col2);
					TheEventStore::Instance()->AddEvent(eve1);
					TheEventStore::Instance()->AddEvent(eve2);
				}
			}
		}
	}
}

bool CollisionController::AddCollisionCheck(CollisionCheck c,TypePair& p)
{
	collisionFuncs_[p]=c;
	collisionFuncs_[TypePair(p.second,p.first)]=c;
	return true;
}
bool CollisionController::AddRayCastCheck(RayCastCheck r, std::string& type)
{
	rayFuncs_[type]=r;
	return true;
}

void CollisionController::RemoveCollider(Collider* c)
{
	ColliderList* coll=&colliders_[c->GetCollisionGroup()];
	ColliderList::iterator it=std::find(coll->begin(),
		coll->end(),c);

	if(it!=coll->end())
	{
		coll->erase(it);
	}
	else
	{
		ReportError("Removal of unknown collider ID: "+ c->GetID()); 
	}
}