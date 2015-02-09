#ifndef GIBBSPAWNCOMPONENT_H_INCLUDED
#define GIBBSPAWNCOMPONENT_H_INCLUDED
#include "GOComponent.h"
#include <vector>
class GibbSpawnComponent:public GOComponent
{
public:
	~GibbSpawnComponent();
	void Update()override;
	void Draw()const override;
	void Destroy()override;
	void PassEvent(EventPtrList* eve)override;
	bool Load(File& file)override;
	bool Load(GOComponentLO* loadObj)override;
	const char* GetTypeName()const override;
public:
	static const char* TYPENAME;
private:
	int numberOfGibbs_;
	Vec3f color_;
	Vec3f scale_;
	typedef std::vector<std::string> MeshTags;
	MeshTags meshes_;
	float maxSpeed_;
	float minSpeed_;
};

#endif