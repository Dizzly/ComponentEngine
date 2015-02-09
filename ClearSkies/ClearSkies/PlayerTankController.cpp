#include "PlayerTankController.h"
#include <EventPoller.h>
#include "EventStore.h"

#include "PlayerControllerEvent.h"
#include "GOComponentFactory.h"
const char* PlayerTankController::TYPENAME="PlayerTankController";

static GOComponent* Create()
{
	return new PlayerTankController();
}

static const bool cheat=TheGOComponentFactory::Instance()->AddComponentFunc(PlayerTankController::TYPENAME,Create);
PlayerTankController::~PlayerTankController()
{}

PlayerTankController::PlayerTankController()
{
	TheEventPoller::Instance()->AddEventHandler(this);


	keyBinds_[SDLK_UP]="Forwards";
	keyBinds_[SDLK_DOWN]="Backwards";
	keyBinds_[SDLK_LEFT]="Left";
	keyBinds_[SDLK_RIGHT]="Right";
	keyBinds_[SDLK_SPACE]="Fire";
}
bool PlayerTankController::Load(GOComponentLO* loadComp)
{
return false;
}
bool PlayerTankController::Load(File& file)
{
	std::string read;
	int upBind=0,downBind=0,leftBind=0,rightBind=0, fireBind=0;
	bool right=false,left=false,up=false,down=false,fire=false;
	while(file.GetString(&read))
	{	
		if(read=="Right")
		{
		right=file.GetInteger(&rightBind);
		}
		if(read=="Left")
		{
		left=file.GetInteger(&leftBind);
		}
		if(read=="Forwards")
		{
		up=file.GetInteger(&upBind);
		}
		if(read=="Backwards")
		{
		down=file.GetInteger(&downBind);
		}
		if(read=="Fire")
		{
		fire=file.GetInteger(&fireBind);
		}
		if(read=="/PlayerTankController")
		{break;}
	}

	if(up&&down&&left&&right&&fire)
	{
		keyBinds_[(SDLKey)upBind]="Forwards";
		keyBinds_[(SDLKey)downBind]="Backwards";
		keyBinds_[(SDLKey)leftBind]="Left";
		keyBinds_[(SDLKey)rightBind]="Right";
		keyBinds_[(SDLKey)fireBind]="Fire";
		return true;
	}
	return false;
}

void PlayerTankController::Update()
{
	int i=0;
}

void PlayerTankController::OnKeyboardEvent(const SDL_KeyboardEvent& event)
{
	if(isActive_)
	{
			PlayerControllerEventPtr eve =new PlayerControllerEvent();
			eve->SetTargetID(parent_->GetID());
			if(event.state==SDL_PRESSED)
			{
				for(KeyBindingMap::iterator it=keyBinds_.begin();
					it!= keyBinds_.end();
					++it)
				{
					if(event.keysym.sym==it->first)
					{

						if(it->second=="Forwards")
						{
							eve->forwards_=2;
						}
						if(it->second=="Backwards")
						{
							eve->backwards_=2;
						}
						if(it->second=="Left")
						{
							eve->left_=2;
						}
						if(it->second=="Right")
						{
							eve->right_=2;
						}
						if(it->second=="Fire")
						{
							eve->fire_=1;
						}
					}
				}
			}
			if(event.state==SDL_RELEASED)
			{
				for(KeyBindingMap::iterator it=keyBinds_.begin();
					it!= keyBinds_.end();
					++it)
				{
					if(event.keysym.sym==it->first)
					{
						if(it->second=="Forwards")
						{
							eve->forwards_=0;
						}
						if(it->second=="Backwards")
						{
							eve->backwards_=0;
						}
						if(it->second=="Left")
						{
							eve->left_=0;
						}
						if(it->second=="Right")
						{
							eve->right_=0;
						}
						if(it->second=="Fire")
						{
							eve->fire_=0;
						}
					}
				}	
			}
			EventPtr ctrl(eve);
			TheEventStore::Instance()->AddEvent(ctrl);
	}
}

void PlayerTankController::OnMouseButtonEvent(const SDL_MouseButtonEvent& event)
{
	if(isActive_)
	{

	}
}

void PlayerTankController::OnMouseMotionEvent(const SDL_MouseMotionEvent& event)
{
	if(isActive_)
	{

	}
}

void PlayerTankController::Draw()const
{}

const char* PlayerTankController::GetTypeName()const
{
	return TYPENAME;
}

void PlayerTankController::Destroy()
{
	TheEventPoller::Instance()->RemoveEventHandler(this);
}
void PlayerTankController::PassEvent(EventPtrList*)
{

}