#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED
#include "Texture.h"
class UI
{
public:
	void Init();
	void Draw();
private:
	Vec2f topLeft_;
	Vec2f size_;
	Texture tex;
};


#endif