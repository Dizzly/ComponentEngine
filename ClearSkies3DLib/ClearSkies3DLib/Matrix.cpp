#include "Matrix.h"
#include <gl/glut.h>
Matrix::Matrix()
{
	colMatrix_[0]=0;
	colMatrix_[1]=0;
	colMatrix_[2]=0;
	colMatrix_[3]=0;

	colMatrix_[4]=0;
	colMatrix_[5]=0;
	colMatrix_[6]=0;
	colMatrix_[7]=0;

	colMatrix_[8]=0;
	colMatrix_[9]=0;
	colMatrix_[10]=0;
	colMatrix_[11]=0;

	colMatrix_[12]=0;
	colMatrix_[13]=0;
	colMatrix_[14]=0;
	colMatrix_[15]=0;
	setFlag_=false;
}

Matrix::Matrix(const float*& veccy)
{
	colMatrix_[0]=veccy[0];
	colMatrix_[1]=veccy[1];
	colMatrix_[2]=veccy[2];
	colMatrix_[3]=veccy[3];

	colMatrix_[4]=veccy[4];
	colMatrix_[5]=veccy[5];
	colMatrix_[6]=veccy[6];
	colMatrix_[7]=veccy[7];

	colMatrix_[8]=veccy[8];
	colMatrix_[9]=veccy[9];
	colMatrix_[10]=veccy[10];
	colMatrix_[11]=veccy[11];

	colMatrix_[12]=veccy[12];
	colMatrix_[13]=veccy[13];
	colMatrix_[14]=veccy[14];
	colMatrix_[15]=veccy[15];
	setFlag_=true;
}

void Matrix::SetMatrix(const float veccy[])
{
	colMatrix_[0]=veccy[0];
	colMatrix_[1]=veccy[1];
	colMatrix_[2]=veccy[2];
	colMatrix_[3]=veccy[3];

	colMatrix_[4]=veccy[4];
	colMatrix_[5]=veccy[5];
	colMatrix_[6]=veccy[6];
	colMatrix_[7]=veccy[7];

	colMatrix_[8]=veccy[8];
	colMatrix_[9]=veccy[9];
	colMatrix_[10]=veccy[10];
	colMatrix_[11]=veccy[11];

	colMatrix_[12]=veccy[12];
	colMatrix_[13]=veccy[13];
	colMatrix_[14]=veccy[14];
	colMatrix_[15]=veccy[15];
	setFlag_=true;
}

bool Matrix::HasValue()
{
	return setFlag_;
}

const float* Matrix::GetMatrix()
{
	return colMatrix_;
}

void Matrix::PrintMatrix()
{}

