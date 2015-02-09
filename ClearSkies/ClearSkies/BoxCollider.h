#ifndef BOXCOLLIDER_H_INCLUDED
#define BOXCOLLIDER_H_INCLUDED
#include "Collider.h"
#include <Vec3.h>
class BoxCollider: public Collider
{
public:
	~BoxCollider();
	void Draw()const override;
	void Update()override;
	bool Load(File& file) override;
	bool Load(GOComponentLO* loadObj)override;
	const char*	GetTypeName()const override;
	void Destroy() override;
	void PassEvent(EventPtrList* eve)override;
	void PostInit();

	Vec3f GetCenter()const;
	Vec2f XValues()const;
	Vec2f YValues()const;
	Vec2f ZValues()const;

public:
	static const char* TYPENAME;
private:
	float minX_,maxX_;
	float minY_,maxY_;
	float minZ_,maxZ_;
	const Transform* parentTransform_;
};

#endif