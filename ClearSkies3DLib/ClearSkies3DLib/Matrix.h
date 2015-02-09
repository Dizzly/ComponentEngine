#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED
#include "Vec3.h"
#include "Vec4.h"
class Matrix
{
public:
	Matrix();
	Matrix(const float*&);
	const float* GetMatrix();
	void SetMatrix(const float veccy[]);
	void PrintMatrix();
	void Multiply(const float veccy[]);
	void Multiply(Vec3f&);
	void Multiply(Vec4f&);
	bool InvertMatrix();
	bool GetModelMatrix();
	bool GetProjectionMatrix();
	bool HasValue();

	void Translate(const Vec3f& ref);
	void RotateX(float rads);
	void RotateY(float rads);
	void RotateZ(float rads);
	void Scale(const Vec3f& ref);
	float operator[](int);


private:
	float colMatrix_[16];
	bool setFlag_;
};

#endif