bool Matrix::InvertMatrix()
{
	float det;
	float temp[16];
	temp[0] = colMatrix_[5]  * colMatrix_[10] * colMatrix_[15] - 
		colMatrix_[5]  * colMatrix_[11] * colMatrix_[14] - 
		colMatrix_[9]  * colMatrix_[6]  * colMatrix_[15] + 
		colMatrix_[9]  * colMatrix_[7]  * colMatrix_[14] +
		colMatrix_[13] * colMatrix_[6]  * colMatrix_[11] - 
		colMatrix_[13] * colMatrix_[7]  * colMatrix_[10];

	temp[4] = -colMatrix_[4]  * colMatrix_[10] * colMatrix_[15] + 
		colMatrix_[4]  * colMatrix_[11] * colMatrix_[14] + 
		colMatrix_[8]  * colMatrix_[6]  * colMatrix_[15] - 
		colMatrix_[8]  * colMatrix_[7]  * colMatrix_[14] - 
		colMatrix_[12] * colMatrix_[6]  * colMatrix_[11] + 
		colMatrix_[12] * colMatrix_[7]  * colMatrix_[10];

	temp[8] = colMatrix_[4]  * colMatrix_[9] * colMatrix_[15] - 
		colMatrix_[4]  * colMatrix_[11] * colMatrix_[13] - 
		colMatrix_[8]  * colMatrix_[5] * colMatrix_[15] + 
		colMatrix_[8]  * colMatrix_[7] * colMatrix_[13] + 
		colMatrix_[12] * colMatrix_[5] * colMatrix_[11] - 
		colMatrix_[12] * colMatrix_[7] * colMatrix_[9];

	temp[12] = -colMatrix_[4]  * colMatrix_[9] * colMatrix_[14] + 
		colMatrix_[4]  * colMatrix_[10] * colMatrix_[13] +
		colMatrix_[8]  * colMatrix_[5] * colMatrix_[14] - 
		colMatrix_[8]  * colMatrix_[6] * colMatrix_[13] - 
		colMatrix_[12] * colMatrix_[5] * colMatrix_[10] + 
		colMatrix_[12] * colMatrix_[6] * colMatrix_[9];

	temp[1] = -colMatrix_[1]  * colMatrix_[10] * colMatrix_[15] + 
		colMatrix_[1]  * colMatrix_[11] * colMatrix_[14] + 
		colMatrix_[9]  * colMatrix_[2] * colMatrix_[15] - 
		colMatrix_[9]  * colMatrix_[3] * colMatrix_[14] - 
		colMatrix_[13] * colMatrix_[2] * colMatrix_[11] + 
		colMatrix_[13] * colMatrix_[3] * colMatrix_[10];

	temp[5] = colMatrix_[0]  * colMatrix_[10] * colMatrix_[15] - 
		colMatrix_[0]  * colMatrix_[11] * colMatrix_[14] - 
		colMatrix_[8]  * colMatrix_[2] * colMatrix_[15] + 
		colMatrix_[8]  * colMatrix_[3] * colMatrix_[14] + 
		colMatrix_[12] * colMatrix_[2] * colMatrix_[11] - 
		colMatrix_[12] * colMatrix_[3] * colMatrix_[10];

	temp[9] = -colMatrix_[0]  * colMatrix_[9] * colMatrix_[15] + 
		colMatrix_[0]  * colMatrix_[11] * colMatrix_[13] + 
		colMatrix_[8]  * colMatrix_[1] * colMatrix_[15] - 
		colMatrix_[8]  * colMatrix_[3] * colMatrix_[13] - 
		colMatrix_[12] * colMatrix_[1] * colMatrix_[11] + 
		colMatrix_[12] * colMatrix_[3] * colMatrix_[9];

	temp[13] = colMatrix_[0]  * colMatrix_[9] * colMatrix_[14] - 
		colMatrix_[0]  * colMatrix_[10] * colMatrix_[13] - 
		colMatrix_[8]  * colMatrix_[1] * colMatrix_[14] + 
		colMatrix_[8]  * colMatrix_[2] * colMatrix_[13] + 
		colMatrix_[12] * colMatrix_[1] * colMatrix_[10] - 
		colMatrix_[12] * colMatrix_[2] * colMatrix_[9];

	temp[2] = colMatrix_[1]  * colMatrix_[6] * colMatrix_[15] - 
		colMatrix_[1]  * colMatrix_[7] * colMatrix_[14] - 
		colMatrix_[5]  * colMatrix_[2] * colMatrix_[15] + 
		colMatrix_[5]  * colMatrix_[3] * colMatrix_[14] + 
		colMatrix_[13] * colMatrix_[2] * colMatrix_[7] - 
		colMatrix_[13] * colMatrix_[3] * colMatrix_[6];

	temp[6] = -colMatrix_[0]  * colMatrix_[6] * colMatrix_[15] + 
		colMatrix_[0]  * colMatrix_[7] * colMatrix_[14] + 
		colMatrix_[4]  * colMatrix_[2] * colMatrix_[15] - 
		colMatrix_[4]  * colMatrix_[3] * colMatrix_[14] - 
		colMatrix_[12] * colMatrix_[2] * colMatrix_[7] + 
		colMatrix_[12] * colMatrix_[3] * colMatrix_[6];

	temp[10] = colMatrix_[0]  * colMatrix_[5] * colMatrix_[15] - 
		colMatrix_[0]  * colMatrix_[7] * colMatrix_[13] - 
		colMatrix_[4]  * colMatrix_[1] * colMatrix_[15] + 
		colMatrix_[4]  * colMatrix_[3] * colMatrix_[13] + 
		colMatrix_[12] * colMatrix_[1] * colMatrix_[7] - 
		colMatrix_[12] * colMatrix_[3] * colMatrix_[5];

	temp[14] = -colMatrix_[0]  * colMatrix_[5] * colMatrix_[14] + 
		colMatrix_[0]  * colMatrix_[6] * colMatrix_[13] + 
		colMatrix_[4]  * colMatrix_[1] * colMatrix_[14] - 
		colMatrix_[4]  * colMatrix_[2] * colMatrix_[13] - 
		colMatrix_[12] * colMatrix_[1] * colMatrix_[6] + 
		colMatrix_[12] * colMatrix_[2] * colMatrix_[5];

	temp[3] = -colMatrix_[1] * colMatrix_[6] * colMatrix_[11] + 
		colMatrix_[1] * colMatrix_[7] * colMatrix_[10] + 
		colMatrix_[5] * colMatrix_[2] * colMatrix_[11] - 
		colMatrix_[5] * colMatrix_[3] * colMatrix_[10] - 
		colMatrix_[9] * colMatrix_[2] * colMatrix_[7] + 
		colMatrix_[9] * colMatrix_[3] * colMatrix_[6];

	temp[7] = colMatrix_[0] * colMatrix_[6] * colMatrix_[11] - 
		colMatrix_[0] * colMatrix_[7] * colMatrix_[10] - 
		colMatrix_[4] * colMatrix_[2] * colMatrix_[11] + 
		colMatrix_[4] * colMatrix_[3] * colMatrix_[10] + 
		colMatrix_[8] * colMatrix_[2] * colMatrix_[7] - 
		colMatrix_[8] * colMatrix_[3] * colMatrix_[6];

	temp[11] = -colMatrix_[0] * colMatrix_[5] * colMatrix_[11] + 
		colMatrix_[0] * colMatrix_[7] * colMatrix_[9] + 
		colMatrix_[4] * colMatrix_[1] * colMatrix_[11] - 
		colMatrix_[4] * colMatrix_[3] * colMatrix_[9] - 
		colMatrix_[8] * colMatrix_[1] * colMatrix_[7] + 
		colMatrix_[8] * colMatrix_[3] * colMatrix_[5];

	temp[15] = colMatrix_[0] * colMatrix_[5] * colMatrix_[10] - 
		colMatrix_[0] * colMatrix_[6] * colMatrix_[9] - 
		colMatrix_[4] * colMatrix_[1] * colMatrix_[10] + 
		colMatrix_[4] * colMatrix_[2] * colMatrix_[9] + 
		colMatrix_[8] * colMatrix_[1] * colMatrix_[6] - 
		colMatrix_[8] * colMatrix_[2] * colMatrix_[5];

	det = colMatrix_[0] * temp[0] + colMatrix_[1] * temp[4] + colMatrix_[2] * temp[8] + colMatrix_[3] * temp[12];

	if (det == 0)
	{
		return false;
	}

	det = 1.0 / det;
	int i;
	for (i = 0; i < 16; i++)
		colMatrix_[i] = temp[i] * det;
	return true;
}
void Matrix::Multiply(const float veccy[])
{
	float temp[16];
	temp[0]=(colMatrix_[0]*veccy[0]+
		colMatrix_[1]*veccy[4]+
		colMatrix_[2]*veccy[8]+
		colMatrix_[3]*veccy[12]);

	temp[1]=(colMatrix_[0]*veccy[1]+
		colMatrix_[1]*veccy[5]+
		colMatrix_[2]*veccy[9]+
		colMatrix_[3]*veccy[13]);

	temp[2]=(colMatrix_[0]*veccy[2]+
		colMatrix_[1]*veccy[6]+
		colMatrix_[2]*veccy[10]+
		colMatrix_[3]*veccy[14]);

	temp[3]=(colMatrix_[0]*veccy[3]+
		colMatrix_[1]*veccy[7]+
		colMatrix_[2]*veccy[11]+
		colMatrix_[3]*veccy[15]);

	temp[4]=(colMatrix_[4]*veccy[0]+
		colMatrix_[5]*veccy[4]+
		colMatrix_[6]*veccy[8]+
		colMatrix_[7]*veccy[12]);

	temp[5]=(colMatrix_[4]*veccy[1]+
		colMatrix_[5]*veccy[5]+
		colMatrix_[6]*veccy[9]+
		colMatrix_[7]*veccy[13]);

	temp[6]=(colMatrix_[4]*veccy[2]+
		colMatrix_[5]*veccy[6]+
		colMatrix_[6]*veccy[10]+
		colMatrix_[7]*veccy[14]);

	temp[7]=(colMatrix_[4]*veccy[3]+
		colMatrix_[5]*veccy[7]+
		colMatrix_[6]*veccy[11]+
		colMatrix_[7]*veccy[15]);

	temp[8]=(colMatrix_[8]*veccy[0]+
		colMatrix_[9]*veccy[4]+
		colMatrix_[10]*veccy[8]+
		colMatrix_[11]*veccy[12]);

	temp[9]=(colMatrix_[8]*veccy[1]+
		colMatrix_[9]*veccy[5]+
		colMatrix_[10]*veccy[9]+
		colMatrix_[11]*veccy[13]);

	temp[10]=(colMatrix_[8]*veccy[2]+
		colMatrix_[9]*veccy[6]+
		colMatrix_[10]*veccy[10]+
		colMatrix_[11]*veccy[14]);

	temp[11]=(colMatrix_[8]*veccy[3]+
		colMatrix_[9]*veccy[7]+
		colMatrix_[10]*veccy[11]+
		colMatrix_[11]*veccy[15]);

	temp[12]=(colMatrix_[12]*veccy[0]+
		colMatrix_[13]*veccy[4]+
		colMatrix_[14]*veccy[8]+
		colMatrix_[15]*veccy[12]);

	temp[13]=(colMatrix_[12]*veccy[1]+
		colMatrix_[13]*veccy[5]+
		colMatrix_[14]*veccy[9]+
		colMatrix_[15]*veccy[13]);

	temp[14]=(colMatrix_[12]*veccy[2]+
		colMatrix_[13]*veccy[6]+
		colMatrix_[14]*veccy[10]+
		colMatrix_[15]*veccy[14]);

	temp[15]=(colMatrix_[12]*veccy[3]+
		colMatrix_[13]*veccy[7]+
		colMatrix_[14]*veccy[11]+
		colMatrix_[15]*veccy[15]);
	SetMatrix(temp);
}

