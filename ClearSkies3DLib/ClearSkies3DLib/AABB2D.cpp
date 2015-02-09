#include "AABB2D.h"
AABB2D::AABB2D()
{
    minX_=0.0f;
    minY_=0.0f;
    maxX_=0.0f;
    maxY_=0.0f;
}

AABB2D::AABB2D(float minX,float minY, float maxX,float maxY)
{
    minX_=minX;
    minY_=minY;
    maxX_=maxX;
    maxY_=maxY;
}

AABB2D::AABB2D(Vec2f min, Vec2f max)
{
	minX_=min.x;
	minY_=min.y;
	maxX_=max.x;
	maxY_=max.y;
}
bool AABB2D::Intersects(const AABB2D& otherBox)const
{
    if(minX_<otherBox.maxX_ &&
        otherBox.minX_ <maxX_&&
        minY_ <otherBox.maxY_&&
        otherBox.minY_<maxY_)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool AABB2D::Intersects(const Vec2f& point)const
{
    if(minX_<point.x&&
        point.x<maxX_&&
        minY_<point.y&&
        point.y<maxY_)
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool AABB2D::IsOutside(const AABB2D& box)const
{
    if(box.minX_>minX_||
        maxX_>box.maxX_||
        box.minY_>minY_||
        maxY_>box.maxY_)
    {
        return true;
    }
    else
    {
        return false;
    }
}