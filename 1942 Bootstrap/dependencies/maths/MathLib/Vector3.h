#pragma once
#include <math.h>

class Vector3 {
public:
	union {
		struct
		{
			float x, y;
			union 
			{
				float z;
			};
		};
		float data[3];
	};

	Vector3();
	Vector3(const Vector3 &V3);
	Vector3(float X, float Y, float Z);
	~Vector3();

	float&  operator [](int index);
	float operator [](int index)const;
	
	//maths operators
	Vector3 operator + (const Vector3& other) const;
	Vector3 operator - (const Vector3& other) const;
	Vector3 operator * (const Vector3& other) const;
	Vector3 operator / (const Vector3& other) const;

	Vector3& operator -= (const Vector3& other);
	Vector3& operator += (const Vector3& other);
	Vector3& operator *= (const Vector3& other);
	Vector3& operator /= (const Vector3& other);

	//scalar operators
	Vector3 operator - (float scalar) const;
	Vector3 operator + (float scalar) const;
	Vector3 operator * (float scalar) const;
	friend Vector3 operator * (float s, Vector3& v);
	Vector3 operator / (float scalar) const;

	Vector3& operator += (float scalar);
	Vector3& operator -= (float scalar);
	Vector3& operator *= (float scalar);
	Vector3& operator /= (float scalar);

	Vector3& operator = (const Vector3& other);
	//member functions
	float	magnitude		()const;
	float	magnitudeSqr	()const;
	float	distance		(const Vector3& other) const;
	void	normalise		();
	Vector3 normalise		(const Vector3& v);
	Vector3 normalised		() const;
	float	dot				(const Vector3& other) const;
	Vector3	cross			(const Vector3& other) const;
	float	angleBetween	(const Vector3& other)const;
	operator float*			();
	operator const float*	() const;
	//non member functions
	float	magnitude	(const Vector3& v);
	float	distance	(const Vector3& a, const Vector3& b);
	float	dot			(const Vector3& a, const Vector3& b);
	Vector3 cross		(const Vector3& a, const Vector3& b);
	float	angleBetween(const Vector3& a, const Vector3& b);
};