void Matrix::Multiply(Vec3f& vec)
{
	Vec3f temp;
	temp.x=(vec.x*colMatrix_[0]+
		vec.y*colMatrix_[4]+
		vec.z*colMatrix_[8]+
		1*colMatrix_[12]);

	temp.y=(vec.x*colMatrix_[1]+
		vec.y*colMatrix_[5]+
		vec.z*colMatrix_[9]+
		1*colMatrix_[13]);

	temp.z=(vec.x*colMatrix_[2]+
		vec.y*colMatrix_[6]+
		vec.z*colMatrix_[10]+
		1*colMatrix_[14]);
	vec=temp;
}

void Matrix::Multiply(Vec4f& vec)
{
	Vec4f temp;
	temp.x=(vec.x*colMatrix_[0]+
		vec.y*colMatrix_[4]+
		vec.z*colMatrix_[8]+
		vec.w*colMatrix_[12]);

	temp.y=(vec.x*colMatrix_[1]+
		vec.y*colMatrix_[5]+
		vec.z*colMatrix_[9]+
		vec.w*colMatrix_[13]);

	temp.z=(vec.x*colMatrix_[2]+
		vec.y*colMatrix_[6]+
		vec.z*colMatrix_[10]+
		vec.w*colMatrix_[14]);

	temp.w=(vec.x*colMatrix_[3]+
		vec.y*colMatrix_[7]+
		vec.z*colMatrix_[11]+
		vec.w*colMatrix_[15]);
	vec=temp;
}

