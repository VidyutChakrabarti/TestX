#include <iostream>
#include <string>

#include "tester.h"
#include "jugs.h"

using namespace std;
// Methods called:
// 	State::State()
class Testcase1 : public Testcase {
public:
	Testcase1() : Testcase("Testcase1", g_testharness) {}
protected:
	void run() {
	  State s;
	}
};

// Methods called:
// 	State::State()
// 	State::State(State *)
// 	State::print()
class Testcase2 : public Testcase {
public:
	Testcase2() : Testcase("Testcase2", g_testharness) {}
protected:
	void run() {
	  State s;
	  State s1(&s);
	  s.print();
	}
};

// Methods called:
// 	State::State()
// 	State::State(State *)
// 	State::setContent(int, int)
// 	State::getContent()
// 	State::operator==()
class Testcase3 : public Testcase {
public:
	Testcase3() : Testcase("Testcase3", g_testharness) {}
protected:
	void run() {
	  State s;
	  State s1(&s);
	  s == s;
	  s.contents.push_back(0);
	  s.contents.push_back(0);
	  s.setContent(1, 1);
	  s == s1;
	  int c = s.getContent(1);
	  
	}
};

// Methods called:
// 	Process::Process
class Testcase4 : public Testcase {
public:
	Testcase4() : Testcase("Testcase4", g_testharness) {}
protected:
	void run() {
		vector<unsigned int> c;
		c.push_back(1u);
		c.push_back(2u);
		Process P1(c, 1u); 
	}
};

// Methods called:
// 	Process::Process
// 	Process::empty
// 	Process::fill
// 	Process::transfer
class Testcase5 : public Testcase {
public:
	Testcase5() : Testcase("Testcase5", g_testharness) {}
protected:
	void run() {
		vector<unsigned int> c;
		c.push_back(1u);
		c.push_back(2u);
		Process P1(c, 1u);
		State * s1 = P1.empty(1, &(P1.initial));	
		State * s2 = P1.fill(0, s1);	
		State * s3 = P1.transfer(1, 2, s2);
		cout << "isNew = " << P1.isNew(&(P1.initial), s3) << endl;
	}
};

// Methods called:
// 	Process::Process
// 	Process::min
class Test_min : public Testcase {
public:
	Test_min() : Testcase("Test_min", g_testharness) {}
protected:
	void run() {
		vector<unsigned int> c;
		c.push_back(1u);
		c.push_back(2u);
		Process P1(c, 1u);
		P1.min(1, 2);
		P1.min(2, 1);
	}
};

// Methods called:
// 	Process::Process
// 	Process::singleStep
class Test_singleStep1 : public Testcase {
public:
	Test_singleStep1() : Testcase("Test_singleStep1", g_testharness) {}
protected:
	void run() {
		vector<unsigned int> c;
		c.push_back(10u);
		c.push_back(2u);
		Process P1(c, 4u);
		P1.go();
	}
};

// Methods called:
// 	Process::Process
// 	Process::go
class Test_go1 : public Testcase {
public:
	Test_go1() : Testcase("Test_go1", g_testharness) {}
protected:
	void run() {
		vector<unsigned int> c;
		c.push_back(10u);
		c.push_back(2u);
		Process P1(c, 4u);
		P1.theQ.push(&(P1.initial));
		P1.singleStep();
	}
};


int main() {

	g_testharness = new Testharness();
	Testcase1 t1;
	Testcase2 t2;
	Testcase3 t3;
	Testcase4 t4;
	Testcase5 t5;
	Test_min t_min;
	Test_singleStep1 t_singleStep1;
	Test_go1 t_go1;
	g_testharness->execute();
	delete(g_testharness);
}
