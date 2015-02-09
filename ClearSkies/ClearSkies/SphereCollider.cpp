#include "SphereCollider.h"
#include "CollisionController.h"
#include "GOComponentFactory.h"
#include <Transform.h>


//debug
#include <gl/glut.h>


const char* SphereCollider::TYPENAME="SphereCollider";
static GOComponent* Create()
{
	return new SphereCollider();
}

static const bool cheat=TheGOComponentFactory::Instance()->AddComponentFunc(SphereCollider::TYPENAME,Create);



SphereCollider::SphereCollider(Vec3f pos, float radius)
{	
	localTransform_.pos=pos;
	radius_=radius;
	parentTransform_=0;
}

SphereCollider::~SphereCollider()
{
		TheCollisionController::Instance()->RemoveCollider(this);
}
void SphereCollider::SetPos(Vec3f pos)
{
	localTransform_.pos=pos;
}

void SphereCollider::SetRad(float rad)
{
	radius_=rad;
}

Vec3f SphereCollider::GetPos()const
{
	Vec3f pos=localTransform_.pos;
	if(parentTransform_) 
	{pos+=parentTransform_->pos;}
	return	pos;
}

float SphereCollider::GetRad()const
{
	return radius_;
}

const char* SphereCollider::GetTypeName()const
{
	return TYPENAME;
}
bool SphereCollider::Load(GOComponentLO* loadComp)
{
return false;
}
bool SphereCollider::Load(File& file)
{
	std::string read;
	bool pos=false,rad=false,colG=false;
	while(file.GetString(&read))
	{
		if(read=="Position")
		{
			pos=file.GetCSVec3f(&localTransform_.pos);
		}
		if(read=="Radius")
		{
			rad=file.GetFloat(&radius_);
		}
		if(read=="CollisionGroup")
		{
			colG=file.GetInteger(&collisionGroup_);
		}
		if(read=="/SphereCollider")
		{
		break;
		}
	}

	if(pos&&rad&&colG)
	{
	TheCollisionController::Instance()->AddCollider(this);
		return true;
	}
	return false;
}

void SphereCollider::PassEvent(EventPtrList* eve)
{

}

void SphereCollider::Destroy()
{

}

void SphereCollider::Draw()const
{
	Vec3f pos;
	if(parentTransform_)
	{
		pos=parentTransform_->pos;
	}
	pos+=localTransform_.pos;
	glPushMatrix();
	{
		glTranslatef(pos.x,pos.y,pos.z);
		//glutSolidSphere(radius_,5,5);
	}
	glPopMatrix();
}

void SphereCollider::Update()
{
}

void SphereCollider::PostInit()
{
	parentTransform_ = parent_->GetTransform();
}