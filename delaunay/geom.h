#pragma once
#include <cstdlib>
#include "Matrix33.h"
#include "Matrix44.h"
#include "Matrix55.h"
#include "AABB.h"

#include "Vec3.h"

#define Matrix33 Matrix33<float>
#define Matrix44 Matrix44<float>
#define Matrix55 Matrix55<float>
//#define Vec2 Vec2<float>
#define Vec3f Vec3<float>
#define AABB AABB<float>

constexpr auto eps = 1e-5;

#define rF rand_float()

#define gP generate_Point()

struct Sphere
{
	Vec3<float> c;
	float radius;
};

struct Circle
{
	Vec3<float> c;
	float radius;
};

IL float rand_float() {
	float num1 = rand() % 1000;
	float num2 = 1 + rand() % 1000;
	float res = num1 / num2;
	return res;
}

IL  Vec3f generate_Point() {
	Vec3f cv(rF, rF, rF);
	return cv;
}



IL Matrix44* rand_Matrix44() {
	Matrix44* cmtr = new Matrix44(rF, rF, rF, rF,
		rF, rF, rF, rF,
		rF, rF, rF, rF,
		rF, rF, rF, rF);
	return cmtr;
}

IL bool checkCompl(const Vec3f& v1, const  Vec3f& v2, const  Vec3f& v3, const  Vec3f& v4) {
	Matrix33 cmtr(
		v2.x - v1.x, v2.y - v1.y, v2.z - v1.z,
		v3.x - v1.x, v3.y - v1.y, v3.z - v1.z,
		v4.x - v1.x, v4.y - v1.y, v4.z - v1.z
		);
	return !fabs(cmtr.Determinant());
}

IL float barCenterHelpFunc(float val1, float  val2, float  val3) {
	return val1 * val1 * (val2 * val2 + val3 * val3 - val1 * val1)/(val1+val2+val3);
}

IL Vec3f& CalcCircleBarCenter(const Vec3f& v1, const  Vec3f& v2, const  Vec3f& v3) {
	float al, bl, cl, BarA, BarB, BarC;

	al = v3.GetDistance(v2);
	bl = v1.GetDistance(v3);
	cl = v1.GetDistance(v2);


	Vec3f BarABC(
		barCenterHelpFunc(al, bl, cl),
		barCenterHelpFunc(bl, al, cl),
		barCenterHelpFunc(cl, al, bl));


	BarA = BarABC.x;
	BarB = BarABC.y;
	BarC = BarABC.z;


	Vec3f scenter(
		(BarA * v1.x + BarB * v2.x + BarC * v3.x) / (BarA + BarB + BarC),
		(BarA * v1.y + BarB * v2.y + BarC * v3.y) / (BarA + BarB + BarC),
		(BarA * v1.z + BarB * v2.z + BarC * v3.z) / (BarA + BarB + BarC));
	return scenter;
}



IL Vec3f projPointPlane(const Vec3f& v1, const  Vec3f& v2, const  Vec3f& v3, const  Vec3f& v4) {

	Vec3f ed1(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z),
		ed2(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);

	Vec3f vc = ed1.Cross(ed2);
	float A = vc.x, B = vc.y, C = vc.z,
		D = -vc.dot(v1);
	float t = -(vc.dot(v4) + D) / vc.dot(vc);
	return Vec3f(A * t + v4.x, B * t + v4.y, C * t + v4.z);
}

IL void LineCircleIntrPoints(Vec3f& rp1, Vec3f& rp2, const  Vec3f& ccenter, float rad, const  Vec3f& pd) {
	Vec3f nv = pd - ccenter;

	float
		t1, t2;

	/*float
		t1, t2,
		a = nv.dot(nv),
		b = 2 * nv.dot(pd - ccenter),
		c = (pd - ccenter).dot(pd - ccenter) - rad * rad,
		Dscr = b * b - 4 * a * c;


	if (Dscr >= 0) {
		t1 = (-b - sqrt(Dscr)) / (2 * fabs(a));
		t2 = (-b + sqrt(Dscr)) / (2 * fabs(a));
	}
	else
		return;*/

	t1 = -rad / sqrtf(nv.dot(nv)) - 1;
	t2 = rad / sqrtf(nv.dot(nv)) - 1;


	rp1 = Vec3f(nv.x * t1 + pd.x, nv.y * t1 + pd.y, nv.z * t1 + pd.z);
	rp2 = Vec3f(nv.x * t2 + pd.x, nv.y * t2 + pd.y, nv.z * t2 + pd.z);

}


IL void CalcCircleBarCenterDot(Circle& circle, const Vec3f& a, const  Vec3f& b, const  Vec3f& c) {
	

	float dotABAB = (b - a).dot(b - a);
	float dotABAC = (b - a).dot(c - a);
	float dotACAC = (c - a).dot(c - a);
	float d = 2.0f * (dotABAB * dotACAC - dotABAC * dotABAC);
	Vec3f referencePt = a;
	if (fabs(d) <= eps) {
		// a, b, and c lie on a line. Circle center is center of AABB of the
		// points, and radius is distance from circle center to AABB corner
		AABB bbox(a, b, c);
		circle.c =  (bbox.min + bbox.max)*0.5f;
		referencePt = bbox.min;
	}
	else {
		float s = (dotABAB * dotACAC - dotACAC * dotABAC) / d;
		float t = (dotACAC * dotABAB - dotABAB * dotABAC) / d;
		// s controls height over AC, t over AB, (1-s-t) over BC
		if (s <= 0.0f) {
			circle.c = (a + c) * 0.5f;
		}
		else if (t <= 0.0f) {
			circle.c = (a + b) * 0.5f;
		}
		else if (s + t >= 1.0f) {
			circle.c = (b + c) * 0.5f;
			referencePt = b;
		}
		else circle.c = a +  (b - a) * s +  (c - a) * t;
	}
	circle.radius = sqrtf((circle.c - referencePt).dot(circle.c - referencePt));
}

IL void CalcSphereBarCenterDot(Sphere& sphere, const Vec3f& a, const  Vec3f& b, const  Vec3f& c) {


	float dotABAB = (b - a).dot(b - a);
	float dotABAC = (b - a).dot(c - a);
	float dotACAC = (c - a).dot(c - a);
	float d = 2.0f * (dotABAB * dotACAC - dotABAC * dotABAC);
	Vec3f referencePt = a;
	if (fabs(d) <= eps) {
		// a, b, and c lie on a line. Circle center is center of AABB of the
		// points, and radius is distance from circle center to AABB corner
		AABB bbox(a, b, c);
		sphere.c = (bbox.min + bbox.max) * 0.5f;
		referencePt = bbox.min;
	}
	else {
		float s = (dotABAB * dotACAC - dotACAC * dotABAC) / d;
		float t = (dotACAC * dotABAB - dotABAB * dotABAC) / d;
		// s controls height over AC, t over AB, (1-s-t) over BC
		if (s <= 0.0f) {
			sphere.c = (a + c) * 0.5f;
		}
		else if (t <= 0.0f) {
			sphere.c = (a + b) * 0.5f;
		}
		else if (s + t >= 1.0f) {
			sphere.c = (b + c) * 0.5f;
			referencePt = b;
		}
		else sphere.c = a + (b - a) * s + (c - a) * t;
	}
	sphere.radius = sqrtf((sphere.c - referencePt).dot(sphere.c - referencePt));
}


