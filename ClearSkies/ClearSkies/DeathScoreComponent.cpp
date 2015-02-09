#include "DeathScoreComponent.h"
#include <assert.h>
const char* DeathScoreComponent::TYPENAME="DeathScoreComponent";
#include "ScoreManager.h"
static GOComponent* Create()
{
return new DeathScoreComponent();
}

static const bool onOrOff=TheGOComponentFactory::Instance()->AddComponentFunc(
	DeathScoreComponent::TYPENAME,Create);

void DeathScoreComponent::Draw()const
{}

void DeathScoreComponent::Update()
{}

const char* DeathScoreComponent::GetTypeName()const
{
return TYPENAME;
}
bool DeathScoreComponent::Load(GOComponentLO* loadComp)
{
return false;
}

bool DeathScoreComponent::Load(File& file)
{
	std::string read;
	bool value=false;
	while(file.GetString(&read))
	{
		if(read=="ScoreValue")
		{
			file.GetInteger(&scoreValue_);
			value=true;
		}
		if(read=="/DeathScoreComponent")
		{
		break;
		}
	}
	isActive_=false;
	return value;
}

void DeathScoreComponent::Destroy()
{
	TheScoreManager::Instance()->AddScore(scoreValue_);
}

void DeathScoreComponent::PassEvent(EventPtrList* eve)
{

}