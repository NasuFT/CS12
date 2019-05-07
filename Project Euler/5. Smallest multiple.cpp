#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

// 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.
// What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

long long findSmallestMultiple(int n) {
    vector<int> factors;
    long long num = 1;

    for(int i = 0; i < n; i++) {
        factors.push_back(i + 1);
    }

    for(int i = 2; i <= n; i++) {
        bool flag = false;
        
        for(int j = 0; j < n; j++) {
            if(factors[j] % i == 0) {
                factors[j] /= i;
                flag = true;
            }
        }

        if(flag) {
            num *= i;
            i--;
        }
    }

    return num;
}

int main() {
    cout << findSmallestMultiple(20) << "\n";
}