#include "Matrix3.h"



Matrix3::Matrix3()
{

}

Matrix3::Matrix3(const Matrix3& mat3)
{
	xAxis = mat3.xAxis;
	yAxis = mat3.yAxis;
	zAxis = mat3.zAxis;
}

Matrix3::Matrix3(float xx, float yx, float zx,
				 float xy, float yy, float zy,
				 float xz, float yz, float zz)
{
	data[0][0] = xx;
	data[0][1] = yx;
	data[0][2] = zx;
	data[1][0] = xy;
	data[1][1] = yy;
	data[1][2] = zy;
	data[2][0] = xz;
	data[2][1] = yz;
	data[2][2] = zz;
}

Matrix3::~Matrix3()
{
}

Matrix3::operator float*()
{
	return &xAxis.x;
}

Matrix3::operator const float* () const
{
	return &xAxis.x;
}

Vector3& Matrix3::operator[](int index)
{
	return axis[index];
}

const Vector3& Matrix3::operator[](int index)const
{
	return axis[index];
}

Matrix3 Matrix3::operator * (const Matrix3& other) const
{
	Matrix3 result;

	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			result.data[c][r] = data[0][r] * other.data[c][0] +
								data[1][r] * other.data[c][1] +
								data[2][r] * other.data[c][2];
		}
	}
	return result;
}

Matrix3& Matrix3::operator = (const Matrix3& other)
{

	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			data[c][r] = other.data[c][r];
		}
	}
	return *this;
}
Matrix3 Matrix3::operator *= (const Matrix3& other) const
{
	Matrix3 result;

	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			result.data[c][r] = data[0][r] * other.data[c][0] +
								data[1][r] * other.data[c][1] +
								data[2][r] * other.data[c][2];
		}
	}
	return result;
}
Vector3 Matrix3::operator*(const Vector3& v) const
{
	Vector3 result;

	for (int r = 0; r < 3; ++r) {
		result[r] = data[0][r] * v[0] +
					data[1][r] * v[1] +
					data[2][r] * v[2];
	}

	return result;
}

Matrix3 Matrix3::transposed() const
{
	Matrix3 result;

	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			result.data[r][c] = data[c][r];
		}
	}

	return result;
}


Matrix3 Matrix3::operator+(const Matrix3& other) const
{
	Matrix3 result;

	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			result.data[c][r] = data[c][r] + other.data[c][r];
		}
	}

	return result;
}

Matrix3 Matrix3::operator-(const Matrix3& other) const
{
	Matrix3 result;

	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			result.data[c][r] = data[c][r] - other.data[c][r];
		}
	}

	return result;
}

Matrix3 Matrix3::setScaled(float x, float y, float z)
{
	xAxis = { x, 0, 0 };
	yAxis = { 0, y, 0 };
	zAxis = { 0, 0, z };
	return *this;
}

Matrix3 Matrix3::setScaled(const Vector3& v)
{
	xAxis = { v.x, 0, 0 };
	yAxis = { 0, v.y, 0 };
	zAxis = { 0, 0, v.z };
	return *this;
}

void Matrix3::scale(float x, float y, float z)
{
	Matrix3 m;
	m.setScaled(x, y, z);
	*this = *this * m;
}

void Matrix3::scale(const Vector3& v)
{
	Matrix3 m;
	m.setScaled(v.x, v.y, v.z);
	*this = *this * m;
}

void Matrix3::setRotateX(float radians)
{
	xAxis = { 1, 0, 0 };
	yAxis = { 0, cosf(radians), sinf(radians) };
	zAxis = { 0, -sinf(radians), cosf(radians) };
}

Matrix3& Matrix3::setRotateY(float radians)
{
	
	xAxis = { cosf(radians), 0, -sinf(radians) };
	yAxis = { 0, 1, 0 };
	zAxis = { sinf(radians), 0, cosf(radians) };
	return *this;
}

Matrix3& Matrix3::setRotateZ(float radians)
{
	xAxis = { cosf(radians),sinf(radians) , 0};
	yAxis = { -sinf(radians), cosf(radians), 0 };
	zAxis = { 0, 0, 1 };
	return *this;
}

void Matrix3::rotateX(float radians)
{
	Matrix3 m;
	m.setRotateX(radians);

	*this = *this * m;
}

void Matrix3::rotateY(float radians)
{
	Matrix3 m;
	m.setRotateY(radians);

	*this = *this * m;
}

void Matrix3::rotateZ(float radians)
{
	Matrix3 m;
	m.setRotateZ(radians);

	*this = *this * m;
}

void Matrix3::setEuler(float pitch, float yaw, float roll)
{
	Matrix3 x, y, z;
	x.setRotateX(pitch);
	y.setRotateY(yaw);
	z.setRotateX(roll);

	*this = z * y * x;
}
Matrix3& Matrix3::translate(float x, float y)
{
	Matrix3 m;
	zAxis.x += x;
	zAxis.y += y;
	zAxis.z = 1;
	*this * m;
	return *this;
}
Matrix3& Matrix3::translate(Vector3 other)
{
	Matrix3 m;
	zAxis.x += other.x;
	zAxis.y += other.y;
	zAxis.z = 1;
	*this * m;
	return *this;
}
const Matrix3 Matrix3::identity = Matrix3(1, 0, 0,
										  0, 1, 0, 
										  0, 0, 1);