#ifndef LLMUTATOR_H
#define LLMUTATOR_H

#include "mutator.h"
#include "linkedlist.h"
#include <functional>
#include <vector>

using namespace std;
using namespace testgenerator;

class LLMutator : public Mutator<LinkedList *>
{
public:
    LLMutator();
    virtual ~LLMutator();
    virtual vector<function<LinkedList *(LinkedList *)>> getMutations(LinkedList *base) override;

private:
    LinkedList *addNodeMutation(LinkedList *ll);
    LinkedList *removeNodeMutation(LinkedList *ll);
    LinkedList *modifyNodeMutation(LinkedList *ll);
};

#endif
