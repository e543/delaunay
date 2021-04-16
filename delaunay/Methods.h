#pragma once
#include "TestMethod.h"
#include <iostream>
#include "geom.h"



// Method Maur1


class Maur1 : public IMethod {

public:
	Maur1() {
		IMethod::method_name = MethodName::MethodMaur1;
	}
	~Maur1() {
	}
	IL TestResult getResult(const Vec3f& v1, const Vec3f& v2, const Vec3f& v3, const Vec3f& v4, const Vec3f& r5)
	{
		Matrix55 mtr(
			v1.x, v1.y, v1.z, v1.dot(v1), 1,
			v2.x, v2.y, v2.z, v2.dot(v2), 1,
			v3.x, v3.y, v3.z, v3.dot(v3), 1,
			v4.x, v4.y, v4.z, v4.dot(v4), 1,
			r5.x, r5.y, r5.z, r5.dot(r5), 1
		);

		auto det = mtr.Determinant();
		calcResult(det);
		test_res.point_state = state_res;
		return test_res;
	}
};

// Method Maur2

class Maur2 : public IMethod {

public:
	Maur2() {
		IMethod::method_name = MethodName::MethodMaur2;
	}
	~Maur2() {
	}
	IL TestResult getResult(const Vec3f& v1, const Vec3f& v2, const Vec3f& v3, const Vec3f& v4, const Vec3f& r5)
	{

		Matrix44 mtr(
			v1.x - r5.x, v1.y - r5.y, v1.z - r5.z, v1.GetSquaredDistance(r5),
			v2.x - r5.x, v2.y - r5.y, v2.z - r5.z, v2.GetSquaredDistance(r5),
			v3.x - r5.x, v3.y - r5.y, v3.z - r5.z, v3.GetSquaredDistance(r5),
			v4.x - r5.x, v4.y - r5.y, v4.z - r5.z, v4.GetSquaredDistance(r5)
		);

		auto det = mtr.Determinant();
		calcResult(det);
		test_res.point_state = state_res;
		return test_res;
	}
};


// Method3

class Method3 : public IMethod {

public:
	Method3() {
		IMethod::method_name = MethodName::_Method3;
	}
	~Method3() {
	}
	IL TestResult getResult(const Vec3f& v1, const Vec3f& v2, const Vec3f& v3, const Vec3f& v4, const Vec3f& r5)
	{

		Matrix44 A(
			v1.x, v1.y, v1.z, 1,
			v2.x, v2.y, v2.z, 1,
			v3.x, v3.y, v3.z, 1,
			v4.x, v4.y, v4.z, 1
		);


		Matrix44 C(
			v1.dot(v1), v1.x, v1.y, v1.z,
			v2.dot(v2), v2.x, v2.y, v2.z,
			v3.dot(v3), v3.x, v3.y, v3.z,
			v4.dot(v4), v4.x, v4.y, v4.z
		);

		Matrix44 mDx(
			v1.dot(v1), v1.y, v1.z, 1,
			v2.dot(v2), v2.y, v2.z, 1,
			v3.dot(v3), v3.y, v3.z, 1,
			v4.dot(v4), v4.y, v4.z, 1
		);

		Matrix44 mDy(
			v1.dot(v1), v1.x, v1.z, 1,
			v2.dot(v2), v2.x, v2.z, 1,
			v3.dot(v3), v3.x, v3.z, 1,
			v4.dot(v4), v4.x, v4.z, 1
		);

		Matrix44 mDz(
			v1.dot(v1), v1.x, v1.y, 1,
			v2.dot(v2), v2.x, v2.y, 1,
			v3.dot(v3), v3.x, v3.y, 1,
			v4.dot(v4), v4.x, v4.y, 1
		);


		auto a = A.Determinant();
		auto c = C.Determinant();

		const auto Dx = mDx.Determinant();
		const auto Dy = -mDy.Determinant();
		const auto Dz = mDz.Determinant();

		const float ha = 1 / (2 * a);

		const auto x0 = Dx * ha;
		const auto y0 = Dy * ha;
		const auto z0 = Dz * ha;

		const auto rad = sqrtf(Dx * Dx + Dy * Dy + Dz * Dz - 4 * a * c) * ha;

		Vec3f cur_scenter(x0, y0, z0);
		float distant = r5.GetDistance(cur_scenter);
		calcResult(rad - distant);

		test_res.circumsphere.radius = rad;
		test_res.circumsphere.c = cur_scenter;
		test_res.point_state = state_res;
		return test_res;
	}
};


// Method4


class Method4 : public IMethod {

public:
	Method4() {
		IMethod::method_name = MethodName::_Method4;
	}
	~Method4() {
	}
	IL TestResult getResult(const Vec3f& v1, const Vec3f& v2, const Vec3f& v3, const Vec3f& v4, const Vec3f& r5)
	{
		Vec3f ccenter = CalcCircleBarCenter(v1, v2, v3);
		float rad = v1.GetDistance(ccenter);


		Vec3f pd = projPointPlane(v1, v2, v3, v4);
		Vec3f S, T;
		LineCircleIntrPoints(S, T, ccenter, rad, pd);

		Vec3f scenter = CalcCircleBarCenter(S, T, v4);

		const float distant = r5.GetDistance(scenter);
		rad = scenter.GetDistance(v4);

		calcResult(rad - distant);
		test_res.circumsphere.radius = rad;
		test_res.circumsphere.c = scenter;
		test_res.point_state = state_res;
		return test_res;
	}
};


// Method5


class Method5 : public IMethod {

public:
	Method5() {
		IMethod::method_name = MethodName::_Method5;
	}
	~Method5() {
	}
	IL TestResult getResult(const Vec3f& v1, const Vec3f& v2, const Vec3f& v3, const Vec3f& v4, const Vec3f& r5)
	{
		Circle ccircle;
		CalcCircleBarCenterDot(ccircle, v1, v2, v3);


		Vec3f pd = projPointPlane(v1, v2, v3, v4);
		Vec3f S, T;
		LineCircleIntrPoints(S, T, ccircle.c, ccircle.radius, pd);

		Circle scircle;
		CalcCircleBarCenterDot(scircle, S, T, v4);
		Vec3f scenter = scircle.c;

		const auto distant = r5.GetDistance(scircle.c);

		calcResult(scircle.radius - distant);
		test_res.circumsphere.radius = scircle.radius;
		test_res.circumsphere.c = scenter;
		test_res.point_state = state_res;
		return test_res;
	}
};



// Method6

class Method6 : public IMethod {

public:
	Method6() {
		IMethod::method_name = MethodName::_Method6;
	}
	~Method6() {
	}

	IL TestResult getResult(const Vec3f& v1, const Vec3f& v2, const Vec3f& v3, const Vec3f& v4, const Vec3f& r5)
	{
		Circle ccircle;
		CalcCircleBarCenterDot(ccircle, v1, v2, v3);
		return test_res;
	}
};




//class Method7 : public IMethod {
//
//public:
//	Method7() {
//		IMethod::method_name = MethodName::_Method7;
//	}
//	~Method7() {
//	}
//	IL void getResult(PointState& res, Vec3f& scenter, const Vec3f& v1, const Vec3f& v2, const Vec3f& v3, const Vec3f& v4, const Vec3f& r5)
//	{
//
//	}
//};
