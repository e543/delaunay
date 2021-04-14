#pragma once
#include "TestMethod.h"
#include <iostream>
#include "geom.h"



// Method Maur1


class Maur1 : public IMethod {

	virtual void Initialize()  override;
public:
	Maur1() {
		IMethod::method_name = MethodName::MethodMaur1;
		Initialize();
	}
	~Maur1() {
	}

	IL virtual PointState getResult(const Vec3f&, const Vec3f&, const Vec3f&, const Vec3f&, const Vec3f&)  override;
};



void Maur1::Initialize(){

}

IL PointState Maur1::getResult(const Vec3f& v1, const Vec3f& v2, const Vec3f& v3, const Vec3f& v4, const Vec3f& r5){
	Matrix55 mtr(
		v1.x, v1.y, v1.z, v1.dot(v1), 1,
		v2.x, v2.y, v2.z, v2.dot(v2), 1,
		v3.x, v3.y, v3.z, v3.dot(v3), 1,
		v4.x, v4.y, v4.z, v4.dot(v4), 1,
		r5.x, r5.y, r5.z, r5.dot(r5), 1
	);

	auto det = mtr.Determinant();
	calcResult(det);
	return  result;
}

// Method Maur2

class Maur2 : public IMethod {

	virtual void Initialize()  override;
public:
	Maur2() {
		IMethod::method_name = MethodName::MethodMaur2;
		Initialize();
	}
	~Maur2() {
	}

	virtual PointState getResult(const Vec3f&, const Vec3f&, const Vec3f&, const Vec3f&, const Vec3f&)  override;
};



void Maur2::Initialize(){

}

IL PointState Maur2::getResult(const Vec3f& v1, const Vec3f& v2, const Vec3f& v3, const Vec3f& v4, const Vec3f& r5)
{
	Matrix44 mtr(
		v1.x - r5.x, v1.y - r5.y, v1.z - r5.z, v1.GetSquaredDistance(r5),
		v2.x - r5.x, v2.y - r5.y, v2.z - r5.z, v2.GetSquaredDistance(r5),
		v3.x - r5.x, v3.y - r5.y, v3.z - r5.z, v3.GetSquaredDistance(r5),
		v4.x - r5.x, v4.y - r5.y, v4.z - r5.z, v4.GetSquaredDistance(r5)
	);

	auto det = mtr.Determinant();
	calcResult(det);
	return  result;
}


// Method3

class Method3 : public IMethod {

	virtual void Initialize()  override;
public:
	Method3() {
		IMethod::method_name = MethodName::_Method3;
		Initialize();
	}
	~Method3() {
	}

	virtual PointState getResult(const  Vec3f&, const  Vec3f&, const Vec3f&, const Vec3f&, const Vec3f&)  override;
};



void Method3::Initialize() {

}

IL PointState Method3::getResult(const Vec3f& v1, const Vec3f& v2, const Vec3f& v3, const Vec3f& v4, const Vec3f& r5)
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

	float Dx, Dy, Dz, x0, y0, z0, rad;
	Dx = mDx.Determinant();
	Dy = -mDy.Determinant();
	Dz = mDz.Determinant();
	
	x0 = Dx / (2 * a);
	y0 = Dy / (2 * a);
	z0 = Dz / (2 * a);

	rad = sqrtf(Dx * Dx + Dy * Dy + Dz * Dz - 4 * a * c) / (2 * fabs(a));

	Vec3f scenter(x0, y0, z0);
	_msg->sendMsg(std::to_string(x0) + " " + std::to_string(y0) + " " + std::to_string(z0));
	float distant = r5.GetDistance(scenter);

	calcResult(rad - distant);
	return  result;
}




// Method4


class Method4 : public IMethod {

	virtual void Initialize()  override;
public:
	Method4() {
		IMethod::method_name = MethodName::_Method4;
		Initialize();
	}
	~Method4() {
	}

	virtual PointState getResult(const Vec3f&, const  Vec3f&, const  Vec3f&, const  Vec3f&, const  Vec3f&)  override;
};



void Method4::Initialize() {

}

IL PointState Method4::getResult(const Vec3f& v1, const Vec3f& v2, const Vec3f& v3, const Vec3f& v4, const Vec3f& r5)
{
	Vec3f ccenter = CalcCircleBarCenter(v1, v2, v3);
	float rad = v1.GetDistance(ccenter);


	Vec3f pd = projPointPlane(v1, v2, v3, v4);
	Vec3f S, T;
	LineCircleIntrPoints(S, T, ccenter, rad, pd);

	Vec3f scenter = CalcCircleBarCenter(S, T, v4);


	float distant = r5.GetDistance(scenter);
	rad = scenter.GetDistance(v4);
	calcResult(rad - distant);

	return  result;
}

// Method5


class Method5 : public IMethod {

	virtual void Initialize()  override;
public:
	Method5() {
		IMethod::method_name = MethodName::_Method5;
		Initialize();
	}
	~Method5() {
	}

	virtual PointState getResult(const Vec3f&, const  Vec3f&, const  Vec3f&, const  Vec3f&, const  Vec3f&)  override;
};



void Method5::Initialize() {

}

IL PointState Method5::getResult(const Vec3f& v1, const Vec3f& v2, const Vec3f& v3, const Vec3f& v4, const Vec3f& r5)
{

	Circle ccircle;
	CalcCircleBarCenterDot(ccircle, v1, v2, v3);


	Vec3f pd = projPointPlane(v1, v2, v3, v4);
	Vec3f S, T;
	LineCircleIntrPoints(S, T, ccircle.c, ccircle.radius, pd);

	Circle scircle;
	CalcCircleBarCenterDot(scircle, S, T, v4);
	
	float distant = r5.GetDistance(scircle.c);
	calcResult(scircle.radius - distant);

	return  result;
}


// Method6

class Method6 : public IMethod {

	virtual void Initialize()  override;
public:
	Method6() {
		IMethod::method_name = MethodName::_Method6;
		Initialize();
	}
	~Method6() {
	}

	virtual PointState getResult(const Vec3f&, const Vec3f&, const Vec3f&, const Vec3f&, const Vec3f&)  override;
};



void Method6::Initialize() {

}

IL PointState Method6::getResult(const Vec3f& v1, const Vec3f& v2, const Vec3f& v3, const Vec3f& v4, const Vec3f& r5)
{

	Circle ccircle;
	CalcCircleBarCenterDot(ccircle,v1,v2,v3);
	_msg->sendMsg(std::to_string(ccircle.c.x) + " " + std::to_string(ccircle.c.y) + " " + std::to_string(ccircle.c.z));

	return  result;
}
