#ifndef MESHMANAGER_H_INCLUDED
#define MESHMANAGER_H_INCLUDED
#include <Singleton.h>
#include <NonCopyable.h>
#include <string>
#include <ObjMesh.h>
#include <map>

class MeshManager;
typedef Singleton<MeshManager> TheMeshManager;

class MeshManager:public NonCopyable
{
public:
	bool LoadMesh(const std::string& file, const std::string& name);
	ObjMesh* GetMesh(const std::string& name);
private:
MeshManager();
friend TheMeshManager;
private:
	typedef std::map<std::string,ObjMesh> MeshMap;
	MeshMap meshMap_;
};

#endif