#include "ObjMesh.h"
#include "File.h"
#include <assert.h>
#include <gl/glut.h>
#include <SDL_image.h>
#include "DirectoryFunctions.h"
bool ObjMesh::Load(const std::string& filename)
{
    File f;
    if(!f.OpenRead(filename))
    {
        assert(0);
        return 0;
    }
    std::string read;
    std::string groupName;
    while(f.GetString(&read))
    {
        Strings data(Split(read,' '));
        if(data[0]=="v")
        {
            coords_.push_back(ToVec3(data));
        }
        if(data[0]=="vt")
        {
			Vec2f vec(ToVec2(data));
			vec.y*=-1;
            uvs_.push_back(vec);
        }
        if(data[0]=="vn")
        {
            normals_.push_back(ToVec3(data));
        }
        if(data[0]=="g")
        {
            groupName=data[1];
            groups_[groupName];
        }
        if(data[0]=="f")
        {
            Face f=ToFace(data);
            groups_[groupName].faces_.push_back(f);
        }
        if(data[0]=="mtllib")
        {
			mtl_=data[1];
			LoadMtl(f.GetFileName());
        }
		if(data[0]=="usemtl")
		{
			groups_[groupName].materialName_=data[1];
		}
    }
    return true;
}
void ObjMesh::FlipNormals()
{
for(Vecs::iterator it=normals_.begin();it!=normals_.end();++it)
{
	(*it)=-(*it);
}
}
bool ObjMesh::LoadMtl(const std::string& dir)
{
	File f;
    if(!f.OpenRead(GetCWD()+"\\"+ExtractDirectory(dir)+mtl_))
    {
        assert(0);
        return 0;
    }
    std::string read;
    std::string materialName;
    while(f.GetString(&read))
    {
		Strings data(Split(read,' '));
		if(data[0]=="newmtl")
		{
			materialName=data[1];
			materials_[data[1]]=new Material();
		}
		if(data[0]=="map_Kd")
		{
			materials_[materialName]->Load(data[1]);
		}
	}
	return true;
}

void ObjMesh::Draw()const
{

    for(Groups::const_iterator gIt=groups_.begin();
        gIt!=groups_.end();
        ++gIt)
    {
        const Group& g=(*gIt).second;
		MaterialMap::const_iterator mat=materials_.find(g.materialName_);
		bool backOff=0;
		if(mat != materials_.cend())
		{
				mat->second->Begin();
				backOff=1;
		}
		else
		{
			//assert(0);
		}
        DrawGroup(g);
		if(backOff)
		{
				mat->second->End();
		}
		
    }

}

void ObjMesh::DrawGroup(const Group& g)const
{
	    glBegin(GL_TRIANGLES);
    for(Faces::const_iterator fIt=g.faces_.begin();
            fIt!=g.faces_.end();
            ++fIt)
        {
            Vec3f a(coords_[(*fIt).pointIndex_[0]]);
            Vec3f b(coords_[(*fIt).pointIndex_[1]]);
            Vec3f c(coords_[(*fIt).pointIndex_[2]]);

            Vec3f na(normals_[(*fIt).normalIndex_[0]]);
            Vec3f nb(normals_[(*fIt).normalIndex_[1]]);
            Vec3f nc(normals_[(*fIt).normalIndex_[2]]);

            Vec2f uva(uvs_[(*fIt).uvIndex_[0]]);
            Vec2f uvb(uvs_[(*fIt).uvIndex_[1]]);
            Vec2f uvc(uvs_[(*fIt).uvIndex_[2]]);
            
            glTexCoord2f(uva.x,uva.y);
            glNormal3f(na.x,na.y,na.z);
            glVertex3f(a.x,a.y,a.z);
            glTexCoord2f(uvb.x,uvb.y);
            glNormal3f(nb.x,nb.y,nb.z);
            glVertex3f(b.x,b.y,b.z);
            glTexCoord2f(uvc.x,uvc.y);
            glNormal3f(nc.x,nc.y,nc.z);
            glVertex3f(c.x,c.y,c.z);
        }
	    glEnd();
}

