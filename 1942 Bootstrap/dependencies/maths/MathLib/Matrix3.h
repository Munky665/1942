#pragma once
#include "Vector3.h"
class Matrix3
{
public:
	union
	{
		struct {
			Vector3 xAxis;
			Vector3 yAxis;
			union 
			{
				Vector3 zAxis;
			};
		};
		Vector3 axis[3];
		float data[3][3];
	};

	static const Matrix3 identity;

	Matrix3();
	Matrix3(const Matrix3 &mat3);
	Matrix3(float xx, float xy, float xz, float yx, float yy, float yz, float zx, float zy, float zz);
	~Matrix3();
	operator float*();
	operator const float* () const;
	Vector3& operator[](int index);
	const Vector3& operator[](int index)const;
	Matrix3 operator * (const Matrix3& other) const;
	Matrix3 operator + (const Matrix3& other) const;
	Matrix3 operator - (const Matrix3& other) const;
	Matrix3& operator = (const Matrix3& other);
	Matrix3 operator*=(const Matrix3 & other) const;
	Vector3 operator * (const Vector3& v) const;
	Matrix3 transposed() const;
	Matrix3 setScaled(float x, float y, float z);
	Matrix3 setScaled(const Vector3& v);
	void scale(float x, float y, float z);
	void scale(const Vector3& v);
	void setRotateX(float radias);
	Matrix3& setRotateY(float radias);
	Matrix3& setRotateZ(float radias);
	void rotateX(float radians);
	void rotateY(float radians);
	void rotateZ(float radians);
	void setEuler(float pitch, float yaw, float roll);
	Matrix3& translate(float x, float y);
};

