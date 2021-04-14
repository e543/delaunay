#pragma once
#include "IMessage.h"
#include "Methods.h"
#include <iostream>
#define to_str std::to_string


class ConsoleHelper : public IMessage
{
	std::string str;
public:
	ConsoleHelper(){}
	virtual void Greeting() const override;
	virtual void sendMsg(std::string) const override;
	virtual std::string getMsg() const override;
	virtual void Parting() const override;
	virtual void showResult(MethodName methodname, PointState result, float time, Vec3f scenter);
	void add_result(PointState);
	void add_methodName(MethodName);
};


void ConsoleHelper::Greeting()  const
{
	std::cout << "\tHello!\n" << std::endl;
	sendMsg("Name:\t\tState:\t\tTime:\t\tSphere center:");
	sendMsg("--------------------------------------------------------------------------------------------");
}

void ConsoleHelper::sendMsg(std::string str) const
{
	std::cout << std::fixed << "\t" << str << std::endl;
}

std::string ConsoleHelper::getMsg() const
{
	std::string str;
	std::cin >> str;
	std::cout << "Get: " << str << std::endl;
	return str;
}

void ConsoleHelper::Parting() const
{
	sendMsg("--------------------------------------------------------------------------------------------");
	std::cout << "\n\tGood Bye!" << std::endl;
}

void ConsoleHelper::showResult(MethodName methodname, PointState result, float time, Vec3f scenter) {
	add_methodName(methodname);
	add_result(result);
	if (result != Error)
		str += (to_str(time) + " sec" +
			"\tx: " + to_str(scenter.x) +
			"\ty: " + to_str(scenter.y) +
			"\tz: " + to_str(scenter.z));
	sendMsg(str);
	str.clear();
}

void ConsoleHelper::add_result(PointState result) {
	
	switch (result)
	{
	case (InSphere):
		str += "In sphere\t";
		break;
	case (OutOfSphere):
		str += "Out of Sphere\t";
		break;
	case (OnSphere):
		str += "On Sphere\t";
		break;
	case (Error):
		str += "State error\t";
		break;
	default:
		str += "State error\t";
		break;
	}

}

void ConsoleHelper::add_methodName(MethodName mn_res) {
	if (mn_res)
	{
		switch (mn_res)
		{
		case (MethodMaur1):
			str += "Maur1\t\t";
			break;
		case (MethodMaur2):
			str += "Maur2\t\t";
			break;
		case (_Method3):
			str += "Method3\t\t";
			break;
		case (_Method4):
			str += "Method4\t\t";
			break;
		case (_Method5):
			str += "Method5\t\t";
			break;
		case (_Method6):
			str += "Method6\t\t";
			break;
		case (_Method7):
			str += "Method7\t\t";
			break;
		case (UNDEF):
			str += "Name error!\t\t";
			break;
		default:
			str += "Name error!\t\t";
			break;
		}
	}
}