#ifndef SPHERECOLLIDER_H_INCLUDED
#define SPHERECOLLIDER_H_INCLUDED
#include "Collider.h"
#include <Transform.h>
#include <Vec3.h>

class SphereCollider:public Collider
{
public:
	~SphereCollider();
	SphereCollider(Vec3f pos=Vec3f(0,0,0), float radius=0);
	void Draw()const override;
	void Update()override;
	Vec3f GetPos()const;
	float GetRad()const;
	void SetPos(Vec3f pos);
	void SetRad(float rad);
	const char* GetTypeName()const override;
	bool Load(File& file)override;
	bool Load(GOComponentLO* loadObj)override;
	void PassEvent(EventPtrList* eve)override;
	void Destroy()override;
	void PostInit()override;
public:
	static const char *TYPENAME;
private:
	float radius_;
	const Transform* parentTransform_;
	Transform localTransform_;
};

#endif