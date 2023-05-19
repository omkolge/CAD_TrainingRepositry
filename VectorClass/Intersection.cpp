#include "Core.h"
#include "Intersection.h"
#include "GeoUtils.h"
#include"Line.h"
using namespace jmk;

bool jmk::Intersection(const jmk::Line2d& l1, const jmk::Line2d& l2, jmk::Point2d& intersection) 
{
	auto l1_start = l1.getPoint();
	auto l1_end = l1_start + l1.getDir(); // end points of line
	auto l2_start = l2.getPoint();
	auto l2_end = l2_start + l2.getPoint();

	return Intersection(l1_start, l1_end, l2_start, l2_end, intersection);
	
}

bool jmk::Intersection(const jmk::Point2d& a, const jmk::Point2d& b, const jmk::Point2d& c, const jmk::Point2d& d) {

	// if one of the end points of a segment is in between other segment endpoints we consider it as intersection.
	auto ab_c = jmk::orientation2d(a, b, c);
	auto ab_d = jmk::orientation2d(a, b, d);
	auto cd_a = jmk::orientation2d(c, d, a);
	auto cd_b = jmk::orientation2d(c, d, b);

	if (ab_c == BETWEEN || ab_c == ORIGIN || ab_c == DESTINATION
		|| ab_d == BETWEEN || ab_d == ORIGIN || ab_d == DESTINATION
		|| cd_a == BETWEEN || cd_a == ORIGIN || cd_a == DESTINATION
		|| cd_b == BETWEEN || cd_b == ORIGIN || cd_b == DESTINATION
		)
	{
		true;
	}
	return _xor(ab_c == LEFT, ab_d == LEFT) && _xor(cd_a == LEFT, cd_b == LEFT);
	/*if (jmk::orientation2d(a, b, c) == jmk::BETWEEN
		|| jmk::orientation2d(a, b, d) == jmk::BETWEEN
		|| jmk::orientation2d(c, d, a) == jmk::BETWEEN
		|| jmk::orientation2d(c, d, b) == jmk::BETWEEN)
	{
		return true;
	}
	return jmk::_xor(jmk::left(a, b, c), jmk::left(a, b, d)) && jmk::_xor(jmk::left(c, d, a), jmk::left(c, d, b));*/
}

bool jmk::Intersection(const jmk::Point2d& a, const jmk::Point2d& b, const jmk::Point2d& c, const jmk::Point2d& d,  jmk::Point2d& interseciton)
{
	Vector2f AB = b - a;
	Vector2f CD = d - c;

	//Normal vector to CD
	Vector2f n(CD[Y], -CD[X]);

	//Denominator = n.(b-a)
	auto deno = dotProduct(n, AB);

	if (!isEqualD(deno, ZERO))
	{
		auto AC = c - a;
		auto nume = dotProduct(n, AC);
		auto t = nume / deno;

		auto x = a[X] + t * AB[X];
		auto y = a[Y] + t * AB[Y];

		interseciton.assign(X, x);
		interseciton.assign(Y, y);
		return true;
	}
	else
	{
		// Lines are parallel or colinear
		return false;
	}
}

//bool jmk::intersect(jmk::Planef& plane, jmk::Line& line, jmk::Point3d& point) {
//
//	auto n = plane.getNormal();
//	auto D = plane.getD();
//	auto d = line.direction();
//	auto p = line.point();
//
//	auto denominator = dotProduct(n, d);
//
//	if (!isEqualD(denominator, ZERO)) {
//		auto t = (-1 * dotProduct(n, p) + D) / denominator;
//		point.assign(X, p[X] + t * d[X]);
//		point.assign(Y, p[Y] + t * d[Y]);
//		point.assign(Z, p[Z] + t * d[Z]);
//		return true;
//	}
//	else {
//		return false;
//	}
//}


//bool jmk::intersect(jmk::Planef& p1, jmk::Planef& p2, jmk::Line& l) {
//
//	auto n1 = p1.getNormal();
//	auto n2 = p2.getNormal();
//	auto d1 = p1.getD();
//	auto d2 = p2.getD();
//
//	auto direction = crossProduct3d(n1, n2);
//	direction.normalize();
//
//	// Check if the planes are parallel.
//	if (isEqualD(direction.magnitude(), ZERO))
//		return false;
//
//	auto n1n2 = dotProduct(n1, n2);
//	auto n1n2_2 = n1n2 * n1n2;
//
//	auto a = (d2 * n1n2 - d1) / (n1n2_2 - 1);
//	auto b = (d1 * n1n2 - d2) / (n1n2_2 - 1);
//
//	auto point = n1 * a + n2 * b;
//
//	l.setPoint(point);
//	l.setDirection(direction);
//
//	return true;
//}



//bool jmk::intersect(jmk::Line2d& line, jmk::Segment2d& seg) {
//
//	// TODO : This can be done efficiently by checking the end points orientation
//	// compared to the line.
//	Vector2f dir = seg.p2 - seg.p1;
//	Point2d point = seg.p1;
//	jmk::Line2d seg_line(point, dir);
//	return intersect(line, seg_line, point);
//}
//
//bool jmk::intersect(jmk::Line2d& line, jmk::Segment2d& seg, jmk::Point2d& pi) {
//	Vector2f dir = seg.p2 - seg.p1;
//	Point2d point = seg.p1;
//	jmk::Line2d seg_line(point, dir);
//	return intersect(line, seg_line, pi);
//}