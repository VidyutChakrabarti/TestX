#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>

#include "jugs.h"

using namespace std;


State::State() : prevState(NULL) {
}

State::State(State *state) : prevState(state) {
	contents = state->contents; 
}
	
State::~State() { 
	for(unsigned int i = 0; i < nextStates.size(); i++) {
		delete(nextStates[i]);
	}
	nextStates.clear(); 
}

bool State::contains(unsigned int value) { 
	for(unsigned int i = 0; i < contents.size(); i++) { 
		if (contents[i] == value) { 
			return true;
		}
	}
	return false;
}

vector<State *> State::getTrace() { 
	vector<State *> trace; 
	if(prevState) { 
		vector<State *> ptrace = prevState->getTrace(); 
		for(unsigned int i = 0; i < ptrace.size(); i++) { 
			trace.push_back(ptrace[i]); 
		}
	}
	trace.push_back(this); 
	return trace;
}

bool State::operator == (State& s) { 
	if(contents == s.contents) { 
		return true;
	}
	return false;
}

void State::setContent(unsigned int value, unsigned int i) { 
	contents[i] = value; 
}

unsigned int State::getContent(unsigned int i) { 
	return contents[i];
}

void State::print() { 
	cout << '(';
	for(unsigned int i = 0; i < contents.size(); i++) { 
		cout << contents[i];
		if(i < contents.size() - 1) { 
			cout << ", ";
		}
	}
	cout << ')' << endl;
}

Process::Process(vector<unsigned int> c, unsigned int f) : capacities(c), final(f) {
	for(unsigned int i = 0; i < capacities.size(); i++) { 
		initial.contents.push_back(0); 
	}
}

Process::~Process() {
	for(unsigned int i = 0; i < initial.nextStates.size(); i++) { 
		delete(initial.nextStates[i]); 
	} 
	initial.nextStates.clear(); 
}
	
bool Process::isNew(State *root, State *s) { 
	if((*root) == (*s)) { 
		return false;
	}
	for(unsigned int i = 0; i < root->nextStates.size(); i++) { 
		if(isNew(root->nextStates[i], s) == false) { 
			return false;
		}
	}
	return true;
}

State *Process::empty(unsigned int i, State *state) {
	State *newstate = new State(state);
	newstate->setContent(0, i);
	return newstate;
}

State *Process::fill(unsigned int i, State* state) {
	State *newstate = new State(state);
	newstate->setContent(capacities[i], i);
	return newstate;
}

unsigned int Process::min(unsigned int a, unsigned int b) {
	if(a < b) {
		return a;
	}
	return b;
}

State *Process::transfer(unsigned int i, unsigned int j, State *state) {
	State *newstate = new State(state);
	unsigned int amount = min(state->getContent(i), capacities[j] - state->getContent(j));
	newstate->setContent(state->getContent(i) - amount, i);
	newstate->setContent(state->getContent(j) + amount, j);
	return newstate;
}

State *Process::finishUp(State *state, unsigned int final) {
	if(state->contains(final)) {
		State *anotherstate = state;
		for(unsigned j = 0; j < capacities.size(); j++) {
			if(anotherstate->getContent(j) != final) {
				State *s = empty(j, anotherstate);
				anotherstate->nextStates.push_back(s);
				anotherstate = s;
			}
		}
		return anotherstate;
	}
	return state;
}

State *Process::singleStep() {
	State *state = theQ.front();
	for(unsigned int i = 0; i < capacities.size(); i++) {
		State *next = empty(i, state);
		if(isNew(&initial, next)) {
			theQ.push(next);
			state->nextStates.push_back(next);
			if(next->contains(final)) {
				return finishUp(next, final);
			}
		}
		else {
			delete next;

		}
	}
	for(unsigned int i = 0; i < capacities.size(); i++) {
		State *next = fill(i, state);
		if(isNew(&initial, next)) {
			theQ.push(next);
			state->nextStates.push_back(next);
			if(next->contains(final)) {
				return finishUp(next, final);
			}
		}
		else {
			delete next;
		}
	}
	for(unsigned int i = 0; i < capacities.size(); i++) { 
		for(unsigned int j = 0; j < capacities.size(); j++) {
			if(i != j) {
				State *next = transfer(i, j, state);
				if(isNew(&initial, next)) {
					theQ.push(next);
					state->nextStates.push_back(next);
					if(next->contains(final)) {
						return finishUp(next, final);
					}
				}
				else {
					delete(next);
				}
			}
		}
	}
	theQ.pop();
	return NULL;
}

void Process::go() {
	theQ.push(&initial);
	while(!theQ.empty()) {
		State *state = singleStep();
		if(state != NULL) {
			vector<State *> trace = state->getTrace();
			for(unsigned int i = 0; i < trace.size(); i++) {
				trace[i]->print();
			}
			return;
		}
	}
	cout << "Couldn't find solution!" << endl;
}

Process *readInput(int argc, char **argv) {
vector<unsigned int> capacities;
unsigned int final;
	for(int i = 0; i < argc - 2; i++) { 
		unsigned int capacity;
		sscanf(argv[i + 1], "%u", &capacity);
		capacities.push_back(capacity);
	}

	sscanf(argv[argc - 1], "%u", &final);
	return new Process(capacities, final);
}
