#include<random>
#include <bits/stdc++.h>

#include "jugs.h"
#include "tester.h"
#include "testgenerator.h"

using namespace std;

ParameterisedTestcase::ParameterisedTestcase(
		string name, Testharness *th,
		unsigned int n,
		vector<int> _targets) :
	Testcase(name, th), 
	numOfInputs(n), targets(_targets) {}	

vector<unsigned int> TestGenerator::generateInputVector(unsigned int n) {
	vector<unsigned int> inputs;
	for(unsigned int i = 0;	i < n; i++) {
		inputs.push_back(rand() % 50);
	}
	return inputs;
}

TestGenerator::TestGenerator() {}

vector<vector<unsigned int>> TestGenerator::generate() {
	unsigned int count = 0u;
	map<vector<unsigned int>, vector<int>> cov_map;
		// map: test input -> covered lines
	vector<int> coveredTargets;
	while(count < MAX_COUNT) {
		Testharness testharness;
		g_testharness = &testharness;
		ParameterisedTestcase *testcase =
			createTestcase(&testharness);
		testcase->inputs = TestGenerator::generateInputVector(testcase->numOfInputs);
		testharness.execute();
		cov_map[testcase->inputs] = *(testharness.coverage[testcase->name]);
		sort(cov_map[testcase->inputs].begin(), cov_map[testcase->inputs].end());
		vector<int> coveredLocations = testharness.getCoverage();
		for(int i = 0; i < coveredLocations.size(); i++) {
			if(Testharness::find_in_intlist(coveredLocations[i], testcase->targets)) {
				if(!Testharness::find_in_intlist(coveredLocations[i], coveredTargets)) {
					coveredTargets.push_back(coveredLocations[i]);
				}
			}
		}
		if(coveredTargets.size() == testcase->targets.size()) {
			delete(testcase);
			break;
		}
		count++;
		delete(testcase);
	}
	return selectTestInputs(cov_map);
}

static vector<int> setunion(vector<int> s1, vector<int> s2) {
	vector<int> s = s1;
	for(auto x : s2) {
		if(Testharness::find_in_intlist(x, s) == false) {
			s.push_back(x);
		}
	}
	sort(s.begin(), s.end());
	return s;
}

static vector<int> setintersect(vector<int> s1, vector<int> s2) {
	vector<int> s;
	for(auto x : s2) {
		if(Testharness::find_in_intlist(x, s1) == true) {
			s.push_back(x);
		}
	}
	sort(s.begin(), s.end());
	return s;
}

class comparison {
private:
	vector<int> targets;
	vector<int> coverage;
	map<vector<unsigned int>, vector<int>> cov_map;
public:
	comparison(
		vector<int> t,
		vector<int> c,
		map<vector<unsigned int>, vector<int>> cm
	):
		targets(t), coverage(c), cov_map(cm) {}

	bool isNewCoverage(int lineNum) {
		return Testharness::find_in_intlist(lineNum, coverage) == false &&
			Testharness::find_in_intlist(lineNum, targets);
	}

	bool operator()(vector<unsigned int> x, vector<unsigned int> y) {
		vector<int> xcov = cov_map[x];
		vector<int> ycov = cov_map[y];
		unsigned int xn;
		for(auto i : xcov) {
			if(isNewCoverage(i)) {
				xn++;
			}
		}
		unsigned int yn;
		for(auto i : ycov) {
			if(isNewCoverage(i)) {
				yn++;
			}
		}
		return xn < yn;
	}
};

vector<vector<unsigned int>> TestGenerator::selectTestInputs(map<vector<unsigned int>, vector<int>> cov_map) {
	
	Testharness testharness;
	ParameterisedTestcase *testcase = createTestcase(&testharness); // to be used
		//  just for accessing the targets.
	vector<int> targets = testcase->targets;
	delete(testcase);
	vector<int> coverage;
	vector<vector<unsigned int>> selectedTestInputs;
	while(coverage.size() != targets.size()) {
		// In the testInputs list, select the test input which covers the largest
		// number of additional targets w.r.t. the current set of covered targets.
		vector<vector<unsigned int>> testInputs;
		map<vector<unsigned int>,vector<int>>::iterator it = cov_map.begin();
		for(; it != cov_map.end(); ++it) {
			vector<unsigned int> first = it->first;
			vector<int> second = it->second;
			if(find(selectedTestInputs.begin(),
					selectedTestInputs.end(),
					it->first) == selectedTestInputs.end()) {
				testInputs.push_back(it->first);
			}
		}
		comparison comp(targets, coverage, cov_map);
		sort(testInputs.begin(), testInputs.end(), comp);
		if(testInputs.size() != 0) {

			vector<unsigned int> testInput = testInputs[0];
			selectedTestInputs.push_back(testInput);
			coverage = setunion(coverage, setintersect(cov_map[testInput], targets));
		}
		else {
			break;
		}
	}
	return selectedTestInputs;
}
