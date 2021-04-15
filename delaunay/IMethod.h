#pragma once
#include "geom.h"
#include "MethodName.h"
#include "PointState.h"
#include "ITest.h"

struct IMethod
{
	MethodName method_name = UNDEF;
	PointState state_res = Error;
	TestResult test_res;
	PointState getState() {
		return state_res;
	};

	IMethod() {};
	virtual ~IMethod() {};
	IL virtual TestResult getResult(const  Vec3f&, const  Vec3f&, const Vec3f&, const Vec3f&, const Vec3f&) = 0;
protected:
	IL void calcResult(float val) {
		if (val >= eps) {
			state_res = InSphere;
		}
		else if (val < -eps) {
			state_res = OutOfSphere;
		}
		else {
			state_res = OnSphere;
		}
	};
	MethodName getName() {
		return method_name;
	};
};