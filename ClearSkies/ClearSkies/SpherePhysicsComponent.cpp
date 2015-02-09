#include"SpherePhysicsComponent.h"
#include <Timer.h>
#include <assert.h>
#include "GOComponentFactory.h"

#include <gl/glut.h>
const char* SpherePhysicsComponent::TYPENAME="SpherePhysicsComponent";
const char* SpherePhysicsComponentLO::TYPENAME="SpherePhysicsComponentLO";
Vec3f SpherePhysicsComponent::globalGravity_;

static GOComponent* Create()
{
return new SpherePhysicsComponent();
}
static const bool b=TheGOComponentFactory::Instance()->AddComponentFunc(SpherePhysicsComponent::TYPENAME,
	Create);


SpherePhysicsComponentLO::SpherePhysicsComponentLO()
{
	loadGravity=false;
	loadFriction=false;
	loadRestitution=false;
	loadGlobalGravity=false;
	loadVelocity=false;
	loadRotation=false;
	friction=0;
	restitution=0;
}
SpherePhysicsComponentLO::~SpherePhysicsComponentLO(){}
const char* SpherePhysicsComponentLO::GetTypeName()const {return TYPENAME;}

SpherePhysicsComponent::~SpherePhysicsComponent()
{

}

void SpherePhysicsComponent::Update()
{
	float dt=TheTimer::Instance()->GetDt();
	Vec3f pos=parentTransform_->pos;
	velocity_+=gravity_+globalGravity_;
	Vec3f move=velocity_;
	move*=dt;
	pos+=move;
	parentTransform_->pos=pos;
	parentTransform_->rot+=rotation_;
	if(pos.y<0)
	{
	Vec3f norm(0,1,0);
	Vec3f yVel=norm*(norm.Dot(velocity_));
	Vec3f xVel =velocity_-yVel;

	yVel*=-1;
	xVel*=friction_;
	yVel*=restitution_;
	velocity_=xVel+yVel;
	parentTransform_->pos.y=0.01;
	}
}

void SpherePhysicsComponent::Draw()const
{

}

void SpherePhysicsComponent::Destroy()
{}

const char* SpherePhysicsComponent::GetTypeName()const
{
	return TYPENAME;
}
bool SpherePhysicsComponent::Load(GOComponentLO* comp)
{
	SpherePhysicsComponentLO* load=NULL;
	if(comp->GetTypeName()==SpherePhysicsComponentLO::TYPENAME)
	{
	load=dynamic_cast<SpherePhysicsComponentLO*>(comp);
	}
	assert(load);
	if(load)
	{
	if(load->loadFriction)friction_=load->friction;
	if(load->loadRestitution)restitution_=load->restitution;
	if(load->loadGravity)gravity_=load->gravity;
	if(load->loadGlobalGravity)globalGravity_=load->globalGravity;
	if(load->loadVelocity)velocity_=load->velocity;
	if(load->loadRotation)rotation_=load->rotation;
	return true;
	}
	return false;
}
bool SpherePhysicsComponent::Load(File& file)
{
	std::string read;
	bool rest=false,frict=false;
	while(file.GetString(&read))
	{
		if(read=="GlobalGravity")
		{
			file.GetCSVec3f(&globalGravity_);
		}
		if(read=="Gravity")
		{
			file.GetCSVec3f(&gravity_);
		}
		if(read=="Restituion")
		{
			rest=file.GetFloat(&restitution_);
		}
		if(read=="Friction")
		{
			frict=file.GetFloat(&friction_);
		}
		if(read=="/SpherePhysicsComponent")
		{
			break;
		}
	}
	if(!frict)
	{
		friction_=0;
	}
	if(!rest)
	{
		restitution_=1;
	}
	return true;
}

void SpherePhysicsComponent::PassEvent(EventPtrList* eve)
{
	//collision and physics events would normally be used here
}

void SpherePhysicsComponent::PostInit()
{
	parentTransform_=parent_->GetTransform();
}
