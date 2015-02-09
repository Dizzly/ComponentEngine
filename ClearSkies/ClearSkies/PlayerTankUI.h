#ifndef PLAYERTANKUI_H_INCLUDED
#define PLAYERTANKUI_H_INCLUDED
#include "GOComponent.h"
#include <GameObject.h>
#include <Texture.h>
#include <set>
class PlayerTankUI: public GOComponent
{
public:
	void Draw()const override;
	void Update() override;
	bool Load(File& file) override;
		bool Load(GOComponentLO* loadObj)override;
	void Destroy()override;
	void PassEvent(EventPtrList* ptr) override;
	const char* GetTypeName()const override;
	void PostInit()override;
	void DrawMiniMap()const;
	void DrawInfoBoard()const;
	void DrawAimer()const;
public:
	static const char* TYPENAME;
private:
	Transform* parentTransform_;
	typedef std::set<int> MapDraw;
	MapDraw mapDraw_;
	Texture mask_;
	Texture nullAim_;
	Texture lockAim_;
	bool isDrawing_;

	bool isLocked_;
	bool hasCursor_;
	int lives_;
	bool playerRespawn_;
	float scanRadius_;
	float scanFadeTime_;
};


#endif