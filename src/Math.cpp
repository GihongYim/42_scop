#include "Math.hpp"

#include <cmath>
#include <stdexcept>

Vec2::Vec2(void)
	: x(0.0f), y(0.0f)
{
}

Vec2::Vec2(float xValue, float yValue)
	: x(xValue), y(yValue)
{
}

Vec3::Vec3(void)
	: x(0.0f), y(0.0f), z(0.0f)
{
}

Vec3::Vec3(float xValue, float yValue, float zValue)
	: x(xValue), y(yValue), z(zValue)
{
}

Mat4::Mat4(void)
{
	for (int i = 0; i < 16; ++i)
		data[i] = 0.0f;
}

Mat4::Mat4(float diagonal)
{
	for (int i = 0; i < 16; ++i)
		data[i] = 0.0f;
	data[0] = diagonal;
	data[5] = diagonal;
	data[10] = diagonal;
	data[15] = diagonal;
}

const float *Mat4::ptr(void) const
{
	return data;
}

float *Mat4::ptr(void)
{
	return data;
}

float &Mat4::operator()(int row, int column)
{
	return data[column * 4 + row];
}

float Mat4::operator()(int row, int column) const
{
	return data[column * 4 + row];
}

Mat4 Mat4::identity(void)
{
	return Mat4(1.0f);
}

Mat4 Mat4::translate(const Vec3 &offset)
{
	return Mat4::translation(offset);
}

Mat4 Mat4::rotateX(float radians)
{
	return Mat4::rotationX(radians);
}

Mat4 Mat4::rotateY(float radians)
{
	return Mat4::rotationY(radians);
}

Mat4 Mat4::rotateZ(float radians)
{
	return Mat4::rotationZ(radians);
}

Mat4 Mat4::translation(const Vec3 &offset)
{
	Mat4 result = Mat4::identity();

	result(0, 3) = offset.x;
	result(1, 3) = offset.y;
	result(2, 3) = offset.z;
	return result;
}

Mat4 Mat4::rotationX(float radians)
{
	Mat4 result = Mat4::identity();
	const float c = std::cos(radians);
	const float s = std::sin(radians);

	result(1, 1) = c;
	result(2, 1) = s;
	result(1, 2) = -s;
	result(2, 2) = c;
	return result;
}

Mat4 Mat4::rotationY(float radians)
{
	Mat4 result = Mat4::identity();
	const float c = std::cos(radians);
	const float s = std::sin(radians);

	result(0, 0) = c;
	result(2, 0) = -s;
	result(0, 2) = s;
	result(2, 2) = c;
	return result;
}

Mat4 Mat4::rotationZ(float radians)
{
	Mat4 result = Mat4::identity();
	const float c = std::cos(radians);
	const float s = std::sin(radians);

	result(0, 0) = c;
	result(1, 0) = s;
	result(0, 1) = -s;
	result(1, 1) = c;
	return result;
}

Mat4 Mat4::scale(const Vec3 &factor)
{
	Mat4 result = Mat4::identity();

	result(0, 0) = factor.x;
	result(1, 1) = factor.y;
	result(2, 2) = factor.z;
	return result;
}

Mat4 Mat4::perspective(float fov, float aspect, float near, float far)
{
	if (aspect == 0.0f)
		throw std::runtime_error("perspective aspect ratio must not be zero");
	if (near <= 0.0f || far <= 0.0f || near == far)
		throw std::runtime_error("invalid perspective clipping planes");

	Mat4 result;
	const float tanHalfFovy = std::tan(fov / 2.0f);

	if (tanHalfFovy == 0.0f)
		throw std::runtime_error("invalid perspective field of view");

	result(0, 0) = 1.0f / (aspect * tanHalfFovy);
	result(1, 1) = 1.0f / tanHalfFovy;
	result(2, 2) = -(far + near) / (far - near);
	result(2, 3) = -(2.0f * far * near) / (far - near);
	result(3, 2) = -1.0f;
	return result;
}

Mat4 operator*(const Mat4 &left, const Mat4 &right)
{
	Mat4 result;

	for (int row = 0; row < 4; ++row)
	{
		for (int column = 0; column < 4; ++column)
		{
			for (int i = 0; i < 4; ++i)
				result(row, column) += left(row, i) * right(i, column);
		}
	}
	return result;
}
