#ifndef TESTER
#define TESTER

#include<vector>
#include<map>
#include<string>

using namespace std;
class Testharness;
class Testcase {
public:
	const string name;
	Testharness *testharness;
	Testcase(string n, Testharness *th);
	void execute();
protected:
	virtual void run() = 0;
};

class Testharness {
public:
	Testharness();
	vector<Testcase*> testcases;
	string currentTestcase;
	map<string, vector<int> *> coverage; // map: test case -> set of lines

	void addTestcase(Testcase* t);
	void execute();
	void log(int loc);
	void printCoverage();
	static bool find_in_intlist(int v, vector<int>);
	static string intlist_to_string(vector<int> *);
	static string intlist_to_string(vector<unsigned int> *);
	vector<int> getCoverage();
};

extern Testharness *g_testharness;
#endif
