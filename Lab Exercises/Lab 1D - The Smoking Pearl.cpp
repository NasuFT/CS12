#include <iostream>

using namespace std;

int main() {
    int n, k, total = 0, cig_butts = 0;

    cin >> n >> k;

    while (n >= 1) {
        total += n;
        cig_butts += n;
        n = cig_butts / k;
        cig_butts -= n * k;
    }

    cout << total << endl;

    return 0;
}