#ifndef COLLISIONSYSTEM_H_INCLUDED
#define COLLISIONSYSTEM_H_INCLUDED
#include "GameObject.h"

class CollisionSystem
{
public:
	virtual void Update(GameObjectMap*)=0;
	virtual ~CollisionSystem(){}
	typedef void (*CollisionHandler)(GameObject*,GameObject*);
	bool AddCollisionHandler(const std::string&, const std::string&,CollisionHandler);
protected:
	void HandleCollision(GameObject*, GameObject*);
private:
	typedef std::pair<std::string,std::string> TypePair;
	typedef std::map<TypePair, CollisionHandler>
		CollisionMap;
	CollisionMap m_collResponce;
};

#endif