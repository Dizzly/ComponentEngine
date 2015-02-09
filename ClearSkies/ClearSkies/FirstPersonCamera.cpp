#include "FirstPersonCamera.h"
#include "CameraManager.h"
#include "GOComponentFactory.h"
#include <AngleConvert.h>
#include <Matrix.h>

const char * FirstPersonCamera::TYPENAME="FirstPersonCamera";

static GOComponent* Create()
{
return new FirstPersonCamera;
}

static const bool sneak=TheGOComponentFactory::Instance()->AddComponentFunc(FirstPersonCamera::TYPENAME,
	Create);

void FirstPersonCamera::Draw()const
{
	TheCameraManager::Instance()->GetCam(ID_);
}

void FirstPersonCamera::Update()
{
	Vec3f pos=parentTransform_->pos;
	Matrix matrix;
	float yRad= DegToRad(parentTransform_->rot.y);
	matrix.RotateY(-yRad);
	Vec3f localPos=localTransform_.pos;
	matrix.Multiply(localPos);
	cam_->SetPos(pos+localPos);	
	Vec3f tar(parentTransform_->pos);
	tar.x+=cos(yRad)*100;
	tar.z+=sin(yRad)*100;
	cam_->SetTarget(tar);
}

const char* FirstPersonCamera::GetTypeName()const
{
return TYPENAME;
}
bool FirstPersonCamera::Load(GOComponentLO* loadComp)
{
return false;
}
bool FirstPersonCamera::Load(File& file)
{
	std::string read;
	bool offset=false;
	while(file.GetString(&read))
	{
		if(read=="Offset")
		{
			offset=file.GetCSVec3f(&localTransform_.pos);
		}
		if(read=="/FirstPersonCamera")
		{
			break;
		}
	}
	TheCameraManager::Instance()->AddCam(Camera(),ID_);
	//makes this the current camera to use.
	cam_=TheCameraManager::Instance()->GetCam(ID_);
	return true;
}

void FirstPersonCamera::PostInit()
{
	parentTransform_=parent_->GetTransform();
	
	Matrix matrix;
	float yRad= DegToRad(parentTransform_->rot.y);
	matrix.RotateY(yRad);
	Vec3f localPos=localTransform_.pos;
	matrix.Multiply(localPos);
	cam_->SetPos(Vec3f(parentTransform_->pos)+localPos);
	Vec3f tar(parentTransform_->pos);
	tar.x+=cos(yRad)*100;
	tar.z-=sin(yRad)*100;
	cam_->SetTarget(tar);
}

void FirstPersonCamera::Destroy()
{
	TheCameraManager::Instance()->RemoveCam(ID_);
}

void FirstPersonCamera::PassEvent(EventPtrList* eve)
{

}