#include <iostream>

using namespace std;

int F(int n, int k) {
    if(n == 0 && k == 0) return 1;
    if(n == 0 || k == 0) return 0;
    return F(n - 1, k - 1) + k * F(n - 1, k);
}

int G(int n, int k) {
    
}

int main() {
    int n, k;

    cin >> n >> k;

    cout << G(n, k) << "\n";
}