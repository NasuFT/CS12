#include <iostream>

using namespace std;

int main() {
    int n, r1, c1, r2, c2;

    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> r1 >> c1 >> r2 >> c2;

        if (r1 == r2 || c1 == c2) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }

    return 0;
}