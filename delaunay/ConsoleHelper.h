#pragma once
#include "IMessage.h"
#include "Methods.h"
#include <iostream>
#define to_str std::to_string


class ConsoleHelper : public IMessage
{
	std::string str;
public:
	ConsoleHelper(){

	}
	virtual bool Greeting() const override;
	virtual bool sendMsg(std::string) const override;
	virtual std::string getMsg() const override;
	virtual bool Parting() const override;
	virtual void showResult(MethodName methodname, PointState result, float time, Vec3f scenter);
	void add_result(PointState);
	void add_methodName(MethodName);
};


bool ConsoleHelper::Greeting()  const
{
	std::cout << "\tHello!\n" << std::endl;
	sendMsg("Name:\t\tState:\t\tTime:\t\tSphere center:");
	sendMsg("--------------------------------------------------------------------------");
	return true;
}

bool ConsoleHelper::sendMsg(std::string str) const
{
	std::cout << std::fixed << "\t" << str << std::endl;
	return true;
}

std::string ConsoleHelper::getMsg() const
{
	std::string str;
	std::cin >> str;
	std::cout << "Get: " << str << std::endl;
	return str;
}

bool ConsoleHelper::Parting() const
{
	sendMsg("--------------------------------------------------------------------------");
	std::cout << "\n\tGood Bye!" << std::endl;
	return true;
}

void ConsoleHelper::showResult(MethodName methodname, PointState result, float time, Vec3f scenter) {
	add_methodName(methodname);
	add_result(result);
	if (result != Error)
		str += (to_str(time) + " sec\t" +
			"x: " + to_str(scenter.x) +
			" y: " + to_str(scenter.y) +
			" z: " + to_str(scenter.z));
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