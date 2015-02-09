#ifndef AABB2D_INCLUDED_H
#define AABB2D_INCLUDED_H
#include "Vec2.h"

struct AABB2D
{
    AABB2D();
    AABB2D(float inX,float inY,float mxX,float mxY);
	AABB2D(Vec2f min,Vec2f max);
    bool Intersects(const AABB2D& otherBox)const;
    bool Intersects(const Vec2f& point)const;
    bool IsOutside(const AABB2D& otherBox)const;
    float minX_,minY_,maxX_,maxY_;
};

#endif
