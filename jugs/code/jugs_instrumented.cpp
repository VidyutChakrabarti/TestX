#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>

#include "jugs.h"
#include "tester.h"

using namespace std;

extern Testharness *g_testharness;

State::State() : prevState(NULL) {
	// 0
	g_testharness->log(0);
}

State::State(State *state) : prevState(state) {
	contents = state->contents; 
	// 1
	g_testharness->log(1);
}
	
State::~State() { // 2
	g_testharness->log(2);
	for(unsigned int i = 0; i < nextStates.size(); i++) {
		delete(nextStates[i]);
		// 3
		g_testharness->log(3);
	}
	// 4
	g_testharness->log(4);
	nextStates.clear(); 
	// 5
	g_testharness->log(5);
}

bool State::contains(unsigned int value) { 
	// 6
	g_testharness->log(6);
	for(unsigned int i = 0; i < contents.size(); i++) { 
		// 7
		g_testharness->log(7);
		if (contents[i] == value) { 
			// 8
			g_testharness->log(8);
			return true;
		}
	}
	// 9
	g_testharness->log(9);
	return false;
}

vector<State *> State::getTrace() { 
	// 10
	g_testharness->log(10);
	vector<State *> trace; 
	// 11
	g_testharness->log(11);
	if(prevState) { 
		// 12
		g_testharness->log(12);
		vector<State *> ptrace = prevState->getTrace(); 
		//13
		g_testharness->log(13);
		for(unsigned int i = 0; i < ptrace.size(); i++) { 
			// 14
			g_testharness->log(14);
			trace.push_back(ptrace[i]); 
			// 15
			g_testharness->log(15);
		}
		// 16
		g_testharness->log(16);
	}
	// 17
	g_testharness->log(17);
	trace.push_back(this); 
	// 18
	g_testharness->log(18);
	return trace;
}

bool State::operator == (State& s) { 
	// 19
	g_testharness->log(19);
	if(contents == s.contents) { 
		// 20
		g_testharness->log(20);
		return true;
	}
	// 21
	g_testharness->log(21);
	return false;
}

void State::setContent(unsigned int value, unsigned int i) { 
	// 22
	g_testharness->log(22);
	contents[i] = value; 
	// 23
	g_testharness->log(23);
}

unsigned int State::getContent(unsigned int i) { 
	// 24
	g_testharness->log(24);
	return contents[i];
}

void State::print() { 
	// 25
	g_testharness->log(25);
	cout << '(';
	for(unsigned int i = 0; i < contents.size(); i++) { 
		// 26
		g_testharness->log(26);
		cout << contents[i];
		if(i < contents.size() - 1) { 
			// 27
			g_testharness->log(27);
			cout << ", ";
		}
		// 28
		g_testharness->log(28);
	}
	// 29
	g_testharness->log(29);
	cout << ')' << endl;
}

Process::Process(vector<unsigned int> c, unsigned int f) : capacities(c), final(f) {
	// 30
	g_testharness->log(30);
	for(unsigned int i = 0; i < capacities.size(); i++) { 
		// 31
		g_testharness->log(31);
		initial.contents.push_back(0); 
		// 32
		g_testharness->log(32);
	}
	// 33
	g_testharness->log(33);
}

Process::~Process() {
	for(unsigned int i = 0; i < initial.nextStates.size(); i++) { 
		// 34
		g_testharness->log(34);
		delete(initial.nextStates[i]); 
		// 35
		g_testharness->log(35);
	} 
	// 36
	g_testharness->log(36);
	initial.nextStates.clear(); 
	// 37
	g_testharness->log(37);
}
	
bool Process::isNew(State *root, State *s) { 
	// 38
	g_testharness->log(38);
	if((*root) == (*s)) { 
		// 39
		g_testharness->log(39);
		return false;
	}
	// 40
	g_testharness->log(40);
	for(unsigned int i = 0; i < root->nextStates.size(); i++) { 
		// 41
		g_testharness->log(41);
		if(isNew(root->nextStates[i], s) == false) { 
			// 42
			g_testharness->log(42);
			return false;
		}
		// 43
		g_testharness->log(43);
	}
	// 44
	g_testharness->log(44);
	return true;
}

State *Process::empty(unsigned int i, State *state) {
	State *newstate = new State(state);
	// 45
	g_testharness->log(45);
	newstate->setContent(0, i);
	// 46
	g_testharness->log(46);
	return newstate;
}

State *Process::fill(unsigned int i, State* state) {
	// 47
	g_testharness->log(47);
	State *newstate = new State(state);
	// 48
	g_testharness->log(48);
	newstate->setContent(capacities[i], i);
	// 49
	g_testharness->log(49);
	return newstate;
}

unsigned int Process::min(unsigned int a, unsigned int b) {
	// 50
	g_testharness->log(50);
	if(a < b) {
		// 51
		g_testharness->log(51);
		return a;
	}
	// 52
	g_testharness->log(52);
	return b;
}

State *Process::transfer(unsigned int i, unsigned int j, State *state) {
	// 53
	g_testharness->log(53);
	State *newstate = new State(state);
	// 54
	g_testharness->log(54);
	unsigned int amount = min(state->getContent(i), capacities[j] - state->getContent(j));
	// 55
	g_testharness->log(55);
	newstate->setContent(state->getContent(i) - amount, i);
	// 56
	g_testharness->log(56);
	newstate->setContent(state->getContent(j) + amount, j);
	// 57
	g_testharness->log(57);
	return newstate;
}

