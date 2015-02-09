#include <assert.h>
#include "EventPoller.h"
#include "Game.h"
#include "Screen.h"
#include "Timer.h"
#include "CollisionSystem.h"
#include "GameState.h"
#include "ReportError.h"
Game::Game()
{
	currentState_=0;
	IDCounter_=0;
}

void Game::SetState(GameState* newState)
{
	 if(currentState_)
    {
        currentState_->OnInactive();
    }
    currentState_=newState;
    currentState_->OnActive();
}
bool Game::SetCollisionSystem(CollisionSystem* cs)
{
	collisionSystem_=cs;
	return true;
}
CollisionSystem* Game::GetCollisionSystem()
{
return collisionSystem_;
}

void Game::UpdateCollision()
{	
	if(collisionSystem_)
	{
		GameObjectMap temp=gameObjects_;
		collisionSystem_->Update(&temp);
	}
}
void Game::DrawGameObjects()
{
	for(std::map<int,GameObject*>::iterator it=gameObjects_.begin();
		it!=gameObjects_.end();
		++it)
	{
		it->second->Draw();
		
	}
}


void Game::SafeDelete(int i)
{
	removeMe_.push_back(i);
}

void Game::UpdateGameObjects()
{
	GameObjectMap GOMCopy = gameObjects_;
	for(GameObjectMap::iterator it=GOMCopy.begin();
		it!=GOMCopy.end();
		++it)
	{
		it->second->Update();
		
	}
	UpdateCollision();
	if(removeMe_.size()>0)
	{
		for(std::list<int>::iterator it=removeMe_.begin();
			it!=removeMe_.end();
			)
		{
			DeleteGameObject((*it));
			it=removeMe_.erase(it);
		}
	}
}

void Game::Run()
{
	while (true)
	{
		Update();
		Draw();
		TheScreen::Instance()->Flip();
	}
}
void Game::Update()
{
	TheTimer::Instance()->Update();
	TheEventPoller::Instance()->Update();
	assert(currentState_);
	currentState_->Update();
}
void Game::Draw()
{
	assert(currentState_);
	TheScreen::Instance()->Clear();
	currentState_->Draw();
}

void Game::AddGameObject(int key,GameObject* g)
{
	gameObjects_[key]=g;
}
void Game::DeleteGameObject(int key)
{
	GameObject* go = GetGameObject(key);
	assert(go);
	if(go==0)
	{
		ReportError("Game Object key not recognised");
	}
	go->Destroy();
	delete go;
	gameObjects_.erase(key);
}

void Game::RemoveGameObject(int key)
{
	GameObject* go=GetGameObject(key);
	assert(go);
	if(go==0)
	{
		ReportError("Game Object key not recognised");
	}
	gameObjects_.erase(key);
}

GameObject* Game::GetGameObject(int key)
{
	GameObjectMap::iterator it=gameObjects_.find(key);
	if(it==gameObjects_.end())
	{
		return 0;
	}
	return (*it).second;
}

void Game::ClearGameObjects()
{
	for(GameObjectMap::iterator it=gameObjects_.begin();
		it!=gameObjects_.end();
		)
	{
		it->second->Destroy();
		delete (*it).second;
		it=gameObjects_.erase(it);
	}
	IDCounter_=0;
	removeMe_.clear();
	gameObjects_.clear();
}

int Game::GetID()
{
	++IDCounter_;
	return IDCounter_;
}