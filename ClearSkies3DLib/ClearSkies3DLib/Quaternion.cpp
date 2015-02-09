// Maths for Game Programming
// Quaternion class - to be completed in lesson
// Jason Colman Qantm London 2009

#include <assert.h>
#ifdef WIN32
#define _USE_MATH_DEFINES
#endif
#include <math.h>
#include "Quaternion.h"

// TODO Default ctor - set to identity
Quaternion::Quaternion()
{
	w_=1.0f;
	x_=0;
	y_=0;
	z_=0;
}
// TODO Ctor - set from axis and angle
Quaternion::Quaternion(Vec3f axis, float angle)
{
	float halfAngle=angle*0.5;
	float sinHalfAngle =sin(halfAngle);
	x_=axis.x*sinHalfAngle;
	y_=axis.y*sinHalfAngle;
	z_=axis.z*sinHalfAngle;
	w_=cos(angle*0.5);
}
// TODO Normalise()
void Quaternion::Normalise()
{
	float sqrLength=x_*x_+y_*y_+z_*z_+w_*w_;
	sqrt(sqrLength);
	x_/=sqrLength;
	y_/=sqrLength;
	z_/=sqrLength;
	w_/=sqrLength;
}

void Quaternion::ToMatrix(float pMatrix[16]) const
{
    assert(pMatrix);

    pMatrix[ 0] = 1.0f - 2.0f * ( y_ * y_ + z_ * z_ ); 
    pMatrix[ 1] = 2.0f * (x_ * y_ + z_ * w_);
    pMatrix[ 2] = 2.0f * (x_ * z_ - y_ * w_);
    pMatrix[ 3] = 0.0f;  

    pMatrix[ 4] = 2.0f * ( x_ * y_ - z_ * w_ );  
    pMatrix[ 5] = 1.0f - 2.0f * ( x_ * x_ + z_ * z_ ); 
    pMatrix[ 6] = 2.0f * (z_ * y_ + x_ * w_ );  
    pMatrix[ 7] = 0.0f;  

    pMatrix[ 8] = 2.0f * ( x_ * z_ + y_ * w_ );
    pMatrix[ 9] = 2.0f * ( y_ * z_ - x_ * w_ );
    pMatrix[10] = 1.0f - 2.0f * ( x_ * x_ + y_ * y_ );  
    pMatrix[11] = 0.0f;  

    pMatrix[12] = 0;  
    pMatrix[13] = 0;  
    pMatrix[14] = 0;  
    pMatrix[15] = 1.0f;
}

Quaternion operator*(const Quaternion& p, const Quaternion& q)
{
    Quaternion r;

    r.w_ = p.w_ * q.w_ - p.x_ * q.x_ - p.y_ * q.y_ - p.z_ * q.z_;
    r.x_ = p.w_ * q.x_ + p.x_ * q.w_ + p.y_ * q.z_ - p.z_ * q.y_;
    r.y_ = p.w_ * q.y_ + p.y_ * q.w_ + p.z_ * q.x_ - p.x_ * q.z_;
    r.z_ = p.w_ * q.z_ + p.z_ * q.w_ + p.x_ * q.y_ - p.y_ * q.x_;

    return r;
}

Quaternion Slerp(const Quaternion& from, const Quaternion& to, float t)
{
    float to1[4];
    double omega, cosom, sinom, scale0, scale1;

    // calc cosine
    cosom = from.x_ * to.x_ + from.y_ * to.y_ + from.z_ * to.z_
        + from.w_ * to.w_;

    // adjust signs (if necessary)
    if (cosom < 0)
    { 
        cosom = -cosom; 
        to1[0] = - to.x_;
        to1[1] = - to.y_;
        to1[2] = - to.z_;
        to1[3] = - to.w_;
    } 
    else  
    {
        to1[0] = to.x_;
        to1[1] = to.y_;
        to1[2] = to.z_;
        to1[3] = to.w_;
    }

    // calculate coefficients

    static const double DELTA = 0.001;
    if ( (1.0 - cosom) > DELTA ) 
    {
        // standard case (slerp)
        omega = acos(cosom);
        sinom = sin(omega);
        scale0 = sin((1.0 - t) * omega) / sinom;
        scale1 = sin(t * omega) / sinom;
    } 
    else 
    {        
        // "from" and "to" quaternions are very close 
        //  ... so we can do a linear interpolation
        scale0 = 1.0 - t;
        scale1 = t;
    }

    Quaternion res;

    // calculate final values
    res.x_ = (float)(scale0 * (double)from.x_ + scale1 * (double)to1[0]);
    res.y_ = (float)(scale0 * (double)from.y_ + scale1 * (double)to1[1]);
    res.z_ = (float)(scale0 * (double)from.z_ + scale1 * (double)to1[2]);
    res.w_ = (float)(scale0 * (double)from.w_ + scale1 * (double)to1[3]);

    return res;
}