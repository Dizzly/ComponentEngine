#include "ActorFactory.h"
#include <Game.h>
#include <ReportError.h>
#include <assert.h>
#include <DirectoryFunctions.h>
ActorFactory::ActorFactory()
{}

Actor* ActorFactory::Create(std::string& name)
{
	TemplateLoadMap::iterator it= templateLoadMap_.find(name);
	if(it!=templateLoadMap_.end())
	{
		Actor* a=new Actor;
		a->SetID(TheGame::Instance()->GetID());
		File f;
		if(f.OpenRead(GetCWD()+templateLoadMap_[name]))
		{
			a->Load(&f);
			return a;
		}
		else
		{
			assert(0);
			return NULL;
		}
	}
	else
	{
		assert(0);
		return NULL;
	}
}

void ActorFactory::AddType(std::string& name, std::string& file)
{
	TemplateLoadMap::iterator it= templateLoadMap_.find(name);
	if(it==templateLoadMap_.end())
	{
		templateLoadMap_[name]=file;
	}
	else
	{
		assert(0);
	}
}