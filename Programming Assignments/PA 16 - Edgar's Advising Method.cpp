#include <iostream>

using namespace std;

int pow(int a, int b) {
    int result = 1;

    for(int i = 0; i < b; i++) {
        result *= a;
    }

    return result;
}

int advise(int n, int mult = 0) {
    if(2 * pow(2, mult) > n) return pow(2, mult);
    return advise(n, mult + 1);
}

int main() {
    int t;
    cin >> t;
    
    for(int i = 0; i < t; i++) {
        int n;
        cin >> n;
        cout << advise(n) << '\n';
    }
}