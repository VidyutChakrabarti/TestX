#ifndef VGEN_H
#define VGEN_H

#include <string>
#include <set>

using namespace std;
namespace testgenerator {
template <typename T> class ValueGenerator {
    protected:
        set<T> values;
    public:
        ValueGenerator();
        virtual T generateValue();
        virtual T generate() = 0;
        virtual bool isValid(T value) = 0;
};

class IntGenerator : public ValueGenerator<int> {
    public:
        IntGenerator();
        virtual int generate();
        virtual bool isValid(int value);
};

class FloatGenerator : public ValueGenerator<float> {
    public:
        FloatGenerator();
        virtual float generate();
        virtual bool isValid(float value);
};

class StringGenerator : public ValueGenerator<string> {
    private:
        const unsigned int MAXLEN = 10;
    public:
        StringGenerator();
        virtual string generate();
        virtual bool isValid(string value);
};


} // namespace testgenerator
#endif
