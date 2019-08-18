#pragma once

class Vector4
{
public:
	union {
		struct
		{
			float x, y, z, w;
		};
		float data[4];
	};
	Vector4();
	Vector4(const Vector4 &v4);
	Vector4(float x, float y,float z,float w);
	~Vector4();
	float& operator [](int index);
	float operator [](int index)const;

	//maths operators
	Vector4 operator + (const Vector4& other) const;
	Vector4 operator - (const Vector4& other) const;
	Vector4 operator * (const Vector4& other) const;
	Vector4 operator / (const Vector4& other) const;

	Vector4& operator -= (const Vector4& other);
	Vector4& operator += (const Vector4& other);
	Vector4& operator *= (const Vector4& other);
	Vector4& operator /= (const Vector4& other);

	//scalar operators
	Vector4 operator - (float scalar) const;
	Vector4 operator + (float scalar) const;
	Vector4 operator * (float scalar) const;
	friend Vector4 operator * (float s, Vector4& v);
	Vector4 operator / (float scalar) const;

	Vector4& operator += (float scalar);
	Vector4& operator -= (float scalar);
	Vector4& operator *= (float scalar);
	Vector4& operator /= (float scalar);

	Vector4& operator = (const Vector4& other);

	//member functions
	float	magnitude()const;
	float	magnitudeSqr()const;
	float	distance(const Vector4& other) const;
	void	normalise();
	Vector4 normalise(const Vector4& v);
	Vector4 normalised() const;
	Vector4	cross(const Vector4& other) const;
	float	dot(const Vector4& other) const;
	float	angleBetween(const Vector4& other)const;
	operator float*			();
	operator const float*	() const;
	//non member functions
	float	magnitude(const Vector4& v);
	float	distance(const Vector4& a, const Vector4& b);
	float	dot(const Vector4& a, const Vector4& b);
	float	angleBetween(const Vector4& a, const Vector4& b);
	Vector4 cross(const Vector4& a, const Vector4& b);
};

