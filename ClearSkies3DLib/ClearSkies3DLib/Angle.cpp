#include "Angle.h"
#include "AngleConvert.h"
Angle::Angle()
{
	degrees_=0;
	radian_=0;
}

float Angle::SetDegrees(float deg)
{
	degrees_=deg;
	radian_=DegToRad(degrees_);
	return radian_;
}

float Angle::SetRadian(float rad)
{
	radian_=rad;
	degrees_=RadToDeg(radian_);
	return degrees_;
}

float Angle::GetDegree()const
{
	return degrees_;
}

float Angle::GetRadian()const
{
	return radian_;
}