#include <iostream>

using namespace std;

int main() {
    int t, a, b, c;

    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> a >> b >> c;

        if (c == 0 || (c > 0 && a > b) || (c < 0 && a < b)) {
            cout << "Invalid Input!" << endl << endl;
            continue;
        } else {
            while (true) {
                if ((c > 0 && a > b) || (c < 0 && a < b)) break;

                if (a % 3 == 0 && a % 5 == 0) {
                    cout << "FizzBuzz" << endl;
                } else if (a % 3 == 0) {
                    cout << "Fizz" << endl;
                } else if (a % 5 == 0) {
                    cout << "Buzz" << endl;
                } else {
                    cout << a << endl;
                }

                a += c;
            }
        }
        cout << endl;
    }

    return 0;
}