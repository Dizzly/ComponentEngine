#ifndef DEFAULTWEAPONCOMPONENT_H_INCLUDED
#define DEFAULTWEAPONCOMPONENT_H_INCLUDED
#include "GOComponent.h"
#include <list>
class DefaultWeaponComponent:public GOComponent
{
public:
	void Update()override;
	void Draw()const override;
	void Destroy()override;
	bool Load(File& file)override;
		bool Load(GOComponentLO* loadObj)override;
	const char* GetTypeName()const override;
	void PassEvent(EventPtrList* eve)override;
	void PostInit() override;
public:
	static const char* TYPENAME;
private:
	void Fire();
private:
	typedef std::list<int> BulletIDs;
	BulletIDs bulletIDs;
	int maxBulletsOut_;
	const Transform* parentTransform_;
	std::string fireSound_;
};

#endif