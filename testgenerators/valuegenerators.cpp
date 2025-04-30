#ifndef VGEN_CPP
#define VGEN_CPP

#include<random>
#include <bits/stdc++.h>

#include "valuegenerators.h"

namespace testgenerator {
template <typename T> ValueGenerator<T>::ValueGenerator() {
}

template <typename T> T ValueGenerator<T>::generateValue() {
    T newValue = generate();
    while(!isValid(newValue)) {
        newValue = generate();
    }
    values.insert(newValue);
    return newValue;
}

IntGenerator::IntGenerator() : ValueGenerator() {}

int IntGenerator::generate() {
    return rand();
}

bool IntGenerator::isValid(int value) {
    return true;
}

FloatGenerator::FloatGenerator() : ValueGenerator() {}

float FloatGenerator::generate() {
    return (float)(rand()) / (float)(rand());
}

bool FloatGenerator::isValid(float value) {
    return true;
}

StringGenerator::StringGenerator() : ValueGenerator() {}

string StringGenerator::generate() {
    unsigned int l = rand() % MAXLEN;
    string s = "";
    for(unsigned int i = 0; i < l; i++) {
        char c = (char)((rand() % 79) + 48);
        s += c;
    }
    return s;
}

bool StringGenerator::isValid(string value) {
    auto it = values.find(value);
    return (it != values.end()) == false;
}

} // namespace testgenerator

#endif
