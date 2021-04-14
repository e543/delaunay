#pragma once
struct ITest
{
	virtual ~ITest() {}
	virtual void RunTest(PointState&, Vec3f& srad, const  Vec3f&, const  Vec3f&, const Vec3f&, const Vec3f&, const Vec3f&) const = 0;
};