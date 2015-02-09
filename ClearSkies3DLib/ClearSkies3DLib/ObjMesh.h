#ifndef OBJMESH_H_INCLUDED
#define OBJMESH_H_INCLUDED
#include "Vec3.h"
#include <string>
#include "ObjUsefulFunctions.h"
#include "Texture.h"

typedef std::map<std::string,Texture> TextureMap;
class ObjMesh
{
public:
	bool Load(const std::string& filename);
	bool LoadMtl(const std::string& dir);
	void Draw()const;
	void FlipNormals();
private:
	void DrawGroup(const Group&)const;
private:
	Groups groups_;
	Vecs coords_;
	UVs uvs_;
	Vecs normals_;
	MaterialMap materials_;
	std::string mtl_;
	TextureMap textures_;
};

#endif