State *Process::finishUp(State *state, unsigned int final) {
	// 58
	g_testharness->log(58);
	if(state->contains(final)) {
		// 59
		g_testharness->log(59);
		State *anotherstate = state;
		// 60
		g_testharness->log(60);
		for(unsigned j = 0; j < capacities.size(); j++) {
			// 61
			g_testharness->log(61);
			if(anotherstate->getContent(j) != final) {
				// 62
				g_testharness->log(62);
				State *s = empty(j, anotherstate);
				// 63
				g_testharness->log(63);
				anotherstate->nextStates.push_back(s);
				// 64
				g_testharness->log(64);
				anotherstate = s;
				// 65
				g_testharness->log(65);
			}
			// 66
			g_testharness->log(66);
		}
		// 67
		g_testharness->log(67);
		return anotherstate;
	}
	// 68
	g_testharness->log(68);
	return state;
}

State *Process::singleStep() {
	// 69
	g_testharness->log(69);
	State *state = theQ.front();
	// 70
	g_testharness->log(70);
	for(unsigned int i = 0; i < capacities.size(); i++) {
		// 71
		g_testharness->log(71);
		State *next = empty(i, state);
		// 72
		g_testharness->log(72);
		if(isNew(&initial, next)) {
			// 73
			g_testharness->log(73);
			theQ.push(next);
			// 74
			g_testharness->log(74);
			state->nextStates.push_back(next);
			// 75
			g_testharness->log(75);
			if(next->contains(final)) {
				// 76
				g_testharness->log(76);
				return finishUp(next, final);
			}
		}
		else {
			// 77
			g_testharness->log(77);
			delete next;

		}
		// 78
		g_testharness->log(78);
	}
	// 79
	g_testharness->log(79);
	for(unsigned int i = 0; i < capacities.size(); i++) {
		// 80
		g_testharness->log(80);
		State *next = fill(i, state);
		// 81
		g_testharness->log(81);
		if(isNew(&initial, next)) {
			// 82
			g_testharness->log(82);
			theQ.push(next);
			// 83
			g_testharness->log(83);
			state->nextStates.push_back(next);
			// 84
			g_testharness->log(84);
			if(next->contains(final)) {
				// 85
				g_testharness->log(85);
				return finishUp(next, final);
			}
		}
		else {
			// 86
			g_testharness->log(86);
			delete next;
		}
		// 87
		g_testharness->log(87);
	}
	// 88
	g_testharness->log(88);
	for(unsigned int i = 0; i < capacities.size(); i++) { 
		// 89
		g_testharness->log(89);
		for(unsigned int j = 0; j < capacities.size(); j++) {
			// 90
			g_testharness->log(90);
			if(i != j) {
				// 91
				g_testharness->log(91);
				State *next = transfer(i, j, state);
				// 92
				g_testharness->log(92);
				if(isNew(&initial, next)) {
					// 93
					g_testharness->log(93);
					theQ.push(next);
					// 94
					g_testharness->log(94);
					state->nextStates.push_back(next);
					// 95
					g_testharness->log(95);
					if(next->contains(final)) {
						// 96
						g_testharness->log(96);
						return finishUp(next, final);
					}
				}
				else {
					// 97
					g_testharness->log(97);
					delete(next);
				}
				// 98
				g_testharness->log(98);
			}
			// 99
			g_testharness->log(99);
		}
		// 100
		g_testharness->log(100);
	}
	// 101
	g_testharness->log(101);
	theQ.pop();
	// 102
	g_testharness->log(102);
	return NULL;
}

void Process::go() {
	// 103
	g_testharness->log(103);
	theQ.push(&initial);
	// 104
	g_testharness->log(104);
	while(!theQ.empty()) {
		// 105
		g_testharness->log(105);
		State *state = singleStep();
		// 106
		g_testharness->log(106);
		if(state != NULL) {
			// 107
			g_testharness->log(107);
			vector<State *> trace = state->getTrace();
			// 108
			g_testharness->log(108);
			for(unsigned int i = 0; i < trace.size(); i++) {
				// 109
				g_testharness->log(109);
				trace[i]->print();
				// 110
				g_testharness->log(110);
			}
			// 111
			g_testharness->log(111);
			return;
		}
		// 112
		g_testharness->log(112);
	}
	// 113
	g_testharness->log(113);
	cout << "Couldn't find solution!" << endl;
}

Process *readInput(int argc, char **argv) {
vector<unsigned int> capacities;
unsigned int final;
// 114
	g_testharness->log(114);
	for(int i = 0; i < argc - 2; i++) { 
		// 115
		g_testharness->log(115);
		unsigned int capacity;
		sscanf(argv[i + 1], "%u", &capacity);
		// 116
		g_testharness->log(116);
		capacities.push_back(capacity);
		// 117
		g_testharness->log(117);
	}
	// 118
	g_testharness->log(118);

	sscanf(argv[argc - 1], "%u", &final);
	// 119
	g_testharness->log(119);
	return new Process(capacities, final);
}
