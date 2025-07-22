#include "llmutator.h"
#include "valuegenerators.h"
#include <algorithm>
#include <random>

using namespace std;
using namespace testgenerator;

LLMutator::LLMutator() {}

LLMutator::~LLMutator() {}

vector<function<LinkedList *(LinkedList *)>> LLMutator::getMutations(LinkedList *base)
{
    vector<function<LinkedList *(LinkedList *)>> mutations;

    // Add node mutation
    mutations.push_back([this](LinkedList *ll) -> LinkedList *
                        { return addNodeMutation(ll); });

    // Remove node mutation
    mutations.push_back([this](LinkedList *ll) -> LinkedList *
                        { return removeNodeMutation(ll); });

    // Modify node mutation
    mutations.push_back([this](LinkedList *ll) -> LinkedList *
                        { return modifyNodeMutation(ll); });

    return mutations;
}

LinkedList *LLMutator::addNodeMutation(LinkedList *ll)
{
    StringGenerator sg;
    string newData = sg.generateValue();
    ll->append(newData);
    return ll;
}

LinkedList *LLMutator::removeNodeMutation(LinkedList *ll)
{
    if (ll->head == nullptr)
    {
        return ll; // Can't remove from empty list
    }

    // Remove the first node
    Node *toDelete = ll->head;
    ll->head = ll->head->next;
    delete toDelete;
    return ll;
}

LinkedList *LLMutator::modifyNodeMutation(LinkedList *ll)
{
    if (ll->head == nullptr)
    {
        return ll; // Can't modify empty list
    }

    StringGenerator sg;
    ll->head->data = sg.generateValue();
    return ll;
}
