#ifndef VGEN_CPP

#define VGEN_CPP

#include <random>

#include <bits/stdc++.h>

#include "valuegenerators.h"

namespace testgenerator
{

    template <typename T>
    ValueGenerator<T>::ValueGenerator()
    {
    }

    template <typename T>
    T ValueGenerator<T>::generateValue()
    {

        T newValue = generate();

        while (!isValid(newValue))
        {

            newValue = generate();
        }

        values.insert(newValue);

        return newValue;
    }
}