#include"LoadLevel.h"
#include "File.h"
#include "ReportError.h"
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "Game.h"
bool LoadLevel(const std::string& levelFileName)
{
	File level;
	if(!level.OpenRead(levelFileName))
	{
		ReportError("Couldnt find this file: "+ levelFileName);
		return false;
	}
	std::string result;
	while(level.GetString(&result))
	{
		//create gameobject from results
		GameObject* g=TheGameObjectFactory::Instance()->Create(result);
		assert(g);
		if(!g)
		{
			ReportError("Type error in "+levelFileName+"\nDo not recognize :"+result);
			return false;
		}
		int key=0;
		level.GetInteger(&key);
		g->SetID(key);
		//load game object
		
		//add objects to game
		if(TheGame::Instance()->GetGameObject(key)==0)
		{
			g->Load(&level);
			TheGame::Instance()->AddGameObject(key,g);
		}
		else
		{
			delete g;
			TheGame::Instance()->GetGameObject(key)->Load(&level);
		}
	}
	return true;
}

bool LoadLevel(File* level)
{
	std::string result;
	while(level->GetString(&result))
	{
		//create gameobject from results
		GameObject* g=TheGameObjectFactory::Instance()->Create(result);
		assert(g);
		if(!g)
		{
			ReportError("Type error with line"+result+"\nDo not recognize");
			return false;
		}
		int key=0;
		level->GetInteger(&key);
		g->SetID(key);
		//load game object
		
		//add objects to game
		if(TheGame::Instance()->GetGameObject(key)==0)
		{
			TheGame::Instance()->AddGameObject(key,g);
			g->Load(level);
		}
		else
		{
			TheGame::Instance()->GetGameObject(key)->Load(level);
		}
	}
	return true;
}