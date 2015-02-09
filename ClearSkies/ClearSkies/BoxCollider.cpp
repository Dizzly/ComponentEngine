#include "BoxCollider.h"
#include "CollisionController.h"
#include <gl/glut.h>
#include "GOComponentFactory.h"
static GOComponent* Create()
{
	return new BoxCollider();
}
const char* BoxCollider::TYPENAME="BoxCollider";

static const bool cheat=TheGOComponentFactory::Instance()->AddComponentFunc(BoxCollider::TYPENAME,Create);

BoxCollider::~BoxCollider()
{
		TheCollisionController::Instance()->RemoveCollider(this);
}

void BoxCollider::Draw()const
{
}

Vec2f BoxCollider::XValues()const
{
	return Vec2f(minX_+parentTransform_->pos.x,maxX_+parentTransform_->pos.x);
}

Vec2f BoxCollider::YValues()const
{
	return Vec2f(minY_+parentTransform_->pos.y,maxY_+parentTransform_->pos.y);
}

Vec2f BoxCollider::ZValues()const
{
	return Vec2f(minZ_+parentTransform_->pos.z,maxZ_+parentTransform_->pos.z);
}
void BoxCollider::Update()
{

}

Vec3f BoxCollider::GetCenter()const
{
	return(Vec3f( minX_+(maxX_-minX_)/2,
		minY_+(maxY_-minY_)/2,
		minZ_+(maxZ_-minZ_)/2
		)+parentTransform_->pos
		);
}

bool BoxCollider::Load(GOComponentLO* loadComp)
{
return false;
}

bool BoxCollider::Load(File& file)
{
	std::string read;
	bool x=false,y=false,z=false,colG=false;
	while(file.GetString(&read))
	{
		if(read=="/BoxCollider")

		{
			break;
		}
		if(read=="XSize")
		{
			Vec2f vec;
			x=file.GetCSVec2f(&vec);
			minX_=vec.x;
			maxX_=vec.y;
			x=true;
		}
		if(read=="YSize")
		{
			Vec2f vec;
			y=file.GetCSVec2f(&vec);
			minY_=vec.x;
			maxY_=vec.y;
			y=true;
		}
		if(read=="ZSize")
		{
			Vec2f vec;
			z=file.GetCSVec2f(&vec);
			minZ_=vec.x;
			maxZ_=vec.y;
			
		}
		if(read=="CollisionGroup")
		{
			colG=file.GetInteger(&collisionGroup_);
		}
	}
	if(x&&y&&z&&colG)
	{
		TheCollisionController::Instance()->AddCollider(this);
		return true;
	}
	return false;
}

const char* BoxCollider::GetTypeName()const
{
	return TYPENAME;
}

void BoxCollider::Destroy()
{

}

void BoxCollider::PassEvent(EventPtrList* eve)
{

}

void BoxCollider::PostInit()
{
	parentTransform_=parent_->GetTransform();
}