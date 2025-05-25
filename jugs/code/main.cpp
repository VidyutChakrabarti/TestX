#include "jugs.h"

void test_min() {
	cout << min(1, 2) << endl;
	cout << min(2, 1) << endl;
	cout << min(10, 10) << endl;
}

/*
void test_transfer2() {
	capacities.push_back(30);
	capacities.push_back(35);
	queue<State *> theQ;
	State *s1 = new State(theQ);
	s1->contents.push_back(0);
	s1->contents.push_back(0);
	s1->setContent(10, 0);
	s1->setContent(30, 1);
	
	State * s2 = transfer(0, 1, s1);
	s2->print();
	capacities.clear();
}

void test_transfer1() {
	capacities.clear();
	capacities.push_back(30);
	capacities.push_back(50);
	queue<State *> theQ;
	State *s1 = new State(theQ);
	s1->contents.push_back(0);
	s1->contents.push_back(0);
	s1->setContent(10, 0);
	s1->setContent(20, 1);
	
	State * s2 = transfer(0, 1, s1);
	s2->print();
	capacities.clear();
}

void test_go(int argc, char** argv) {
	readInput(argc, argv);
	cout << capacities.size() << " jugs." << endl;
	for(unsigned int i = 0; i < capacities.size(); i++) {
		cout << capacities[i] << endl;
		initial.contents.push_back(0);

	}
	cout << "initial = ";
	for(unsigned int i = 0; i < capacities.size(); i++) {
		cout << initial.getContent(i) << " ";
	}
	cout << endl;
	
	cout << "final = " << final;
	go();
}
*/

int main(int argc, char **argv) {
//	test_min();
//	test_transfer1();
//	test_transfer2();

	Process *proc = readInput(argc, argv);
	proc->go();
	delete(proc);

	return 0;
}
