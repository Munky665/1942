#include "Vector3.h"


//defult constructor
Vector3::Vector3() 
{

}

Vector3::~Vector3()
{

}

Vector3::Vector3(const Vector3 &V3)
{
	x = V3.x;
	y = V3.y;
	z = V3.z;
}

Vector3::Vector3(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}

Vector3::operator float*()
{
	return &x;
}

Vector3::operator const float* () const
{
	return &x;
}

float&  Vector3::operator[](int index)
{ 
	return data[index]; 
}
float Vector3::operator[](int index)const 
{
	return data[index];
}
 //maths operators
//addition operator
Vector3 Vector3::operator + (const Vector3& other) const
{
	return{
		x + other.x,
		y + other.y,
		z + other.z
	};
}
//minus operator
Vector3 Vector3::operator - (const Vector3& other) const
{
	return{
		x - other.x,
		y - other.y,
		z - other.z
	};
}
//multiplication operator
Vector3 Vector3::operator * (const Vector3& other) const
{
	return{
		x * other.x,
		y * other.y,
		z * other.z
	};
}
Vector3 operator*(float s, Vector3 & v)
{
	v.x = s * v.x;
	v.y = s * v.y;
	v.z = s * v.z;
	return v;
}
//division operator
Vector3 Vector3::operator / (const Vector3& other) const
{
	return{
		x / other.x,
		y / other.y,
		z / other.z
	};
}

Vector3& Vector3::operator -= (const Vector3& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

Vector3& Vector3::operator += (const Vector3& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

Vector3& Vector3::operator *= (const Vector3& other)
{
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

Vector3& Vector3::operator /= (const Vector3& other)
{
	x /= other.x;
	y /= other.y;
	z /= other.z;
	return *this;
}

Vector3 Vector3::operator - (float scalar) const
{
	return{
		x - scalar,
		y - scalar,
		z - scalar
	};
}

Vector3 Vector3::operator + (float scalar) const
{
	return{
		x + scalar,
		y + scalar,
		z + scalar
	};
}

Vector3 Vector3::operator * (float scalar) const
{
	return{
		x * scalar,
		y * scalar,
		z * scalar
	};
}

Vector3 Vector3::operator / (float scalar) const
{
	return{
		x / scalar,
		y / scalar,
		z / scalar
	};
}


Vector3& Vector3::operator += (float scalar)
{
	x += scalar;
	y += scalar;
	z += scalar;
	return *this;
}

Vector3& Vector3::operator -= (float scalar)
{
	x -= scalar;
	y -= scalar;
	z -= scalar;
	return *this;
}

Vector3& Vector3::operator *= (float scalar)
{
	x *= scalar;
	y *= scalar;
	z *= scalar;
	return *this;
}

Vector3& Vector3::operator /= (float scalar)
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

Vector3& Vector3::operator = (const Vector3& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	return *this;
}

//returns magnatude
float Vector3::magnitude() const
{
	return sqrt(x*x + y * y + z * z);
}
//returns squared magnatude 
float Vector3::magnitudeSqr() const
{
	return (x*x + y * y + z * z);
}
//returns non member magnatude
float Vector3::magnitude(const Vector3& v)
{
	return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
//checks distance between member other
float Vector3::distance(const Vector3& other) const
{
	float diffX = x - other.x;
	float diffY = y - other.y;
	float diffZ = z - other.z;
	return sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ);
}
//checks distance between non-member Vector3's
float Vector3::distance(const Vector3& a, const Vector3& b)
{
	float diffX = a.x - b.x;
	float diffY = a.y - b.y;
	float diffZ = a.z - b.z;
	return sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ);
}
//normalise vector. make unit value
void Vector3::normalise()
{
	float mag = magnitude();
	x /= mag;
	y /= mag;
	z /= mag;
}
//return a normalised version of vector
Vector3 Vector3::normalised() const
{
	float mag = magnitude();
	return
	{
		x / mag,
		y / mag,
		z / mag
	};
}
//global method that returns normalised copy of vector
Vector3 Vector3::normalise(const Vector3& v)
{
	float mag = v.magnitude();
	return
	{
		v.x / mag,
		v.y / mag,
		v.z / mag
	};
}
//created Dot Product from two vectors
float Vector3::dot(const Vector3& other) const
{
	return x * other.x + y * other.y + z * other.z;
}
//creates non-member dot product.
float Vector3::dot(const Vector3& a, const Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
//creates cross product (perpandicular vectors)
Vector3 Vector3::cross(const Vector3& other) const
{
	return
	{
		y * other.z - z * other.y,
		z * other.x - x * other.z,
		x * other.y - y * other.x
	};
}
//non-member cross product
Vector3 Vector3::cross(const Vector3& a, const Vector3& b)
{
	return
	{
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	};		  
}

//return angle between two Vectors
float Vector3::angleBetween(const Vector3& other)const
{
	//normalise vectors
	Vector3 a = normalised();
	Vector3 b = other.normalised();

	//calculate the dot product
	float d = a.x * b.x + a.y * b.y + a.z * b.z;

	//return angle between them
	return acos(d);
}
//non-member angle finder
float Vector3::angleBetween(const Vector3& a, const Vector3& b)
{
	//normalise and calculate the do product
	float d = dot(normalise(a), normalise(b));
	return acos(d);
}