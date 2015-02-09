#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

struct Color
{
	float r,g,b,a;
	Color()
	{
		r,g,b,a=0;
	}
	Color(const Color& col)
	{
		r=col.r;
		g=col.g;
		b=col.b;
		a=col.a;
	}
};

#endif