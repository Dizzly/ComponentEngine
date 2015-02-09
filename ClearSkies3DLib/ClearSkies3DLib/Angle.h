#ifndef ANGLE_H_INCLUDED
#define ANGLE_H_INCLUDED

class Angle// ready to use, but not implemented just yet, nice and simple though
{
public:
	Angle();
	float SetDegrees(float deg);//returns the radian
	float SetRadian(float rad);//returns the degree
	float GetDegree()const;
	float GetRadian()const;
private:
	float degrees_;
	float radian_;
};

#endif