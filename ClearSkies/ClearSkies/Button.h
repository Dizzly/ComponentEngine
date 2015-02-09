#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <BitmapFontUI.h>
#include <string>
#include <AABB2D.h>
class Button
{
public:
	Button(int tag);
	Button();
	~Button();
	virtual void Draw()=0;
	virtual void OnClick();
	virtual void OnOver();
	virtual void OnUp();
	virtual bool CheckCollision(Vec2f mousePos)=0;
	int GetTag()const;
protected:
	int tag_;
};

#endif