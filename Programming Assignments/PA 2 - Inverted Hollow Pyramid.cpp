#include <iostream>

using namespace std;

int main() {
    int t, b;
    
    cin >> t;

    for(int k = 0; k < t; k++) {
        cin >> b;

        if(b % 2 == 0) b -= 1;

        for(int i = 0; i < b / 2 + 1; i++) {
            for(int j = 0; j < b - i; j++) {
                if(i == 0 || j == i || j == b - i - 1) {
                    cout << "*";
                } else {
                    cout << " ";
                }
            }

            cout << endl;
        }

        cout << endl;
    }
}