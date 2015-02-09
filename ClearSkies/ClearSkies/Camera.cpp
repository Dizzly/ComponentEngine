#include "Camera.h"
#include <gl/glut.h>
Camera::Camera(Vec3f& pos, Vec3f& target, Vec3f& up)
{
	pos_=pos;
	target_=target;
	up_=up;
}

Camera::Camera():pos_(0,0,0), target_(0,0,-1), up_(0,1,0)
{

}

void Camera::UseCamera()
{
	gluLookAt(pos_.x,pos_.y,pos_.z,
		target_.x,target_.y,target_.z,
		up_.x,up_.y,up_.z);
}

void Camera::UseCameraZeroed()
{
	gluLookAt(0,0,0,
		target_.x-pos_.x,target_.y-pos_.y,target_.z-pos_.z,
		up_.x,up_.y,up_.z);
}
Vec3f Camera::GetPos()
{
	return pos_;
}

Vec3f Camera::GetTarget()
{
	return target_;
}

Vec3f Camera::GetUp()
{
	return up_;
}

void Camera::SetPos(Vec3f& pos)
{
	pos_=pos;
}

void Camera::SetTarget(Vec3f& target)
{
	target_=target;
}

void Camera::SetUp(Vec3f& up)
{
	up_=up;
}

