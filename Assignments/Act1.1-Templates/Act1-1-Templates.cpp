#include <iostream>
using namespace std;

int sum(int a, int b) {
    return a + b;
}

int main() {
    int a = 5;
    int b = 10;
    cout << "The sum of " << a << " and " << b << " is: " << sum(a, b) << endl;
    return 0;
}