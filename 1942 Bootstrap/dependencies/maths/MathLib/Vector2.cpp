#include "Vector2.h"

//defult constructor
Vector2::Vector2()
{

}

Vector2::~Vector2()
{

}

Vector2::Vector2(const Vector2 &V2)
{
	x = V2.x;
	y = V2.y;
}

Vector2::Vector2(float X, float Y)
{
	x = X;
	y = Y;
}

Vector2::operator float*()
{
	return &x;
}

Vector2::operator const float* () const
{
	return &x;
}

float&  Vector2::operator[](int index)
{
	return data[index];
}
float Vector2::operator[](int index)const
{
	return data[index];
}
//maths operators
//addition operator
Vector2 Vector2::operator + (const Vector2& other) const
{
	return{
		x + other.x,
		y + other.y
	};
}
//minus operator
Vector2 Vector2::operator - (const Vector2& other) const
{
	return{
		x - other.x,
		y - other.y
	};
}
//multiplication operator
Vector2 Vector2::operator * (const Vector2& other) const
{
	return{
		x * other.x,
		y * other.y
	};
}
//division operator
Vector2 Vector2::operator / (const Vector2& other) const
{
	return{
		x / other.x,
		y / other.y
	};
}

Vector2& Vector2::operator -= (const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2& Vector2::operator += (const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2& Vector2::operator *= (const Vector2& other)
{
	x *= other.x;
	y *= other.y;
	return *this;
}

Vector2& Vector2::operator /= (const Vector2& other)
{
	x /= other.x;
	y /= other.y;
	return *this;
}

Vector2 Vector2::operator - (float scalar) const
{
	return{
		x - scalar,
		y - scalar,
	};
}

Vector2 Vector2::operator + (float scalar) const
{
	return{
		x + scalar,
		y + scalar
	};
}

Vector2 Vector2::operator * (float scalar) const
{
	return{
		x * scalar,
		y * scalar
	};
}
Vector2 operator*(float s, Vector2& v)
{
	v.x = s * v.x;
	v.y = s * v.y;
	return v;
}

Vector2 Vector2::operator / (float scalar) const
{
	return{
		x / scalar,
		y / scalar
	};
}

Vector2& Vector2::operator += (float scalar)
{
	x += scalar;
	y += scalar;
	return *this;
}

Vector2& Vector2::operator -= (float scalar)
{
	x -= scalar;
	y -= scalar;
	return *this;
}

Vector2& Vector2::operator *= (float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2& Vector2::operator /= (float scalar)
{
	x /= scalar;
	y /= scalar;
	return *this;
}

Vector2& Vector2::operator = (const Vector2& other)
{
	x = other.x;
	y = other.y;
	return *this;
}

//returns magnatude
float Vector2::magnitude() const
{
	return sqrt(x*x + y * y);
}
//returns squared magnatude 
float Vector2::magnitudeSqr() const
{
	return (x*x + y * y);
}
//returns non member magnatude
float Vector2::magnitude(const Vector2& v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}
//checks distance between member other
float Vector2::distance(const Vector2& other) const
{
	float diffX = x - other.x;
	float diffY = y - other.y;
	return sqrt(diffX * diffX + diffY * diffY);
}
//checks distance between non-member Vector3's
float Vector2::distance(const Vector2& a, const Vector2& b)
{
	float diffX = a.x - b.x;
	float diffY = a.y - b.y;
	return sqrt(diffX * diffX + diffY * diffY);
}
//normalise vector. make unit value
void Vector2::normalise()
{
	float mag = magnitude();
	x /= mag;
	y /= mag;

}
//return a normalised version of vector
Vector2 Vector2::normalised() const
{
	float mag = magnitude();
	return
	{
		x / mag,
		y / mag
	};
}
//global method that returns normalised copy of vector
Vector2 Vector2::normalise(const Vector2& v)
{
	float mag = v.magnitude();
	return
	{
		v.x / mag,
		v.y / mag
	};
}
//created Dot Product from two vectors
float Vector2::dot(const Vector2& other) const
{
	return (x * other.x) + (y * other.y);
}
//creates non-member dot product.
float Vector2::dot(const Vector2& a, const Vector2& b)
{
	return (a.x * b.x) + (a.y * b.y);
}

//get right hand perpendicular vector
Vector2 Vector2::getPerpendicularRH() const
{
	return { -y, x };
}
//get left hand perpendicular vector
Vector2 Vector2::getPerpendicularLH()const
{
	return{ y, -x };
}

//return angle between two Vectors
float Vector2::angleBetween(const Vector2& other)const
{
	//normalise vectors
	Vector2 a = normalised();
	Vector2 b = other.normalised();

	//calculate the dot product
	float d = a.x * b.x + a.y * b.y;

	//return angle between them
	return acos(d);
}
//non-member angle finder
float Vector2::angleBetween(const Vector2& a, const Vector2& b)
{
	//normalise and calculate the do product
	float d = dot(normalise(a), normalise(b));
	return acos(d);
}

