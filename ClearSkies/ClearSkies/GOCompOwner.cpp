#include "GOCompOwner.h"

GOCompOwner::GOCompOwner(GameObject* g)
{
	parent_=g;
}

GOCompOwner::~GOCompOwner()
{
	for(CompMap::iterator it=compMap_.begin();
		it!=compMap_.end();
		++it)
	{
		delete it->second;

	}
}

void GOCompOwner::AddGOComponent(GOComponent& go)
{
	int id=go.GetID();
	compMap_[id]=&go;
	compMap_[id]->SetParentID(parent_);
}

void GOCompOwner::DeleteGOComponent(int ID)
{
	compMap_[ID]->Destroy();
	delete compMap_[ID];
	compMap_.erase(compMap_.find(ID));
}

GOComponent* GOCompOwner::GetGOComponent(const std::string& type)
{
	for(CompMap::iterator it=compMap_.begin();
		it!=compMap_.end();
		++it)
	{
		if(it->second->GetTypeName()==type)
		{
			return it->second;
		}
	}
	return NULL;
}

GOComponent* GOCompOwner::GetColliderComponent()
{
	std::string name;
	for(CompMap::iterator it=compMap_.begin();
		it!=compMap_.end();
		++it)
	{
		name=it->second->GetTypeName();
		if(name.find("Collider")!=std::string::npos)
		{
		return it->second;
		}
	}
	return 0;
}

void GOCompOwner::UpdateComps()
{
	for(CompMap::iterator it=compMap_.begin();
		it!=compMap_.end();
		++it)
	{
		if(it->second->ShouldUpdate())
		{
			it->second->Update();
		}
	}
}

void GOCompOwner::DrawComps()const
{
	for(CompMap::const_iterator it=compMap_.begin();
		it!=compMap_.end();
		++it)
	{
		if(it->second->ShouldDraw())
		{
			it->second->Draw();
		}
	}
}