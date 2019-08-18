#include "Matrix4.h"



Matrix4::Matrix4()
{
}

Matrix4::Matrix4(const Matrix4& mat4)
{
	xAxis = mat4.xAxis;
	yAxis = mat4.yAxis;
	zAxis = mat4.zAxis;
	translation = mat4.translation;
}

Matrix4::Matrix4(float xx, float xy, float xz, float xt,
				 float yx, float yy, float yz, float yt,
				 float zx, float zy, float zz, float zt,
				 float tx, float ty, float tz, float tt)
{
	data[0][0] = xx;
	data[0][1] = xy;
	data[0][2] = xz;
	data[0][3] = xt;
	data[1][0] = yx;
	data[1][1] = yy;
	data[1][2] = yz;
	data[1][3] = yt;
	data[2][0] = zx;
	data[2][1] = zy;
	data[2][2] = zz;
	data[2][3] = zt;
	data[3][0] = tx;
	data[3][1] = ty;
	data[3][2] = tz;
	data[3][3] = tt;
}

Matrix4::~Matrix4()
{
}

Matrix4::operator float*()
{
	return &xAxis.x;
}

Matrix4::operator const float* () const
{
	return &xAxis.x;
}

Vector4& Matrix4::operator[](int index)
{
	return axis[index];
}

const Vector4& Matrix4::operator[](int index)const
{
	return axis[index];
}

Matrix4 Matrix4::operator * (const Matrix4& other) const
{
	Matrix4 result;

	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			result.data[c][r] = data[0][r] * other.data[c][0] +
								data[1][r] * other.data[c][1] +
								data[2][r] * other.data[c][2] + 
								data[3][r] * other.data[c][3];
		}
	}

	return result;
}
Matrix4& Matrix4::operator = (const Matrix4& other)
{
	Matrix4 result;

	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			data[c][r] = other.data[c][r];
		}
	}
	return *this;
}
Vector4 Matrix4::operator*(const Vector4& v) const
{
	Vector4 result;

	for (int r = 0; r < 4; ++r) {
		result[r] = data[0][r] * v[0] +
					data[1][r] * v[1] +
					data[2][r] * v[2] +
					data[3][r] * v[3];
	}

	return result;
}

Matrix4 Matrix4::transposed() const
{
	Matrix4 result;

	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			result.data[r][c] = data[c][r];
		}
	}

	return result;
}

Matrix4 Matrix4::operator+(const Matrix4& other) const
{
	Matrix4 result;

	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			result.data[c][r] = data[c][r] + other.data[c][r];
		}
	}

	return result;
}

Matrix4 Matrix4::operator-(const Matrix4& other) const
{
	Matrix4 result;

	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			result.data[c][r] = data[c][r] - other.data[c][r];
		}
	}

	return result;
}

Matrix4 Matrix4::setScaled(float x, float y, float z)
{
	xAxis = { x, 0, 0, 0 };
	yAxis = { 0, y, 0, 0 };
	zAxis = { 0, 0, z, 0 };
	translation = { 0, 0, 0, 1 };
	return *this;
}

Matrix4 Matrix4::setScaled(const Vector4& v)
{
	xAxis = { v.x, 0, 0, 0 };
	yAxis = { 0, v.y, 0, 0 };
	zAxis = { 0, 0, v.z, 0 };
	translation = { 0, 0, 0, 1 };
	return *this;
}


void Matrix4::scale(float x, float y, float z)
{
	Matrix4 m;
	m.setScaled(x, y, z);
	*this = *this * m;
}

void Matrix4::scale(const Vector4& v)
{
	Matrix4 m;
	m.setScaled(v.x, v.y, v.z);
	*this = *this * m;
}

void Matrix4::setRotateX(float radians)
{
	xAxis = { 1, 0, 0, 0 };
	yAxis = { 0, cosf(radians), sinf(radians), 0 };
	zAxis = { 0, -sinf(radians), cosf(radians), 0 };
	translation = { 0,0,0,1 };
}

void Matrix4::setRotateY(float radians)
{
	xAxis = { cosf(radians), 0, -sinf(radians), 0 };
	yAxis = { 0, 1, 0, 0 };
	zAxis = { sinf(radians), 0, cosf(radians), 0 };
	translation = { 0,0,0,1 };
}

void Matrix4::setRotateZ(float radians)
{
	xAxis = { cosf(radians), sinf(radians), 0, 0 };
	yAxis = { -sinf(radians), cosf(radians), 0, 0 };
	zAxis = { 0, 0, 1, 0 };
	translation = { 0,0,0,1 };
}

void Matrix4::rotateX(float radians)
{
	Matrix4 m;
	m.setRotateX(radians);

	*this = *this * m;
}

void Matrix4::rotateY(float radians)
{
	Matrix4 m;
	m.setRotateY(radians);

	*this = *this * m;
}

void Matrix4::rotateZ(float radians)
{
	Matrix4 m;
	m.setRotateZ(radians);

	*this = *this * m;
}

void Matrix4::setEuler(float pitch, float yaw, float roll)
{
	Matrix4 x, y, z;
	x.setRotateX(pitch);
	y.setRotateY(yaw);
	z.setRotateX(roll);

	*this = z * y * x;
}
void Matrix4::translate(float x, float y, float z)
{
	Matrix4 m;
	m.data[0][3] += x;
	m.data[1][3] += y;
	m.data[2][3] += z;
	m.data[3][3] = 1;
	*this * m;

}
const Matrix4 Matrix4::identity = Matrix4(1, 0, 0, 0,
										  0, 1, 0, 0, 
										  0, 0, 1, 0,
										  0, 0, 0, 1 );