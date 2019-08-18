#pragma once
#include <math.h>

class Vector2
{
public:
	union {
		struct
		{
			float x, y;
		};
		float data[2];
	};

	Vector2();
	Vector2(const Vector2 &V2);
	Vector2(float X, float Y);
	~Vector2();
	float&  operator [](int index);
	float operator [](int index)const;

	//maths operators
	Vector2 operator + (const Vector2& other) const;
	Vector2 operator - (const Vector2& other) const;
	Vector2 operator * (const Vector2& other) const;
	Vector2 operator / (const Vector2& other) const;

	Vector2& operator -= (const Vector2& other);
	Vector2& operator += (const Vector2& other);
	Vector2& operator *= (const Vector2& other);
	Vector2& operator /= (const Vector2& other);

	//scalar operators
	Vector2 operator - (float scalar) const;
	Vector2 operator + (float scalar) const;
	Vector2 operator * (float scalar) const;
    friend Vector2 operator * (float s, Vector2& v);
	Vector2 operator / (float scalar) const;
	Vector2& operator += (float scalar);
	Vector2& operator -= (float scalar);
	Vector2& operator *= (float scalar);
	Vector2& operator /= (float scalar);

	Vector2& operator = (const Vector2& other);

	operator float*();
	operator const float* () const;
	//member functions
	float	magnitude		()const;
	float	magnitudeSqr	()const;
	float	distance		(const Vector2& other) const;
	void	normalise		();
	Vector2 normalise		(const Vector2& v);
	Vector2 normalised		() const;
	float	dot				(const Vector2& other) const;
	float	angleBetween	(const Vector2& other)const;
	Vector2 getPerpendicularRH() const;
	Vector2 getPerpendicularLH() const;
	//non member functions
	float	magnitude		(const Vector2& v);
	float	distance		(const Vector2& a, const Vector2& b);
	float	dot				(const Vector2& a, const Vector2& b);
	float	angleBetween	(const Vector2& a, const Vector2& b);
};

