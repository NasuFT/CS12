#include <iostream>
#include <math.h>

using namespace std;

// By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.
// What is the 10 001st prime number?

bool isPrime(int n) {
    if(n < 2) return false;
    else if(n < 4) return true;
    else if(n % 2 == 0) return false;
    else if(n < 9) return true;
    else if(n % 3 == 0) return false;
    else {
        for(int i = 5; i <= floor(sqrt(n)); i += 6) {
            if(n % i == 0) return false;
            if(n % (i + 2) == 0) return false;
        }
    }

    return true;
}

// Execution time(500,000th Prime) = ~11s

// bool isPrime(int n) {
//     if(n < 2) return false;

//     for(int i = 2; i <= sqrt(n); i++) {
//         if(n % i == 0) return false;
//     }

//     return true;
// }
// Execution time(500,000th Prime) = ~51s

long long findPrime(int n) {
    long long num;
    long long prime_num = 2;

    for(int i = 0; i < n; i++) {
        if(isPrime(prime_num)) num = prime_num;
        else i--;

        prime_num++;
    }

    return num;
}

int main() {
    cout << findPrime(10001) << "\n";
    return 0;
}
