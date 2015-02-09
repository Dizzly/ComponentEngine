#include "StaticMesh.h"
#include "MeshManager.h"
#include <gl/glut.h>
#include <assert.h>
#include "GOComponentFactory.h"
#include "GraphicsOptions.h"
static GOComponent* Create()
{
	return new StaticMesh();
}

static const bool cheaty=TheGOComponentFactory::Instance()->AddComponentFunc(StaticMesh::TYPENAME,
	Create);
const char* StaticMesh::TYPENAME="StaticMesh";
const char* StaticMeshLO::TYPENAME="StaticMeshLO";

StaticMeshLO::~StaticMeshLO(){};
StaticMeshLO::StaticMeshLO()
{
loadMesh=false;
loadScale=false;
loadRot=false;
loadColor=false;
}
const char* StaticMeshLO::GetTypeName()const{return TYPENAME;}


bool StaticMesh::Load(GOComponentLO* loadComp)
{
	StaticMeshLO* lo=NULL;
	if(loadComp->GetTypeName()==StaticMeshLO::TYPENAME)
	{
		lo=dynamic_cast<StaticMeshLO*>(loadComp);
	}
	assert(lo);
	if(lo)
	{
	if(lo->loadMesh)meshTag_=lo->meshTag;
	if(lo->loadColor)color_=lo->color;
	if(lo->loadRot)rot_=lo->rot;
	if(lo->loadScale)scale_=lo->scale;
	if(!lo->loadColor)
	{
	color_=Vec3f(1,1,1);	
	}
	if(!lo->loadScale)
	{
	scale_=Vec3f(1,1,1);
	}
	return true;
	}
	return false;
}

bool StaticMesh::Load(File& file)
{
	std::string read;
	bool name=false,scale=false,color=false;
	while(file.GetString(&read))
	{
		if(read=="MeshName")
		{
			name=file.GetString(&meshTag_);
		}
		if(read=="Scale")
		{
			scale=file.GetCSVec3f(&scale_);
		}
		if(read=="Rot")
		{
			file.GetCSVec3f(&rot_);
		}
		if(read=="Color")
		{
			color=file.GetCSVec3f(&color_);
		}
		if(read=="/StaticMesh")
		{
		break;
		}
	}
	if(!color)
	{
	color_=Vec3f(1,1,1);	
	}
	if(!scale)
	{
	scale_=Vec3f(1,1,1);
	scale=true;
	}
	assert(TheMeshManager::Instance()->GetMesh(meshTag_));
	return name&&scale;
}
void StaticMesh::Draw()const
{
	Transform* tr= parent_->GetTransform();
	glPushMatrix();
	{
		if(GraphicsOptions::WIREFRAME_MODELS)
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			glColor3f(color_.x,color_.y,color_.z);
		}
		glTranslatef(tr->pos.x,tr->pos.y,tr->pos.z);
		glRotatef(-(tr->rot.x+rot_.x),1,0,0);
		glRotatef(-(tr->rot.y+rot_.y),0,1,0);
		glRotatef(-(tr->rot.z+rot_.z),0,0,1);
		glScalef(tr->scale.x,tr->scale.y,tr->scale.z);
		glScalef(scale_.x,scale_.y,scale_.z);
		TheMeshManager::Instance()->GetMesh(meshTag_)->Draw();
		if(GraphicsOptions::WIREFRAME_MODELS)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
			glColor3f(1,1,1);
		}
	}
	glPopMatrix();
}

void StaticMesh::Update()
{

}

const char* StaticMesh::GetTypeName()const
{
	return TYPENAME;
}

void StaticMesh::Destroy()
{

}

void StaticMesh::PassEvent(EventPtrList* eve)
{

}
