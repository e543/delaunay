#pragma once
#include "geom.h"
#include "IMessage.h"

struct IMethod
{
	MethodName method_name = UNDEF;
	PointState result = Error;
	PointState getState() {
		return result;
	};

	IMethod() {};
	virtual ~IMethod() {};
	IL virtual void getResult(PointState& , Vec3f& scenter, const  Vec3f&, const  Vec3f&, const Vec3f&, const Vec3f&, const Vec3f&) = 0;
protected:
	IL void calcResult(float val) {
		if (val >= eps) {
			result = InSphere;
		}
		else if (val < -eps) {
			result = OutOfSphere;
		}
		else {
			result = OnSphere;
		}
	};
	MethodName getName() {
		return method_name;
	};
};