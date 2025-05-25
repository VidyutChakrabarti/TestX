#include "jugs.h"
#include "testgenerator.h"
#include "testgen_main.h"

using namespace std;

PTC_min1::PTC_min1(string name, Testharness *th) :
	ParameterisedTestcase(name, th, 5, vector<int>{50, 51, 52}) {}

void PTC_min1::run() {
	vector<unsigned int> c;
	c.push_back(inputs[0]);
	c.push_back(inputs[1]);
	Process P1(c, inputs[2]);
	P1.min(inputs[3], inputs[4]);
}

TestGenerator_min::TestGenerator_min() {}

ParameterisedTestcase * TestGenerator_min::createTestcase(Testharness *th) {
	return new PTC_min1("PTC_min1", th);
}

PTC_go::PTC_go(string name, Testharness *th) :
	ParameterisedTestcase(name, th, 3, 
		vector<int>{103, 104, 105, 106,
			107, 108, 109, 110,
			111, 112, 113}) {}

void PTC_go::run() {
	vector<unsigned int> c;
	c.push_back(inputs[0]);
	c.push_back(inputs[1]);
	Process P1(c, inputs[2]);
	P1.go();
}

TestGenerator_go::TestGenerator_go() {}

ParameterisedTestcase * TestGenerator_go::createTestcase(Testharness *th) {
	return new PTC_go("PTC_go", th);
}

PTC_singleStep::PTC_singleStep(string name, Testharness *th) :
	ParameterisedTestcase(name, th, 3, 
		vector<int>{69, 70, 71, 72, 73,
			74, 75, 76, 77, 78,
			79, 80, 81, 82, 83,
			84, 85, 86, 87, 88,
			89, 90, 91, 92, 93,
			94, 95, 96, 97, 98,
			99, 100, 101, 102}) {}

void PTC_singleStep::run() {
	vector<unsigned int> c;
	c.push_back(inputs[0]);
	c.push_back(inputs[1]);
	Process P1(c, inputs[2]);
	P1.theQ.push(&(P1.initial));
	P1.singleStep();
}

TestGenerator_singleStep::TestGenerator_singleStep() {}

ParameterisedTestcase * TestGenerator_singleStep::createTestcase(Testharness *th) {
	return new PTC_singleStep("PTC_singleStep", th);
}

int main() {
	TestGenerator_min tg;
	vector<vector <unsigned int>> ti = tg.generate();
	for(unsigned int i = 0; i < ti.size(); i++) {
		cout << "test input = " << Testharness::intlist_to_string(&ti[i]) << endl;
	}

	TestGenerator_go tg_go;
	vector<vector <unsigned int>> ti_go = tg_go.generate();
	for(unsigned int i = 0; i < ti_go.size(); i++) {
		cout << "test input = " << Testharness::intlist_to_string(&ti_go[i]) << endl;
	}
	TestGenerator_singleStep tg_singleStep;
	vector<vector <unsigned int>> ti_singleStep = tg_singleStep.generate();
	for(unsigned int i = 0; i < ti_singleStep.size(); i++) {
		cout << "test input = " << Testharness::intlist_to_string(&ti_singleStep[i]) << endl;
	}
}
