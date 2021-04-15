#pragma once
#include "geom.h"
#include "PointState.h"

struct TestResult {
	Sphere circumsphere;
	PointState point_state;
};

struct ITest{
	virtual ~ITest() {}
	virtual TestResult RunTest(const  Vec3f&, const  Vec3f&, const Vec3f&, const Vec3f&, const Vec3f&) const = 0;
};
