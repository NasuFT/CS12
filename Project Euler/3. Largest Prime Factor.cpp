#include <iostream>
#include <math.h>
using namespace std;

// The prime factors of 13195 are 5, 7, 13 and 29.
// What is the largest prime factor of the number 600851475143 ?

int main() {
    long long t;
    int largest_prime_factor = 0;
    cin >> t;

    int prime_factor = sqrt(t);

    for(int i = 2; i < prime_factor; i++) {
        if(t % i == 0) {
            t /= i;
            if(largest_prime_factor < i) {
                largest_prime_factor = i;
            }

            cout << t << " " << i << endl;
            i--;
        }
    }

    cout << largest_prime_factor << endl;

    return 0;
}