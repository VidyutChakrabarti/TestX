#ifndef MUTATOR_H
#define MUTATOR_H

#include <vector>
#include <functional>

using namespace std;

template <typename T>
class Mutator {
protected:
    vector<function<T(T)>> mutations;
public:
    Mutator() = default;
    virtual ~Mutator() = default;

    void addMutation(function<T(T)> mutation) {
        mutations.push_back(mutation);
    }

    virtual const vector<function<T(T)>>& getMutations(const T&) const {
        return mutations;
    }
};

#endif
