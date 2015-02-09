#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED
#include"Vec3.h"
#include<vector>
typedef std::vector<float> FloatVec;
class Light
{
public:
	Light();
	void SetNumber(int num);
	void Draw();
	void Update();
	void SetPos(Vec3f newPos);
	Vec3f GetPos()const;
	void SetAmbient(Vec3f);
	void SetDiffuse(Vec3f);
	void SetSpecular(Vec3f);
	void SetConAt(float value);
	void SetLinAt(float value);
	void SetQuadAt(float value);
	void SetDir(Vec3f);
private:
	FloatVec ambient_, diffuse_,specular_,position_;
	float constantAt_,linearAt_,quadAt_;
	int number_;
};
#endif