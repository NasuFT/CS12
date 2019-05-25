#include <iostream>

using namespace std;

int main() {
    int t;
    cin >> t;

    for(int i = 0; i < t; i++) {
        unsigned long long a, b;
        cin >> a >> b;
        unsigned long long gap_av, average;
        if(a < b) {
            gap_av = (b - a) / 2;
            average = a + gap_av;
        } else {
            gap_av = (a - b) / 2;
            average = b + gap_av;
        }

        cout << average << '\n';
    }
}