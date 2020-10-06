#ifndef _3DMATH_H_
#define _3DMATH_H_


#include "ase2dar.h"


//#define PI       3.1415926535898f


class Vector2
{
public:

	GLfloat x;
	GLfloat y;

	Vector2() {};
	Vector2(float *);
	Vector2(float, float);

	operator float* ();
	operator const float* () const;

	float &operator [] (unsigned int);
	const float &operator [] (unsigned int) const;


	Vector2& operator += (Vector2&);
	Vector2& operator -= (Vector2&);

	Vector2& operator *= (Vector2&);
	Vector2& operator /= (Vector2&);

	Vector2& operator *= (float);
	Vector2& operator /= (float);


	Vector2 operator + (Vector2&);
	Vector2 operator - (Vector2&);

	Vector2 operator * (Vector2&);
	Vector2 operator / (Vector2&);
		
	Vector2 operator * (float);
	Vector2 operator / (float);


	bool operator == (Vector2&);
	bool operator != (Vector2&);
};


class Vector3
{
public:

	GLfloat x;
	GLfloat y;
	GLfloat z;

	Vector3() {};
	Vector3(float *);
	Vector3(float, float, float);

	operator float* ();
	operator const float* () const;

	float &operator [] (unsigned int);
	const float &operator [] (unsigned int) const;


	Vector3& operator += (Vector3&);
	Vector3& operator -= (Vector3&);

	Vector3& operator *= (Vector3&);
	Vector3& operator /= (Vector3&);
	
	Vector3& operator *= (float);
	Vector3& operator /= (float);

	
	Vector3 operator + (Vector3&);
	Vector3 operator - (Vector3&);

	Vector3 operator * (Vector3&);
	Vector3 operator / (Vector3&);
	
	Vector3 operator * (float);
	Vector3 operator / (float);


	bool operator == (Vector3&);
	bool operator != (Vector3&);
};


class Vector4
{
public:

	GLfloat x;
	GLfloat y;
	GLfloat z;
	GLfloat t;

	Vector4() {};
	Vector4(float *);
	Vector4(float, float, float, float);

	operator float* ();
	operator const float* () const;

	float &operator [] (unsigned int);
	const float &operator [] (unsigned int) const;


	Vector4& operator += (Vector4&);
	Vector4& operator -= (Vector4&);

	Vector4& operator *= (Vector4&);
	Vector4& operator /= (Vector4&);
	
	Vector4& operator *= (float);
	Vector4& operator /= (float);


	Vector4 operator + (Vector4&);
	Vector4 operator - (Vector4&);

	Vector4 operator * (Vector4&);
	Vector4 operator / (Vector4&);
	
	Vector4 operator * (float);
	Vector4 operator / (float);


	bool operator == (Vector4&);
	bool operator != (Vector4&);
};


typedef struct
{
	Vector3 Vertex[3];
}VertexNormal;


typedef struct
{
	unsigned int Num[3];
}UInt3;


#endif