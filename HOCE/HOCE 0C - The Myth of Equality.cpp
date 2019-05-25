#include <iostream>
#include <limits>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    float a, b;
    cin >> a >> b;

    float approximation = fabs(min(a, b)) * numeric_limits<float>::epsilon();
    float essentiallyequal = fabs(a - b);

    if(essentiallyequal <= approximation) cout << "true" << '\n';
    else cout << "false" << '\n';
}