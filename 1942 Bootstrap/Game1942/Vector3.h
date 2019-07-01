#pragma once

#include <math.h>

class vector3 {
public:
	union {
		struct {
			float x, y, z;
		};
		float data[3];
	};

	vector3(float vx, float vy, float vz);
	float operator[](int index)const;
	vector3 operator+(const vector3& other) const;
	vector3& operator -= (vector3& other);
	vector3 operator * (float scalar) const;
	vector3& operator /= (float scalar);
	vector3 operator = (const vector3& other);
	vector3& operator += (const vector3& other);
	vector3& operator *= (const vector3& other);
	vector3 operator-(const vector3& other)const;
	float Angle(vector3& other);
	//cast
	operator float*();
	operator const float*()const;
	float magnitued()const;
	float magnituedSqr() const;
	float distance(const vector3& other) const;
	vector3 normalise(const vector3& v);
	vector3& operator += (float scalar);
	vector3& operator -= (float scalar);
};