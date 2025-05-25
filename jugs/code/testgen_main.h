#ifndef TESTGEN_MAIN
#define TESTGEN_MAIN

class PTC_min1 : public ParameterisedTestcase {
public:
	PTC_min1(string name, Testharness *th);

protected:
	virtual void run();
};

class TestGenerator_min : public TestGenerator {
public:
	TestGenerator_min(); 
protected:
	virtual ParameterisedTestcase *createTestcase(Testharness *);
};

class PTC_go : public ParameterisedTestcase {
public:
	PTC_go(string name, Testharness *th);

protected:
	virtual void run();
};

class TestGenerator_go : public TestGenerator {
public:
	TestGenerator_go(); 
protected:
	virtual ParameterisedTestcase *createTestcase(Testharness *);
};

class PTC_singleStep : public ParameterisedTestcase {
public:
	PTC_singleStep(string name, Testharness *th);

protected:
	virtual void run();
};

class TestGenerator_singleStep : public TestGenerator {
public:
	TestGenerator_singleStep(); 
protected:
	virtual ParameterisedTestcase *createTestcase(Testharness *);
};



#endif
