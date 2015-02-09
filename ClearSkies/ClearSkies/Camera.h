#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED
#include <Vec3.h>
//intended to piggyback on another gameobject class
//as it has no ID it is not a game object
//at need be a game object camera could be made with its own event handling
//see camera manager.h
class Camera 
{
public:
	Camera(Vec3f& pos,Vec3f& target, Vec3f& up=Vec3f(0,1,0));
	Camera();
	void UseCamera();
	void UseCameraZeroed();
	void SetPos(Vec3f& pos);
	void SetTarget(Vec3f& target);
	void SetUp(Vec3f& up);
	Vec3f GetPos();
	Vec3f GetTarget();
	Vec3f GetUp();
private:
	int ID_;
	Vec3f pos_;
	Vec3f target_;
	Vec3f up_;
};

#endif