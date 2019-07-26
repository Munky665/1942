#include "Vector2.h"


vector2::vector2()
{
}

vector2::vector2(float vx, float vy) {
	x = vx;
	y = vy;
}
float vector2::operator[](int index)const {
	return data[index];
}

vector2 vector2::operator+(const vector2& other) const {
	return{ x + other.x,
			y + other.y};
}

vector2 vector2::operator-(const vector2& other) const {
	return{ x - other.x,
			y - other.y};
}

vector2 vector2::operator = (const vector2& other) {
	return{ x = other.x,
			y = other.y};
}


vector2 vector2::operator * (float scalar) const {
	return { x * scalar,
			 y * scalar};
}

vector2& vector2::operator += (float scalar) {
	x += scalar;
	y += scalar;
	return *this;
}
vector2& vector2::operator -= (float scalar) {
	x -= scalar;
	y -= scalar;
	return *this;
}

vector2& vector2::operator -= (vector2& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

vector2& vector2::operator += (const vector2& other) {
	x += other.x;
	y += other.y;
	return *this;
}
vector2& vector2::operator *= (const vector2& other) {
	x *= other.x;
	y *= other.y;
	return *this;
}

vector2& vector2::operator /= (float scalar) {
	x /= scalar;
	y /= scalar;
	return *this;
}
//cast
vector2::operator float*() {
	return data;
}
vector2::operator const float*()const {
	return data;
}

float vector2::magnitued()const {
	return sqrt(x * x + y * y);
}

float vector2::magnituedSqr() const {
	return (x * x + y * y);
}

float vector2::distance(const vector2& other) const {
	float diffx = x - other.x;
	float diffy = y - other.y;
	return sqrt(diffx * diffx + diffy * diffy);
}

float vector2::Angle(vector2& other) {
	float dx = other.x - x;
	float dy = other.y - y;
	float angle = atan(dy / dx);
	return angle;
}

vector2 vector2::normalise(const vector2& v) {
	float mag = sqrt(v.x* v.x + v.y * v.y);
	return{ v.x / mag,
			v.y / mag};
}
