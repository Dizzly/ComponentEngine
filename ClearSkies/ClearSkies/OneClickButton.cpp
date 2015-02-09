#include "OneClickButton.h"
#include "FontManager.h"
#include <gl/glut.h>
OneClickButton::OneClickButton(int tag, 
	std::string fontTag,
	std::string spriteTag,
	AABB2D& box,
	std::string text): 
	color_(1,1,1), 
	box_(box), 
	fontTag_(fontTag),
	spriteTag_(spriteTag),
	text_(text)
{
	tag_=tag;
}

OneClickButton::~OneClickButton()
{}

void OneClickButton::Draw()
{
	glPushMatrix();
	{
		glColor3f(color_.x,color_.y,color_.z);
		BitmapFontUI* bfu =TheFontManager::Instance()->GetBitUIFont(fontTag_);
		bfu->DynamicDraw(text_,Vec2f(box_.minX_,box_.minY_),Vec2f(box_.maxX_,box_.maxY_));
	}
	glPopMatrix();
}

void OneClickButton::OnClick()
{
	color_=Vec3f(1,0,0);
}

void OneClickButton::OnOver()
{
	color_=Vec3f(0.1f,0,0);
}

void OneClickButton::OnUp()
{
	color_=Vec3f(1,1,1);
}

bool OneClickButton::CheckCollision(Vec2f mousePos)
{
	return box_.Intersects(mousePos);
}