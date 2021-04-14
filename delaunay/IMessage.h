#pragma once
#include <string>
struct IMessage
{
	virtual ~IMessage() {}
	virtual void Greeting() const = 0;
	virtual void sendMsg(std::string) const = 0;
	virtual std::string getMsg() const = 0;
	virtual void Parting() const = 0;
	virtual void showResult(MethodName methodname, PointState result, float time, Vec3f scenter) = 0;
	virtual void showPoints(const Vec3f&, const Vec3f&, const Vec3f&, const Vec3f&, const Vec3f&) = 0;
};

