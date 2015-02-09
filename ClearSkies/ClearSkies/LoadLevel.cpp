#include "LoadLevel.h"
#include <File.h>
#include <ReportError.h>
#include <GameObjectFactory.h>
#include <Game.h>
#include "ActorFactory.h"

bool LoadLevel(const std::string& fileName)
{
	File level;
	if(!level.OpenRead(fileName))
	{
		ReportError("Couldnt find this file: "+fileName);
		return false;
	}
	return LoadLevel(&level);
}

bool LoadLevel(File* level)
{
	std::string result;
	while(level->GetString(&result))
	{
		if(result[0]=='-')
		{
			std::string name;
			name.insert(name.end(),++result.begin(),result.end());
			Actor* a =TheActorFactory::Instance()->Create(name);
			if(!a)
			{
				ReportError("Template "+result +" could not be found");
			}
			else
			{
				TheGame::Instance()->AddGameObject(a->GetID(),a);
			}
			continue;
		}
		GameObject* g=TheGameObjectFactory::Instance()->Create(result);
		assert(g);
		if(!g)
		{
			ReportError("Type error in "+level->GetFileName()+"\nDo not recognize: "+result);
			return false;
		}
		g->SetID(TheGame::Instance()->GetID());
		if(TheGame::Instance()->GetGameObject(g->GetID())==0)
		{
			g->Load(level);
			TheGame::Instance()->AddGameObject(g->GetID(),g);
		}
		else
		{
			TheGame::Instance()->GetGameObject(g->GetID())->Load(level);
			delete g;
		}
	}
	return true;
}

bool LoadTemplates(std::string& str)
{
	File temp;
	if(!temp.OpenRead(str))
	{
		assert(0);
		ReportError("Couldnt find this file: "+ str);
	}
	std::string read;
	while(temp.GetString(&read))
	{
		if(read[0]=='-')
		{
			std::string file;
			std::string name;
			name.insert(name.end(),++read.begin(),read.end());
			temp.GetString(&file);
			TheActorFactory::Instance()->AddType(name,file);
		}
	}
	return true;
}