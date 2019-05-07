#include <iostream>
#include <math.h>

using namespace std;

// A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.
// Find the largest palindrome made from the product of two 3-digit numbers.

bool isProduct(int n) {
    for(int i = 999; i >= sqrt(n); i--) {
        if(n % i == 0) return true;
    }

    return false;
}

int findReverse(int n) {
    int num = 0;

    while(true) {
        num *= 10;
        num += n % 10;
        n /= 10;
        
        if(n == 0) return num;
    }
}

int findPalindrome(int n) {
    return n * 1000 + findReverse(n);
}

int findLargestPalindrome() {
    for(int t = 999; t > 99; t--) {
        int x = findPalindrome(t);

        if(isProduct(x)) return x;
    }

    return -1;
}

int main() {
    cout << findLargestPalindrome() << "\n";

    return 0;
}