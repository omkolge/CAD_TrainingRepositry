#include"GeoUtils.h"
#include"Vector.h"

#include <math.h>
#include <set>
#include <map>
#include <algorithm>
#include <list>

#include "Intersection.h"

using namespace jmk;

int jmk::orientation3d(const Point3d& a, const Point3d& b, const Point3d& c)
{
	float area = areaTriangle3d(a, b, c);

	if (area > 0 && area < TOLERANCE)
		area = 0;

	if (area < 0 && area > TOLERANCE)
		area = 0;

	Point3d p1 = b - a;
	Point3d p2 = c - a;

	double p1x, p1y, p2x, p2y;

	p1x = p1[X];
	p1y = p1[Y];
	p2x = p2[X];
	p2y = p2[Y];

	if (area > 0.0)
		return LEFT;
	if (area < 0.0)
		return RIGHT;
	if ((p1x * p2x < 0.0) || (p1y * p2y < 0.0))
		return BEHIND;
	if (p1.magnitude() < p2.magnitude())
		return BEYOND;
	if (a == c)
		return ORIGIN;
	if (b == c)
		return DESTINATION;
	return BETWEEN;

	return 0;
}

//int jmk::orientation3d(const Point3d& a, const Point3d& b, const Point3d& c)
//{
//	return orientation(a,b,c);
//}

int jmk::orientation2d(const Point2d& a, const Point2d& b, const Point2d& c)
{
	float area = areaTriangle2d(a, b, c);

	if (area > 0 && area < TOLERANCE)
		area = 0;

	if (area < 0 && area > TOLERANCE)
		area = 0;

	Vector2f ab = b - a;
	Vector2f ac = c - a;

	if (area > 0.0)
		return LEFT;
	if (area < 0.0)
		return RIGHT;
	if ((ab[X] * ac[X] < 0.0) || (ab[Y] * ac[Y] < 0.0))
		return BEHIND;
	if (ab.magnitude() < ac.magnitude())
		return BEYOND;
	if (a == c)
		return ORIGIN;
	if (b == c)
		return DESTINATION;
	return BETWEEN;

	return 0;
}

//int jmk::orientation2d(const Point2d& a, const Point2d& b, const Point2d& c)
//{
//	return orientation(a, b, c);
//}

bool jmk::left(const Point3d& a, const Point3d& b, const Point3d& c)
{
	return orientation3d(a, b, c) == RELATIVE_POSITION::LEFT;
}

bool jmk::left(const Point2d& a, const Point2d& b, const Point2d& c)
{
	return orientation2d(a, b, c) == RELATIVE_POSITION::LEFT;
}

bool jmk::right(const Point3d& a, const Point3d& b, const Point3d& c)
{
	return orientation3d(a, b, c) == RELATIVE_POSITION::RIGHT;
}

bool jmk::leftOrBeyond(const Point2d& a, const Point2d& b, const Point2d& c)
{
	int position = orientation2d(a, b, c);
	return (position == RELATIVE_POSITION::LEFT || position == RELATIVE_POSITION::BEYOND);
}

bool jmk::leftOrBeyond(const Point3d& a, const Point3d& b, const Point3d& c)
{
	int position = orientation3d(a, b, c);
	return (position == RELATIVE_POSITION::LEFT || position == RELATIVE_POSITION::BEYOND);
}

bool jmk::leftOrBetween(const Point3d& a, const Point3d& b, const Point3d& c)
{
	int position = orientation3d(a, b, c);
	return (position == RELATIVE_POSITION::LEFT || position == RELATIVE_POSITION::BETWEEN);
}




float jmk::polarAngle(const Point2d& _other, const Point2d& _ref)
{
	// Consider the given points as 2D ones which are in XY plane
	float _x = _other[X] - _ref[X];
	float _y = _other[Y] - _ref[Y];

	if ((isEqualD(_x, 0.0)) && (isEqualD(_y, 0.0)))
		return -1.0;
	if (isEqualD(_x, 0.0))
		return ((_y > 0.0) ? 90 : 270);

	double theta = atan(_y / _x);
	theta = RadianceToDegrees(theta);
	//theta *= 360 / (2 * M_PI);

	if (_x > 0.0)
		return ((_y >= 0.0) ? theta : 360 + theta);
	else
		return (180 + theta);
}

double jmk::areaTriangle2d(const Point3d& a, const Point3d& b, const Point3d& c)
{
	return 0.5 * ((b[X] - a[X]) * (c[Y] - a[Y]) - (c[X] - a[X]) * (b[Y] - a[Y]));
}

double jmk::areaTriangle2d(const Point2d& a, const Point2d& b, const Point2d& c)
{
	auto AB = b - a;
	auto AC = c - a;
	auto result = crossProduct2d(AB, AC);
	return result / 2;  // area of triang. will half of that value.
	//return 0.5 * ((b[X] - a[X]) * (c[Y] - a[Y]) - (c[X] - a[X]) * (b[Y] - a[Y]));
}

double jmk::areaTriangle3d(const Point3d& a, const Point3d& b, const Point3d& c)
{
	float x_, y_, z_;

	Vector3f AB = b - a;
	Vector3f AC = c - a;

	x_ = AB[Y] * AC[Z] - AB[Z] * AC[Y];
	y_ = AB[X] * AC[Z] - AB[Z] * AC[X];
	z_ = AB[X] * AC[Y] - AB[Y] * AC[X];

	float sum_of_powers = pow(x_, 2.0) + pow(y_, 2.0) + pow(z_, 2.0);
	float root = sqrtf(sum_of_powers);
	return root / 2;
}




float jmk::angle(const Vector2f& _v1, const Vector2f& _v2)
{
	float dot = dotProduct(_v1, _v2);
	float v1_mag = _v1.magnitude();
	float v2_mag = _v2.magnitude();
	auto deno = v1_mag * v2_mag;
	if (isEqualDL(dot, deno))
		return 0;

	return acos(dot / (v1_mag * v2_mag));
}

int jmk::getClosestPointIndex(Point3d& _point, std::vector<Point3d>& _points)
{
	return 0;
}

bool jmk::collinear(const Point3d& a, const Point3d& b, const Point3d& c)
{
	Vector3f P = b - a;
	Vector3f Q = c - a;

	return collinear(P, Q);
}

bool jmk::collinear(const Vector3f& a, const Vector3f& b)
{
	auto v1 = a[X] * b[Y] - a[Y] * b[X];
	auto v2 = a[Y] * b[Z] - a[Z] * b[Y];
	auto v3 = a[X] * b[Z] - a[Z] * b[X];

	return isEqualD(v1, ZERO) && isEqualD(v2, ZERO) && isEqualD(v3, ZERO);
}

bool jmk::coplaner(const Point3d& a, const Point3d& b, const Point3d& c, const Point3d& d)
{
	Vector3f AB = b - a;
	Vector3f AC = c - a;
	Vector3f AD = d - a;
	return coplaner(AB, AC, AD);
}

bool jmk::coplaner(const Vector3f& _v1, const Vector3f& _v2, const Vector3f& _v3)
{
	float value = scalerTripleProduct(_v1, _v2, _v3);
	return isEqualD(value, ZERO);
}






//double jmk::areaTriangle2d(const Point2d& a, const Point2d& b, const Point2d& c)
//{
//	auto AB = b - a;
//	auto AC = c - a;
//	auto result = crossProduct2d(AB, AC);
//	return result / 2;  // area of triang. will half of that value.
//
//	//return 0.5 * ((b[X] - a[X]) * (c[Y] - a[Y]) - (c[X] - a[X]) * (b[Y] - a[Y]));
//}
