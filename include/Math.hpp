#ifndef MATH_HPP
# define MATH_HPP

struct Vec2
{
	float x;
	float y;

	Vec2(void);
	Vec2(float xValue, float yValue);
};

struct Vec3
{
	float x;
	float y;
	float z;

	Vec3(void);
	Vec3(float xValue, float yValue, float zValue);
};

struct Mat4
{
	float data[16];

	Mat4(void);
	explicit Mat4(float diagonal);

	const float *ptr(void) const;
	float *ptr(void);

	float &operator()(int row, int column);
	float operator()(int row, int column) const;

	static Mat4 identity(void);
	static Mat4 translate(const Vec3 &offset);
	static Mat4 rotateX(float radians);
	static Mat4 rotateY(float radians);
	static Mat4 rotateZ(float radians);
	static Mat4 scale(const Vec3 &factor);

	static Mat4 translation(const Vec3 &offset);
	static Mat4 rotationX(float radians);
	static Mat4 rotationY(float radians);
	static Mat4 rotationZ(float radians);
	static Mat4 perspective(float fov, float aspect, float near, float far);
};

Mat4 operator*(const Mat4 &left, const Mat4 &right);

#endif
