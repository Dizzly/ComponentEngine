#ifndef COLLISIONCONTROLLER_H_INCLUDED
#define COLLISIONCONTROLLER_H_INCLUDED
#include <map>
#include <Singleton.h>
#include <NonCopyable.h>
#include "Collider.h"
#include <LineSegment.h>
// ray cast checks
//collision functions that can be added
// and each collision group only collides with things in the same group
class CollisionController;
typedef Singleton<CollisionController> TheCollisionController;
class CollisionController:public NonCopyable
{
public:
	typedef std::list<Collider*> ColliderList;
	typedef std::map<int,ColliderList> ColliderMap;
	typedef std::pair<std::string, std::string> TypePair;
	typedef bool (*CollisionCheck)(const Collider* obj1, const Collider* obj2);
	typedef bool (*RayCastCheck)(const Collider* obj1, const LineSegment* ray);
	typedef std::map<TypePair,CollisionCheck> CheckFuncs;
	typedef std::map<std::string,RayCastCheck> RayCastCheckFuncs;
public:
	void CheckCollisions();
	bool AddCollisionCheck(CollisionCheck c,TypePair& p);
	bool AddRayCastCheck(RayCastCheck,std::string& type);
	void AddCollider(Collider* c);
	void RemoveCollider(Collider* c);

	bool RaycastTest(Vec3f& start, Vec3f& dir,int ID,std::string tag="");
	bool TestCollision(const Collider* c);
private:
	CollisionController();
	friend TheCollisionController;
private:
	ColliderMap colliders_;
	CheckFuncs collisionFuncs_;
	RayCastCheckFuncs rayFuncs_;

};

#endif