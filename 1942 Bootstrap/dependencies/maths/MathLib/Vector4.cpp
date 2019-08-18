#include "Vector4.h"
#include <math.h>


Vector4::Vector4()
{
}

Vector4::Vector4(float X, float Y, float Z, float W) 
{
	x = X;
	y = Y;
	z = Z;
	w = W;
}

Vector4::Vector4(const Vector4 &v4)
{
	x = v4.x;
	y = v4.y;
	z = v4.z;
	w = v4.w;
}

Vector4::~Vector4()
{
}

Vector4::operator float*()
{
	return &x;
}

Vector4::operator const float* () const
{
	return &x;
}

float&  Vector4::operator[](int index)
{
	return data[index];
}
float Vector4::operator[](int index)const
{
	return data[index];
}
//maths operators
//addition operator
Vector4 Vector4::operator + (const Vector4& other) const
{
	return{
		x + other.x,
		y + other.y,
		z + other.z,
		w + other.w
	};
}
//minus operator
Vector4 Vector4::operator - (const Vector4& other) const
{
	return{
		x - other.x,
		y - other.y,
		z - other.z,
		w - other.w
	};
}
//multiplication operator
Vector4 Vector4::operator * (const Vector4& other) const
{
	return{
		x * other.x,
		y * other.y,
		z * other.z,
		w * other.w
	};
}
Vector4 operator*(float s, Vector4& v)
{
	v.x = s * v.x;
	v.y = s * v.y;
	v.z = s * v.z;
	v.w = s * v.w;
	return v;
}
//division operator
Vector4 Vector4::operator / (const Vector4& other) const
{
	return{
		x / other.x,
		y / other.y,
		z / other.z,
		w / other.w
	};
}

Vector4& Vector4::operator -= (const Vector4& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	w -= other.w;
	return *this;
}

Vector4& Vector4::operator += (const Vector4& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	w += other.w;
	return *this;
}

Vector4& Vector4::operator *= (const Vector4& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	w *= other.w;
	return *this;
}

Vector4& Vector4::operator /= (const Vector4& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	z /= other.w;
	return *this;
}

Vector4 Vector4::operator - (float scalar) const
{
	return{
		x - scalar,
		y - scalar,
		z - scalar,
		w - scalar
	};
}

Vector4 Vector4::operator + (float scalar) const
{
	return{
		x + scalar,
		y + scalar,
		z + scalar,
		w + scalar
	};
}

Vector4 Vector4::operator * (float scalar) const
{
	return{
		x * scalar,
		y * scalar,
		z * scalar,
		w * scalar,
	};
}

Vector4 Vector4::operator / (float scalar) const
{
	return{
		x / scalar,
		y / scalar,
		z / scalar,
		w / scalar
	};
}


Vector4& Vector4::operator += (float scalar)
{
	x += scalar;
	y += scalar;
	z += scalar;
	w += scalar;
	return *this;
}

Vector4& Vector4::operator -= (float scalar)
{
	x -= scalar;
	y -= scalar;
	z -= scalar;
	w -= scalar;
	return *this;
}

Vector4& Vector4::operator *= (float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	w *= scalar;
	return *this;
}

Vector4& Vector4::operator /= (float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	w /= scalar;
	return *this;
}

Vector4& Vector4::operator = (const Vector4& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
	return *this;
}
//returns magnatude
float Vector4::magnitude() const
{
	return sqrt(x*x + y * y + z * z + w * w);
}
//returns squared magnatude 
float Vector4::magnitudeSqr() const
{
	return (x*x + y * y + z * z);
}
//returns non member magnatude
float Vector4::magnitude(const Vector4& v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z + v.w * v.w);
}
//checks distance between member other
float Vector4::distance(const Vector4& other) const
{
	float diffX = x - other.x;
	float diffY = y - other.y;
	float diffZ = z - other.z;
	float diffW = w - other.w;
	return sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ + diffW * diffW);
}
//checks distance between non-member Vector3's
float Vector4::distance(const Vector4& a, const Vector4& b)
{
	float diffX = a.x - b.x;
	float diffY = a.y - b.y;
	float diffZ = a.z - b.z;
	float diffW = a.w - b.w;
	return sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ + diffW * diffW);
}
//normalise vector. make unit value
void Vector4::normalise()
{
	float mag = magnitude();
	x /= mag;
	y /= mag;
	z /= mag;
	w /= mag;
}
//return a normalised version of vector
Vector4 Vector4::normalised() const
{
	float mag = magnitude();
	return
	{
		x / mag,
		y / mag,
		z / mag,
		w / mag
	};
}
//global method that returns normalised copy of vector
Vector4 Vector4::normalise(const Vector4& v)
{
	float mag = v.magnitude();
	return
	{
		v.x / mag,
		v.y / mag,
		v.z / mag,
		v.w / mag
	};
}
//created Dot Product from two vectors
float Vector4::dot(const Vector4& other) const
{
	return x * other.x + y * other.y + z * other.z + w * other.w;
}
//creates non-member dot product.
float Vector4::dot(const Vector4& a, const Vector4& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

//creates cross product (perpandicular vectors)
Vector4 Vector4::cross(const Vector4& other) const
{
	return
	{
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x,
		w * other.w
	};
}
//non-member cross product
Vector4 Vector4::cross(const Vector4& a, const Vector4& b)
{
	return
	{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
		a.w * b.w
	};
}
//return angle between two Vectors
float Vector4::angleBetween(const Vector4& other)const
{
	//normalise vectors
	Vector4 a = normalised();
	Vector4 b = other.normalised();

	//calculate the dot product
	float d = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;

	//return angle between them
	return acos(d);
}
//non-member angle finder
float Vector4::angleBetween(const Vector4& a, const Vector4& b)
{
	//normalise and calculate the do product
	float d = dot(normalise(a), normalise(b));
	return acos(d);
}