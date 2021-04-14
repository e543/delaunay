#pragma once
#include "TestsRunner.h"
#define TM TestMethod

class RunHelper
{
public:
	RunHelper() {
		srand(time(NULL));
		ConsoleHelper* ch = new ConsoleHelper();
		TestsRunner tr(ch);

		tmList tml = setTests(ch);
		tr.RunTests(1000000,tml);
	}

	tmList setTests(IMessage* rhmsg) {
		tmList* curtml = new tmList();
		curtml->push_back(new Maur1());
		curtml->push_back(new Maur2());
		curtml->push_back(new Method3());
		curtml->push_back(new Method4());
		curtml->push_back(new Method5());
		curtml->push_back(new Method6());

		return* curtml;
	}

	~RunHelper() {}

};
