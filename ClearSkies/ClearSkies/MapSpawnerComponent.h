#ifndef MAPSPAWNERCOMPONENT_H_INCLUDED
#define MAPSPAWNERCOMPONENT_H_INCLUDED
#include "GOComponent.h"
#include <map>
#include <queue>
#include <string>
#include <vector>
#include <list>
class MapSpawnerComponent: public GOComponent
{
public:
	void Update()override;
	void Draw()const override;
	void Destroy()override;
	void PassEvent(EventPtrList* eve)override;
	bool Load(File& file)override;
		bool Load(GOComponentLO* loadObj)override;
	const char* GetTypeName()const override;
	void PostInit() override;
public:
	static const char* TYPENAME;
private:
	typedef std::map<int,const GameObject*> ObjectMap;
	ObjectMap walls_;
	ObjectMap enemies_;

	std::list<float> spawnTimes_;

private:
	void CheckDespawn();
	void SpawnHorizonWall();
	void SpawnWall();
	void SpawnEnemy();

private:
	float minEnemyRespawnTime_;
	float maxEnemyRespawnTime_;

	int maxEnemiesAtOnce_;
	float minEnemySpawnRange_;
	float maxEnemySpawnRange_;

	int minWallsAtOnce_;
	float horizonSpawnRange_;
	float horizonDespawnRange_;

	std::vector<std::string> wallNames_;
	std::vector<std::string> enemyNames_;

	const Transform* playerTransform_;
};

#endif