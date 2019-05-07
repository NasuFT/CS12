#include <iostream>

using namespace std;

bool isPrime(int n) {
    for (int i = 2; i < n; i++) {
        if(n % i == 0) return false;
    }

    return true;
}   

int main() {
    bool anyPrime, primeRange;
    int t, m, n, j, k;

    cin >> t;

    for (int i = 0; i < t; i++) {
        anyPrime = false;
        primeRange = false;

        cin >> m >> n;

        if(isPrime(m) && isPrime(n)) {
            primeRange = true;
            j = m;
            k = n;
        } else {
            j = m + 1;
            k = n - 1;
        }

        for (j; j <= k; j++) {
            if(isPrime(j)) {
                if(!anyPrime) {
                    anyPrime = true;
                    cout << j;
                } else {
                    cout << "," << j;
                }
            }
        }

        if(primeRange) {
            cout << " Yehey! This is a prime range.";
        }

        if(!anyPrime) {
            cout << "There are no primes.";
        }

        cout << endl;
    }
}