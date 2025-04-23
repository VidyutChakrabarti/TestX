#ifndef LLTG
#define LLTG

#include <set>
#include "testgenerator.h"
#include "linkedlist.h"

using namespace std;
using namespace testgenerator;

class Lltg : public TestGenerator<LinkedList *> {
    private:
        unsigned int count = 0;
        static const unsigned int MAXTESTCOUNT;
    protected:
        void callPUT(LinkedList *) = 0;
    public:
        virtual ~Lltg();
        virtual LinkedList *generateTest();
        virtual void deleteTest(LinkedList *);
        virtual bool toContinue();
        virtual string toString(LinkedList *);
        virtual string toJSON(LinkedList *);
        virtual LinkedList *readFromJSONFile(string);
};

class Lltg_reverseLinkedList : public Lltg {
    protected:
        void callPUT(LinkedList *);
};

#endif
