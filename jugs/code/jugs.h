#ifndef JUGS_H
#define JUGS_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class State {
public:
	State * prevState;
	vector<unsigned int> contents;
	vector<State *> nextStates;

	State();
	State(State *);
	~State();
	bool contains(unsigned int);
	vector<State *> getTrace();
	bool operator == (State&);
	void setContent(unsigned int, unsigned int);
	unsigned int getContent(unsigned int);
	void print();
};

class Process {
public:
	const vector<unsigned int> capacities;
	queue<State *> theQ;
	State initial;
	const unsigned int final;

	Process(vector<unsigned int>, unsigned int);
	~Process();
	bool isNew(State *, State *);
	State *empty(unsigned int, State *);
	State *fill(unsigned int, State*);
	unsigned int min(unsigned int, unsigned int);
	State *transfer(unsigned int, unsigned int, State *);
	State *finishUp(State *, unsigned int);
	State *singleStep();
	void go();
};

Process *readInput(int, char **);
#endif
