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


		IL void make_Setting(Vec3f& v1, Vec3f& v2, Vec3f& v3, Vec3f& v4, Vec3f& r5) {
			r5 = gP;
			while (checkCompl(v1 = gP, v2 = gP, v3 = gP, v4 = gP)) {}
		}

		void RunTests(size_t n, tmList test_methods) {
			if (n > 0)
			{
				TestResult test_result;
				Vec3f test_scenter;
				
				Vec3f v1, v2, v3, v4, r5;
				make_Setting(v1, v2, v3, v4, r5);


				for (TestMethod test_method : test_methods) {

					double t1 = getCPUTime();
					for (size_t N = n; --N > 0;) {
						test_result = test_method.RunTest(v1, v2, v3, v4, r5);
					};
					double t2 = getCPUTime();
					float test_time = t2 - t1;
					_msg->showResult(test_method.getName(), test_result.point_state, test_time, test_result.circumsphere.c);
				}

			}
			else _msg->sendMsg("N error");
		}

		

};

