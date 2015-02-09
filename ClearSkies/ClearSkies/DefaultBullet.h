#ifndef DEFAULTBULLET_H_INCLUDED
#define DEFAULTBULLET_H_INCLUDED
#include "GOComponent.h"
#include "Actor.h"
class DefaultBullet:public GOComponent
{
public:
	DefaultBullet();
	void Update()override;
	void Draw()const override;
	void Destroy()override;
	bool Load(File& file)override;
		bool Load(GOComponentLO* loadObj)override;
	void PassEvent(EventPtrList* eve)override;
	const char* GetTypeName()const override;
	void PostInit() override;
	void SetOwner(int id);
public:
	static const char* TYPENAME;
private:
	float speed_;
	float lifetime_;
	float timer_;
	Transform* parentTransform_;
	int ownerID_;
};

#endif