#include <iostream>
using namespace std;

void testFunction(int x) {
    if (x > 0) {
        cout << "Positive\n";
    } else if (x < 0) {
        cout << "Negative\n";
    } else {
        cout << "Zero\n";
    }
}

int main() {
    int x;
    while (cin >> x) {
        testFunction(x);
    }
    return 0;
}

