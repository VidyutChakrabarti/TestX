#include<iostream>
#include<vector>
#include<map>
#include<string>
#include <bits/stdc++.h>

#include "tester.h"

using namespace std;

Testcase::Testcase(string n, Testharness *th) : name(n), testharness (th) {
	testharness->addTestcase(this);
}

void Testcase::execute() {
	testharness->currentTestcase = name;
	run();
}

Testharness::Testharness() : currentTestcase("None") {}

void Testharness:: addTestcase(Testcase* t) {
	testcases.push_back(t);
}

void Testharness::execute() {
	for(int i = 0; i < testcases.size(); i++) {
		testcases[i]->execute();
	}
}

void Testharness::log(int loc) {
	if(coverage.find(currentTestcase) == coverage.end()) {
		coverage[currentTestcase] = new vector<int>();
	}
	if(find_in_intlist(loc, *(coverage[currentTestcase])) == false) {
	  coverage[currentTestcase]->push_back(loc);
	}
}

bool Testharness::find_in_intlist(int v, vector<int> list) {
  for(int i = 0; i < list.size(); i++) {
    if(v == list[i]) {
	    return true;
    }
  }
  return false;
}

string Testharness::intlist_to_string(vector<int> *list) {
	string s = "";
	for(int i = 0; i < list->size(); i++) {
		string str = to_string((*list)[i]);
		s += ", " + str;
	}
	return s;
}

string Testharness::intlist_to_string(vector<unsigned int> *list) {
	string s = "";
	for(int i = 0; i < list->size(); i++) {
		string str = to_string((*list)[i]);
		s += ", " + str;
	}
	return s;
}

vector<int> Testharness::getCoverage() {
	vector<int> covered_locations;
	for(std::map<string,vector<int>*>::iterator it = coverage.begin(); it != coverage.end(); ++it) {
		sort(it->second->begin(), it->second->end());
		cout << it->first << " : " << intlist_to_string(it->second) << endl;
		for(auto i : *(it->second)) {
			if(find_in_intlist(i, covered_locations) == false) {
				covered_locations.push_back(i);
			}
		}
	}
	sort(covered_locations.begin(), covered_locations.end());
	return covered_locations;

}

void Testharness::printCoverage() {
	cout << "Coverage: " << endl;
	vector<int> covered_locations = getCoverage();

	cout << "covered locations : " << 
		intlist_to_string(&covered_locations) << endl;
	vector<int> uncov;
	for(int i = 0; i <= 119; i++) {
          if(find_in_intlist(i, covered_locations) == false) {
		  uncov.push_back(i);
	  }
	}
	cout << "not covered : " <<
		intlist_to_string(&uncov) << endl;

}

Testharness *g_testharness;
