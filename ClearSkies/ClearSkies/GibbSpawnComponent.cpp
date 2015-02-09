#include "GibbSpawnComponent.h"
#include "GOComponentFactory.h"
#include "StaticMesh.h"
#include "Actor.h"
#include "ActorFactory.h"
#include "SpherePhysicsComponent.h"
#include <AngleConvert.h>
#include <Game.h>
const char* GibbSpawnComponent::TYPENAME="GibbSpawnComponent";
static GOComponent* Create()
{
	return new GibbSpawnComponent();
}

static const bool b=TheGOComponentFactory::Instance()->AddComponentFunc(GibbSpawnComponent::TYPENAME,
	Create);

GibbSpawnComponent::~GibbSpawnComponent()
{

}

void GibbSpawnComponent::Update()
{

}

void GibbSpawnComponent::Draw()const
{

}

void GibbSpawnComponent::Destroy()
{
	for(int i=0;i<numberOfGibbs_;++i)
	{
		int choice =rand()%meshes_.size();
		float speed=(((float)rand()/RAND_MAX)*(maxSpeed_-minSpeed_)+minSpeed_);
		Vec3f vel;
		float yRad =(DegToRad(rand()%360)+1);
		float xRad =(DegToRad(rand()%360)+1);
		float zRad= (DegToRad(rand()%360)+1);
		vel.x=cos(xRad);
		vel.z=sin(zRad);
		vel.y=sin(yRad);
		vel.Normalise();
		vel*=speed;
		Actor* a = TheActorFactory::Instance()->Create(std::string("Gibb"));
		a->GetTransform()->pos=parent_->GetCTransform()->pos;
		GOComponent* mesh=TheGOComponentFactory::Instance()->CreateComponent(StaticMesh::TYPENAME);
		a->AddGOComponent(*mesh);
		GOComponent* phy= a->GetGOComponent(SpherePhysicsComponent::TYPENAME);
		SpherePhysicsComponentLO phyLoader;
		StaticMeshLO meshLoader;
		meshLoader.loadMesh=true;
		meshLoader.meshTag=meshes_[choice];

		meshLoader.loadColor=true;
		meshLoader.color=color_;

		meshLoader.loadScale=true;
		meshLoader.scale=scale_;

		phyLoader.loadVelocity=true;
		phyLoader.velocity=vel;

		phyLoader.loadRotation=true;
		phyLoader.rotation=vel;

		mesh->Load(&meshLoader);
		phy->Load(&phyLoader);
		TheGame::Instance()->AddGameObject(a->GetID(),a);
	}
}

void GibbSpawnComponent::PassEvent(EventPtrList* eve)
{

}

bool GibbSpawnComponent::Load(File& file)
{
	std::string read;
	bool minVel=false,maxVel=false,
		gibbNums=false, 
		color=false, scale=false;
	while(file.GetString(&read))
	{
		if(read=="MinSpeed")
		{
			minVel=file.GetFloat(&minSpeed_);
		}
		if(read=="MaxSpeed")
		{
			maxVel=file.GetFloat(&maxSpeed_);
		}
		if(read=="Scale")
		{
			file.GetCSVec3f(&scale_);
		}
		if(read=="NumOfGibbs")
		{
			gibbNums=file.GetInteger(&numberOfGibbs_);
		}
		if(read=="GibbMesh")
		{
			std::string name;
			file.GetString(&name);
			meshes_.push_back(name);
		}
		if(read=="Color")
		{
			color=file.GetCSVec3f(&color_);
		}
		if(read=="/GibbSpawnComponent")
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
	}
	if(meshes_.size()<=0)
	{
		return false;
	}
	if(minSpeed_>maxSpeed_)
	{
		maxSpeed_=minSpeed_;
	}
	return minVel&&maxVel&&gibbNums;
}

bool GibbSpawnComponent::Load(GOComponentLO* loadObj)
{
	return false;
}

const char* GibbSpawnComponent::GetTypeName()const
{
	return TYPENAME;
}