bool Matrix::GetModelMatrix()
{
	glGetFloatv(GL_MODELVIEW_MATRIX,
		colMatrix_);
	setFlag_=true;
	return true;
}

bool Matrix::GetProjectionMatrix()
{
	glGetFloatv(GL_PROJECTION_MATRIX,
		colMatrix_);
	setFlag_=true;
	return true;
}

void Matrix::Translate(const Vec3f& ref)
{
	colMatrix_[12]=ref.x;
	colMatrix_[13]=ref.y;
	colMatrix_[14]=ref.z;
	colMatrix_[15]=1.0f;
}
void Matrix::RotateX(float rads)
{
	colMatrix_[0] = 1.0f;
    colMatrix_[5] = cos(rads);
    colMatrix_[6] = sin(rads);
    colMatrix_[9] = -sin(rads);
    colMatrix_[10] = cos(rads);
    colMatrix_[15] = 1.0f;
}
void Matrix::RotateY(float rads)
{
	colMatrix_[0] = cos(rads);
    colMatrix_[2] = -sin(rads);
    colMatrix_[5] = 1.0f;
    colMatrix_[8] = sin(rads);
    colMatrix_[10] = cos(rads);
    colMatrix_[15] = 1.0f;
}
void Matrix::RotateZ(float rads)
{
	colMatrix_[0] = cos(rads);
    colMatrix_[1] = sin(rads);
    colMatrix_[4] = -sin(rads);
    colMatrix_[5] = cos(rads);
    colMatrix_[10] = 1.0f;
    colMatrix_[15] = 1.0f;
}
void Matrix::Scale(const Vec3f& ref)
{
	colMatrix_[0]=ref.x;
	colMatrix_[5]=ref.y;
	colMatrix_[10]=ref.z;
	colMatrix_[15]=1.0f;
}