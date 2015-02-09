#include "LoadState.h"
#include "FontManager.h"
#include "SplashState.h"
#include "MeshManager.h"
#include <Game.h>
#include <Skybox.h>
#include "OneClickButton.h"
#include "LoadLevel.h"
#include <time.h>
#include "ScoreManager.h"
#include "PlayState.h"
#include "GraphicsOptions.h"
#include <ReportError.h>
LoadState::ButtonVecMap LoadState::buttonMap_;
LoadState::~LoadState()
{}

LoadState::LoadState()
{
	shouldRestart_=false;
}

void LoadState::Update()
{
	TheGame::Instance()->ClearGameObjects();
	TheScoreManager::Instance()->ClearScore();
	if(shouldRestart_==false)
	{
		GraphicsOptions::WIREFRAME_MODELS=true;
		srand(time(NULL));
		glEnable(GL_BLEND);
		glBlendFunc(GL_ZERO,GL_SRC_COLOR);
		glLineWidth(2);
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT_MODEL_TWO_SIDE);
		TheScoreManager::Instance()->Load();



		TheFontManager::Instance()->AddBitUIFont("Fonts/Vector.png","MenuFont",16);
		TheFontManager::Instance()->AddBitUIFont("Fonts/Vector.png","UIFont",16);

		TheMeshManager::Instance()->LoadMesh("Models/Tanky.obj","TankMesh");
		TheMeshManager::Instance()->LoadMesh("Models/CubeWall.obj","CubeWall");
		TheMeshManager::Instance()->LoadMesh("Models/Bullet.obj","Bullet");

		TheSkybox::Instance()->Load("Textures/VecHill/VecHill_",".png",7);

		buttonMap_["MainMenu"].push_back(new OneClickButton(1,"MenuFont","OneClickButtonSprite",AABB2D(-0.5,-0.4,0.5,-0.2),"<Quit>"));
		buttonMap_["MainMenu"].push_back(new OneClickButton(2,"MenuFont","OneClickButtonSprite",AABB2D(-0.5,-0.2,0.5,0),"<Play>"));
		buttonMap_["GameOverMenu"].push_back(new OneClickButton(1,"MenuFont","OneClickButtonSprite",AABB2D(-0.5,-0.4,0.5,-0.2),"<Submit>"));
		buttonMap_["GameOverMenu"].push_back(new OneClickButton(2,"MenuFont","OneClickButtonSprite",AABB2D(-0.5,-0.2,0.5,0),"<Replay>"));

		File soundFile;
		if(!soundFile.OpenRead("Sounds/SoundConfig.txt"))
		{
			ReportError("Could not open the SoundConfig file in Sounds");
		}
		else
		{
			TheAudioManager::Instance()->Load(soundFile);
		}

		LoadTemplates(std::string("Config/Templates.txt"));
	}
	LoadLevel(std::string("Config/Start.txt"));
	if(shouldRestart_==false)
	{
	TheGame::Instance()->SetState(TheSplashState::Instance());
	shouldRestart_=true;
	}
	else
	{
	TheGame::Instance()->SetState(ThePlayState::Instance());
	}
}

bool LoadState::LoadMenu(const std::string& state, Menu& menu)
{
	ButtonPVec& butt =buttonMap_[state];
	if(butt.empty())
	{
		return false;
	}
	menu.ClearButtons();
	for(ButtonPVec::iterator it=butt.begin();
		it!=butt.end();
		++it)
	{
		menu.AddButton(*it);
	}
	return true;

}

void LoadState::Draw()
{

}

void LoadState::OnActive()
{

}

void LoadState::OnInactive()
{

}

