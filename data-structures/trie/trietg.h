#ifndef TRIETG
#define TRIETG

#include <set>
#include "testgenerator.h"
#include "trie.h"

using namespace std;
using namespace testgenerator;

class Trietg : public TestGenerator<Trie *> {
    private:
        unsigned int count = 0;
        static const unsigned int MAXTESTCOUNT;
    protected:
        void callPUT(Trie *) = 0;
    public:
        virtual ~Trietg();
        virtual Trie *generateTest();
        virtual void deleteTest(Trie *);
        virtual bool toContinue();
        virtual string toString(Trie *);
        virtual string toJSON(Trie *);
        virtual Trie *readFromJSONFile(string);
};

class Trietg_search_key : public Trietg {
   protected:
        void callPUT(Trie *);
};

#endif
