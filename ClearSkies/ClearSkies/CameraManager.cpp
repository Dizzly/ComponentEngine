#include "CameraManager.h"
#include <ReportError.h>
#include <sstream>
CameraManager::CameraManager()
{
	lastUsed_=0;
	nullCam_=new Camera();
}

CameraManager::~CameraManager()
{
	delete nullCam_;
}

void CameraManager::RemoveCam(int ID)
{
	CamMap::iterator it=cams_.find(ID);
	if(it!=cams_.end())
	{
	cams_.erase(it);
	}
}
Camera* CameraManager::GetCam(int ID)
{
	CamMap::iterator it=cams_.find(ID);
	if(it==cams_.end())
	{
		std::stringstream ss;
		ss<<"There is no camera with ID ";
		ss<<ID;
		ss<<" found in the camera map";
		return NULL;
	}
	else
	{
		Camera* cammy=&cams_.at(ID);
		lastUsed_=cammy;
		return cammy;
	}
}

void CameraManager::AddCam(Camera& cam, int ID)
{
	cams_[ID]=cam;
}

Camera* CameraManager::CurrentCam()
{
	if(lastUsed_)
	{
		return lastUsed_;
	}
	else
	{
		return nullCam_;
	}
}
