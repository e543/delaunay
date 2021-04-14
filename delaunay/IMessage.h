#pragma once
#include <string>
struct IMessage
{
	virtual ~IMessage() {}
	virtual bool Greeting() const = 0;
	virtual bool sendMsg(std::string) const = 0;
	virtual std::string getMsg() const = 0;
	virtual bool Parting() const = 0;
	virtual void showResult(MethodName methodname, PointState result, float time, Vec3f scenter) = 0;
};

