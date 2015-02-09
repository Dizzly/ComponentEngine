#ifndef ONECLICKBUTTON_H_INCLUDED
#define ONECLICKBUTTON_H_INCLUDED
#include "Button.h"
#include <Vec3.h>
class OneClickButton:public Button
{
public:
	OneClickButton(int tag,std::string fontTag,
		std::string spriteTag,AABB2D& box,std::string text);
	~OneClickButton();
	virtual void Draw()override;
	virtual void OnClick()override;
	virtual void OnOver()override;
	virtual void OnUp()override;
	virtual bool CheckCollision(Vec2f mousePos)override;
private:
	Vec3f color_;
	AABB2D box_;
	std::string text_;
	std::string fontTag_;
	std::string spriteTag_;
};

#endif