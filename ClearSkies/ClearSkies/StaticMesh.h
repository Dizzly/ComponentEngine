#ifndef STATICMESH_H_INCLUDED
#define STATICMESH_H_INCLUDED
#include "GOComponent.h"
#include <string>
#include <Vec3.h>

class StaticMeshLO: public GOComponentLO
{
public:
	~StaticMeshLO();
	StaticMeshLO();
	const char* GetTypeName()const override;
public:
	static const char* TYPENAME;

public:
	bool loadMesh;
	std::string meshTag;

	bool loadScale;
	Vec3f scale;

	bool loadRot;
	Vec3f rot;

	bool loadColor;
	Vec3f color;
};


class StaticMesh:public GOComponent
{
public:
	void Draw()const override;
	void Update()override;
	const char* GetTypeName()const override;
	bool Load(File& file) override;
	bool Load(GOComponentLO* loadObject) override;
	void Destroy() override;
	void PassEvent(EventPtrList* eve)override;
public:
	static const char* TYPENAME;
private:
	std::string meshTag_;
	Vec3f scale_;
	Vec3f rot_;
	Vec3f color_;
	
};


#endif