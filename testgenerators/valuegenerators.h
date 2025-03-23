#ifndef VGEN_H

#define VGEN_H

#include <string>

#include <set>

using namespace std;

namespace testgenerator
{

    template <typename T>
    class ValueGenerator
    {

    protected:
        set<T> values;

    public:
        ValueGenerator();

        virtual T generateValue();

        virtual T generate() = 0;

        virtual bool isValid(T value) = 0;
    };

}