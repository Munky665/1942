#pragma once

#include <math.h>

class vector2 {
public:
	union {
		struct {
			float x, y;
		};
		float data[3];
	};
	vector2();
	vector2(float vx, float vy);
	float operator[](int index)const;
	vector2 operator+(const vector2& other) const;
	vector2& operator -= (vector2& other);
	vector2 operator * (float scalar) const;
	vector2& operator /= (float scalar);
	vector2 operator = (const vector2& other);
	vector2& operator += (const vector2& other);
	vector2& operator *= (const vector2& other);
	vector2 operator-(const vector2& other)const;
	float Angle(vector2& other);
	//cast
	operator float*();
	operator const float*()const;
	float magnitued()const;
	float magnituedSqr() const;
	float distance(const vector2& other) const;
	vector2 normalise(const vector2& v);
	vector2& operator += (float scalar);
	vector2& operator -= (float scalar);
};