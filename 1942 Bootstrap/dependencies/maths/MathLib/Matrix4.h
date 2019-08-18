#pragma once
#include "Vector4.h"
#include <math.h>
class Matrix4
{
public:
	union
	{
		struct {
			Vector4 xAxis;
			Vector4 yAxis;
			Vector4 zAxis;
			Vector4 translation;
		};
		Vector4 axis[4];
		float data[4][4];
	};

	static const Matrix4 identity;

	Matrix4();
	Matrix4(const Matrix4 &mat3);
	Matrix4(float xx, float xy, float xz, float xt, float yx, float yy, float yz, float yt,
			float zx, float zy, float zz, float zt, float tx, float ty, float tz, float tt);
	~Matrix4();
	operator float*();
	operator const float* () const;
	Vector4& operator[](int index);
	const Vector4& operator[](int index)const;
	Matrix4 operator * (const Matrix4& other) const;
	Matrix4 operator + (const Matrix4& other) const;
	Matrix4 operator - (const Matrix4& other) const;
	Matrix4& operator = (const Matrix4& other);
	Vector4 operator * (const Vector4& v) const;
	Matrix4 transposed() const;
	Matrix4 setScaled(float x, float y, float z);
	Matrix4 setScaled(const Vector4& v);
	void scale(float x, float y, float z);
	void scale(const Vector4& v);
	void setRotateX(float radias);
	void setRotateY(float radias);
	void setRotateZ(float radias);
	void rotateX(float radians);
	void rotateY(float radians);
	void rotateZ(float radians);
	void setEuler(float pitch, float yaw, float roll);
	void translate(float x, float y, float z);
};

