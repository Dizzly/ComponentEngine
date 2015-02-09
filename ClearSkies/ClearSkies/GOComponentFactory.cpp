#include "GOComponentFactory.h"
#include <assert.h>
#include <Game.h>
#include <ReportError.h>
#include <sstream>
bool GOComponentFactory::AddComponentFunc(const std::string& key, CreateFun create)
{
	if(factoryMap_.find(key)==factoryMap_.end())
	{
		factoryMap_[key]=create;
		return true;
	}
	return false;
}

GOComponent* GOComponentFactory::CreateComponent(const std::string& key)
{
	CreateFun create = factoryMap_[key];
	assert(create);
	if(!create)
	{
	ReportError(std::string("There is no component type "+key));
	return NULL;
	}
	GOComponent* go=create();
	go->SetID(TheGame::Instance()->GetID());
	return go;
}

void GOComponentFactory::LoadComponents(GOCompOwner& compMap,File* file)
{
	std::string read;
	while(file->GetString(&read))
	{
		std::string type=read;
		if(type=="<END>")
		{
			break;
		}
		GOComponent* go = CreateComponent(read);
		go->SetID(TheGame::Instance()->GetID());
		if(go->Load(*file))
		{
			compMap.AddGOComponent(*go);
			go->PostInit();
			continue;
		}
		else
		{
			std::stringstream ss;
			ss<<"Loading failed for object with type ";
			ss<<type;
			ss<<" on line ";
			ss<<file->GetLineNum();
			ss<<" in file ";
			ss<<file->GetFileName();
			ReportError(ss.str());
		}
	}
}