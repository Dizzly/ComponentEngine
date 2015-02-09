#include "PlayerTankUI.h"
#include "GOComponentFactory.h"
#include <gl/glut.h>
#include "CollisionController.h"
#include <Screen.h>
#include "CreateActorEvent.h"
#include "DestroyActorEvent.h"
#include <AngleConvert.h>
#include <assert.h>
#include <Game.h>
#include "FontManager.h"
#include "PlayerDeathEvent.h"
#include "PlayerSpawnEvent.h"
#include "UIManager.h"
#include <HomebrewShapes.h>
#include <Timer.h>
#include "GetComponentEvent.h"
#include <sstream>
#include "ScoreManager.h"

#include <iostream>
const char* PlayerTankUI::TYPENAME="PlayerTankUI";
static bool isDrawing=false;

static GOComponent* Create()
{
	return new PlayerTankUI();
}

static const bool b=TheGOComponentFactory::Instance()->AddComponentFunc(
	PlayerTankUI::TYPENAME,
	Create);


void PlayerTankUI::Update()
{
	scanRadius_+=TheTimer::Instance()->GetDt()*5;
	if(scanRadius_>30)
	{
		scanRadius_=0;
	}
	Vec3f dir;
	float radY=DegToRad(parentTransform_->rot.y);
	dir.x=cos(radY);
	dir.z=sin(radY);


	if(TheCollisionController::Instance()->RaycastTest(parentTransform_->pos,dir,parent_->GetID(),"Enemy"))
	{
		isLocked_=true;
	}
	else
	{
		isLocked_=false;
	}
}

void PlayerTankUI::DrawMiniMap() const
{
	Vec2i screen=TheScreen::Instance()->ScreenBounds();
	Vec3f pos=parentTransform_->pos;
	Vec3f rot=parentTransform_->rot;


	glPushMatrix();
	{
		TheScreen::Instance()->SetPerspective();
		glViewport(0,screen.y-screen.y/6,screen.x/6,screen.y/6);
		Vec3f forwards;
		forwards.x=cos(DegToRad(rot.y));
		forwards.z=sin(DegToRad(rot.y));

		gluLookAt(pos.x,pos.y+55,pos.z,
			pos.x,pos.y,pos.z,
			forwards.x,0,forwards.z);

		float size=75;
		glColor3f(0,0.1,0);
		glBegin(GL_QUADS);
		{
			glVertex3f(pos.x-size,-2,pos.z-size);
			glVertex3f(pos.x+size,-2,pos.z-size);
			glVertex3f(pos.x+size,-2,pos.z+size);
			glVertex3f(pos.x-size,-2,pos.z+size);
		}
		glEnd();
		glColor3f(0,1,0);
		DrawCircle(Vec2f(pos.x,pos.z),scanRadius_);
		for(MapDraw::const_iterator it=mapDraw_.begin();
			it!=mapDraw_.end();
			++it)
		{
			GameObject* g=TheGame::Instance()->GetGameObject(*it);
			if(g)
			{
				g->Draw();
			}
		}
		mask_.Begin();
		glColor3f(0,1,0);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0,0);
			glVertex3f(pos.x-size,1,pos.z-size);
			glTexCoord2f(1,0);
			glVertex3f(pos.x+size,1,pos.z-size);
			glTexCoord2f(1,1);
			glVertex3f(pos.x+size,1,pos.z+size);
			glTexCoord2f(0,1);
			glVertex3f(pos.x-size,1,pos.z+size);

		}
		glEnd();
		mask_.End();
	}
	glPopMatrix();
	glViewport(0,0,screen.x,screen.y);
}

void PlayerTankUI::DrawInfoBoard()const
{
	Vec2i screen= TheScreen::Instance()->ScreenBounds();
	glPushMatrix();
	{
		glBegin(GL_QUADS);
		{
			glColor3f(0,1,0);
			glVertex3f(1,0.58,0);
			glVertex3f(-1,0.58,0);
			glVertex3f(-1,1,0);
			glVertex3f(1,1,0);

			glColor3f(0,0,0);
			glVertex3f(1,0.6,0);
			glVertex3f(-1,0.6,0);
			glVertex3f(-1,1,0);
			glVertex3f(1,1,0);	
		}
		glEnd();
		glColor3f(0,1,0);
		std::stringstream ss;
		ss<<lives_;
		BitmapFontUI* font=TheFontManager::Instance()->GetBitUIFont("UIFont");
		font->DynamicDraw("Lives:",Vec2f(0.4,0.90),Vec2f(0.55,0.95));
		font->Draw(ss.str(),Vec2f(0.55,0.90),0.04);
		ss.str("");
		ss<<TheScoreManager::Instance()->GetCurrentScore();
		font->DynamicDraw("Score:",Vec2f(0.4,0.75),Vec2f(0.55,0.8));
		font->Draw(ss.str(),Vec2f(0.55,0.75),0.04);
		ss.str("");
		ss<<TheScoreManager::Instance()->GetHighScore();
		font->DynamicDraw("HighScore:",Vec2f(0.4,0.65),Vec2f(0.64,0.7));
		font->Draw(ss.str(),Vec2f(0.65,0.65),0.04);
	}
	glPopMatrix();
}

