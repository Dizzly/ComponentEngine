#ifndef CAMERAMANAGER_H_INCLUDED
#define CAMERAMANAGER_h_INCLUDED
#include <Singleton.h>
#include <NonCopyable.h>
#include <map>
#include "Camera.h"
//like camera this is a shell of compatiblity,
//This would work reasonably well, but when fully intergrated,
//it would accept camera changing events rather then direct calls

class CameraManager;
typedef Singleton<CameraManager> TheCameraManager;
//singleton
class CameraManager: public NonCopyable
{
public:
	Camera* GetCam(int ID);
	void RemoveCam(int ID);
	//Get camera from Id fucntion
	void AddCam(Camera& cam, int ID);
	//Set  new camera from ID
	Camera* CurrentCam();
	//Use current camera
private:
	CameraManager();
	~CameraManager();
	friend TheCameraManager;
private:
	typedef std::map<int,Camera> CamMap;
	//last ID picked
	Camera* lastUsed_;
	//camera map, key=id
	CamMap cams_;
	Camera* nullCam_;

};

#endif