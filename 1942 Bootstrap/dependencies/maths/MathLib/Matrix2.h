#pragma once
#include "Vector2.h"
class Matrix2
{
public:
	union
	{
		struct {
			Vector2 xAxis;
			Vector2 yAxis;
		};
		Vector2 axis[2];
		float data[2][2];
	};

	static const Matrix2 identity;

	Matrix2();
	Matrix2(const Matrix2 &mat2);
	Matrix2(float xx, float xy, float yx, float yy);
	~Matrix2();
	operator float*();
	operator const float* () const;
	Vector2& operator[](int index);
	const Vector2& operator[](int index)const;
	Matrix2 operator * (const Matrix2& other) const;
	Matrix2 operator + (const Matrix2& other) const;
	Matrix2 operator - (const Matrix2& other) const;
	Vector2 operator * (const Vector2& v) const;
	Matrix2& operator = (const Matrix2& other) const;
	Matrix2 transposed() const;
	Matrix2 setScaled(float x, float y);
	Matrix2 setScaled(const Vector2& v);
	void scale(float x, float y);
	void scale(const Vector2& v);
	void setRotate(float radians);
	void rotate(float radians);
};

