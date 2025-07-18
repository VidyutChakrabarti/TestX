#ifndef ENERGYASSIGNER_H
#define ENERGYASSIGNER_H

#include <vector>
#include <set>

// Returns an integer energy (priority) for a testcase based on new lines covered

template <typename T>
class EnergyAssigner
{
public:
    // Assigns energy to a testcase based on new_coverage (float)
    int assignEnergy(const T &testcase, float new_coverage)
    {
        return 1;
    }
};

#endif // ENERGYASSIGNER_H
