#include "Button.h"

Button::Button(int tag)
{
	tag_=tag;
}

Button::Button()
{
	tag_=-1;
}

Button::~Button()
{

}
void Button::OnClick()
{

}

void Button::OnOver()
{

}

void Button::OnUp()
{

}

void Button::Draw()
{
		
}

bool Button::CheckCollision(Vec2f mouse)
{
	return false;
}
int Button::GetTag()const
{
return tag_;
}