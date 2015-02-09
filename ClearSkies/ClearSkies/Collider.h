#ifndef COLLIDER_H_INCLUDED
#define COLLIDER_H_INCLUDED
#include "GOComponent.h"
//this base is just for a conceptual specilisation, and setting up collision groups
class Collider:public GOComponent
{
public:
	virtual ~Collider()=0{}
	int GetCollisionGroup()const{return collisionGroup_;}
	void SetCollisionGroup(int col){collisionGroup_=col;}
protected:
	int collisionGroup_;
};

#endif