#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "NonCopyable.h"
#include "Singleton.h"
#include "Actor.h"
#include "GameObject.h"
#include "CollisionSystem.h"
#include <map>
#include <list>
#include <vector>

class Game;
class GameState;

typedef Singleton<Game> TheGame;

class Game: public NonCopyable
{
public: 
	void Run();
	void SetState(GameState* state);
	bool SetCollisionSystem(CollisionSystem* cs);
	CollisionSystem* GetCollisionSystem();
	void AddGameObject(int,GameObject*);
	void DeleteGameObject(int);
	void RemoveGameObject(int);
	void SafeDelete(int);
	GameObject* GetGameObject(int);
	void ClearGameObjects();
	void UpdateCollision();
	void UpdateGameObjects();
	void DrawGameObjects();
	int GetID();
private:
	Game();
	void Update();
	void Draw();

private:
	std::list<int> removeMe_;
	GameState* currentState_;
	friend TheGame;
	GameObjectMap gameObjects_;//make a specific draw and update function
	CollisionSystem* collisionSystem_;
	int IDCounter_;
};

#endif