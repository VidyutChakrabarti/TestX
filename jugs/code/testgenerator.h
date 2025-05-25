#ifndef TESTGENERATOR_H
#define TESTGENERATOR_H

#include "tester.h"

class ParameterisedTestcase : public Testcase {
public:
	unsigned int numOfInputs;
	vector<unsigned int> inputs;
	vector<int> targets;
	ParameterisedTestcase(
			string name, Testharness *th,
			unsigned int n,
			vector<int> _targets);
};

class TestGenerator {
private:
	static const unsigned int MAX_COUNT = 100; // maximum number of attempts

	static vector<unsigned int> generateInputVector(unsigned int);
public:
	TestGenerator();

	vector<vector<unsigned int>> generate();

protected:
	virtual ParameterisedTestcase *createTestcase(Testharness *) = 0;
	vector<vector<unsigned int>> selectTestInputs(map<vector<unsigned int>, vector<int>>);
};
#endif
