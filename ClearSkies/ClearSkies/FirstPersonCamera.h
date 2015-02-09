#ifndef FIRSTPERSONCAMERA_H_INCLUDED
#define FIRSTPERSONCAMERA_H_INCLUDED
#include "GOComponent.h"
#include "Camera.h"
//A first person camera that controls as  you would expect off the parent controller.
//With further working you would have a looking transform as well as the player transform
class FirstPersonCamera:public GOComponent
{
public:
	void Draw()const override;
	void Update()override;
	const char* GetTypeName()const override;
	bool Load(File& file)override;
		bool Load(GOComponentLO* loadObj)override;
	void Destroy()override;
	void PassEvent(EventPtrList* ptr)override;
	void PostInit()override;
	static const char* TYPENAME;
private:

	Camera* cam_;
	const Transform* parentTransform_;
	Transform localTransform_;
};
#endif