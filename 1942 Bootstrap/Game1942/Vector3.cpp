#include "Vector3.h"


vector3::vector3(float vx, float vy, float vz) {
	x = vx;
	y = vy;
	z = vz;
}
float vector3::operator[](int index)const {
	return data[index];
}

vector3 vector3::operator+(const vector3& other) const {
	return{ x + other.x,
			y + other.y,
			z + other.z };
}

vector3 vector3::operator-(const vector3& other) const {
	return{ x - other.x,
			y - other.y,
			z - other.z };
}

vector3 vector3::operator = (const vector3& other) {
	return{ x = other.x,
			y = other.y,
			z = other.z };
}


vector3 vector3::operator * (float scalar) const {
	return { x * scalar,
			 y * scalar,
			 z * scalar };
}

vector3& vector3::operator += (float scalar) {
	x += scalar;
	y += scalar;
	z += scalar;
	return *this;
}
vector3& vector3::operator -= (float scalar) {
	x -= scalar;
	y -= scalar;
	z -= scalar;
	return *this;
}

vector3& vector3::operator -= (vector3& other) {
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

vector3& vector3::operator += (const vector3& other) {
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}
vector3& vector3::operator *= (const vector3& other) {
	x *= other.x;
	y *= other.y;
	z *= other.z;
	return *this;
}

vector3& vector3::operator /= (float scalar) {
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}
//cast
vector3::operator float*() {
	return data;
}
vector3::operator const float*()const {
	return data;
}

float vector3::magnitued()const {
	return sqrt(x * x + y * y + z * z);
}

float vector3::magnituedSqr() const {
	return (x * x + y * y + z * z);
}

float vector3::distance(const vector3& other) const {
	float diffx = x - other.x;
	float diffy = y - other.y;
	float diffz = z - other.z;
	return sqrt(diffx * diffx + diffy * diffy + diffz + diffz);
}

float vector3::Angle(vector3& other) {
	float dx = other.x - x;
	float dy = other.y - y;
	float dz = other.z - z;
	float angle = atan(dy / dx);
	return angle;
}

vector3 vector3::normalise(const vector3& v) {
	float mag = sqrt(v.x* v.x + v.y * v.y + v.z * v.z);
	return{ v.x / mag,
			v.y / mag,
			v.z / mag };
}
