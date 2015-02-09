#ifndef TANKMOVER_H_INCLUDED
#define TANKMOVER_H_INCLUDED
#include "GOComponent.h"
class TankMover:public GOComponent
{
public:
	void Draw()const override;
	void Update() override;
	bool Load(File& file) override;
		bool Load(GOComponentLO* loadObj)override;
	const char* GetTypeName()const override;
	void PassEvent(EventPtrList* eve)override;
	void PostInit()override;
	void Destroy()override;

	void Bump();
public:
	static const char* TYPENAME;
private:
	bool fKey_,bKey_,lKey_,rKey_;
	float fSpeed_,
			bSpeed_,
			turnSpeed_;
	Vec3f oldPos_;
	Transform* parentTransform_;
};

#endif