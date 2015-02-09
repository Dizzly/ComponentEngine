#include "TileFunctions.h"

float RoundTo(float floatToRound,int multiple)
{
    int num=(int)floatToRound;
    if(multiple==0)
    {
        return (float)num;
    }

    int remainder=num%multiple;
    if(remainder==0)
    {
        return (float)num;
    }
    if(remainder>10)
    {
        return (float)num+multiple-remainder;
    }
    else
    {
        return (float)num-remainder;
    }

}

Vec2f Settle(Vec2f vec)
{
    return Vec2f(RoundTo(vec.x,20),RoundTo(vec.y,20)+5);
}
