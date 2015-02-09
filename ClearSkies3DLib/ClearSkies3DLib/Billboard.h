#ifndef BILLBOARD_H_INCLUDED
#define BILLBOARD_H_INCLUDED
#include "Vec2.h"
#include "Vec3.h"
#include "Texture.h"
class Billboard
{
public:
	Billboard(Vec3f pos,int width, int height):sideLength_(width,height),pos_(pos){}
	void Draw();
	void SetSideLength(Vec2f lengths);
	Vec2f GetSideLength()const;
	void SetPos(Vec3f);
private:
	Vec2f sideLength_;
	Vec3f pos_;
};

#endif