void PlayerTankUI::DrawAimer()const
{
	if(hasCursor_)
	{
		glPushMatrix();
		{

			if(isLocked_)
			{
				lockAim_.Begin();
			}
			else
			{
				nullAim_.Begin();
			}
			glColor3f(1,1,1);
			glBegin(GL_QUADS);
			{
				glTexCoord2f(0,0);
				glVertex3f(0.3,0.3,0);
				glTexCoord2f(0,1);
				glVertex3f(0.3,-0.3,0);
				glTexCoord2f(1,1);
				glVertex3f(-0.3,-0.3,0);
				glTexCoord2f(1,0);
				glVertex3f(-0.3,0.3,0);
			}
			glEnd();
			if(isLocked_)
			{
				lockAim_.End();
			}
			else
			{
				nullAim_.End();
			}
		}
		glPopMatrix();
	}
}

void PlayerTankUI::Draw()const
{
	if(!isDrawing)
	{
		glPushMatrix();

		isDrawing=true;

		Vec2i theScreen =TheScreen::Instance()->ScreenBounds();
		

		DrawInfoBoard();
		DrawMiniMap();
		DrawAimer();
		

		glPopMatrix();
		glColor3f(1,1,1);
		isDrawing=false;
		glEnable(GL_DEPTH_TEST);
	}
}

void PlayerTankUI::PostInit()
{
	parentTransform_=parent_->GetTransform();
	isLocked_=false;
}

bool PlayerTankUI::Load(GOComponentLO* loadComp)
{
return false;
}

bool PlayerTankUI::Load(File& file)
{
	std::string read;
	bool mc=false, voidc=false, lockc=false;
	hasCursor_=false;
	while(file.GetString(&read))
	{
		if(read=="MapMaskGraphic")
		{
			std::string filename;
			file.GetString(&filename);
			mc=mask_.Load(filename);
		}
		if(read=="VoidAimGraphic")
		{
			std::string filename;
			file.GetString(&filename);
			voidc=nullAim_.Load(filename);
		}
		if(read=="LockAimGraphic")
		{
			std::string filename;
			file.GetString(&filename);
			lockc=lockAim_.Load(filename);
		}
		if(read=="/PlayerTankUI")
		{
			break;
		}
	}
	if(voidc&&lockc)
	{
		hasCursor_=true;
	}
	shouldDraw_=false;
	TheUIManager::Instance()->AddUIElement(this);
	scanRadius_=0;
	return(voidc&&lockc);
}

void PlayerTankUI::Destroy()
{
	lives_=0;
	TheUIManager::Instance()->RemoveUIElement(this);
}

const char* PlayerTankUI::GetTypeName()const
{
	return TYPENAME;
}

void PlayerTankUI::PassEvent(EventPtrList* ptr)
{
	for(EventPtrList::iterator it=ptr->begin();
		it!=ptr->end();
		++it)
	{
		if((*it)->GetEventType()==CreateActorEvent::TYPENAME)
		{
			CreateActorEventPtr create=it->DynamicCast(CreateActorEventPtr());
			assert(ptr);
			if(create->createdActor->HasTag(std::string("Mappable")))
			{
				mapDraw_.insert(create->createdActor->GetID());
			}
		}
		if((*it)->GetEventType()==DestroyActorEvent::TYPENAME)
		{
			DestroyActorEventPtr destro=it->DynamicCast(DestroyActorEventPtr());
			assert(destro);
			MapDraw::iterator it=mapDraw_.find(destro->destroyActorID_);
			if(it!=mapDraw_.end())
			{
				mapDraw_.erase(it);
			}
		}
		if((*it)->GetEventType()==PlayerSpawnEvent::TYPENAME)
		{
			PlayerSpawnEventPtr spawn=it->DynamicCast(PlayerSpawnEventPtr());
			assert(spawn);
			if(spawn->spawnID_==parent_->GetID())
			{
				lives_=spawn->livesLeft_;
				playerRespawn_=false;
			}
		}
		if((*it)->GetEventType()==PlayerDeathEvent::TYPENAME)
		{
			PlayerDeathEventPtr death=it->DynamicCast(PlayerDeathEventPtr());
			assert(death);
			if(death->deathID_=parent_->GetID())
			{
				playerRespawn_=true;
			}
		}
	}
}