#include "MeshManager.h"


MeshManager::MeshManager()
{

}
bool MeshManager::LoadMesh(const std::string& file, const std::string& name)
{
	if(meshMap_[name].Load(file))
	{
	return true;
	}
	return false;
}

ObjMesh* MeshManager::GetMesh(const std::string& name)
{
	return &meshMap_[name];
}