#include <iostream>
#include "valuegenerators.h"

using namespace std;
using namespace testgenerator;
void t1() {
    cout << "t1()" << endl;
    IntGenerator g;
    for(unsigned int i = 0; i < 5; i++) {
        cout << g.generateValue() << endl;
    }
}

void t2() {
    cout << "t2()" << endl;
    FloatGenerator g;
    for(unsigned int i = 0; i < 5; i++) {
        cout << g.generateValue() << endl;
    }
}

void t3() {
    cout << "t3()" << endl;
    StringGenerator g;
    for(unsigned int i = 0; i < 5; i++) {
        cout << g.generateValue() << endl;
    }
}
int main() {
    cout << "Testing value generators" << endl;
    t1();
    t2();
    t3();
    return 0;
}
