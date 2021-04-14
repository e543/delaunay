#pragma once
#include "Methods.h";
#include "ConsoleHelper.h";
#include <list>
#define tmList std::list<TestMethod>

class TestsRunner
{
	IMessage* _msg = nullptr;
	PointState result = Error;
	std::string str;
	public: 
		TestsRunner(IMessage* msg) : _msg(msg) {
			_msg->Greeting();
		}
		~TestsRunner() {
			if (_msg) {
				_msg->Parting();
				delete _msg;
			}
		}


		

		void RunTests(size_t n, tmList test_methods) {


			if (n > 0)
			{
				Vec3f test_scenter;
				Vec3f v1, v2, v3, v4, r5;
				r5 = Vec3f(rF, rF, rF);
				while (checkCompl(v1, v2, v3, v4)) {
					v1 = Vec3f(rF, rF, rF);
					v2 = Vec3f(rF, rF, rF);
					v3 = Vec3f(rF, rF, rF);
					v4 = Vec3f(rF, rF, rF);
				}


				for (TestMethod tm : test_methods) {

					double t1 = getCPUTime();
					for (size_t N = n; --N > 0;) {
						tm.RunTest(result, test_scenter, v1, v2, v3, v4, r5);
					};
					double t2 = getCPUTime();
					float test_time = t2 - t1;
					_msg->showResult(tm.getName(), result, test_time, test_scenter);
					tm.RunTest(result, test_scenter, v1, v2, v3, v4, r5);
					result = Error;
				}
				_msg->showPoints(v1,v2,v3,v4,r5);

			}
			else _msg->sendMsg("N error");
		}

		

};

