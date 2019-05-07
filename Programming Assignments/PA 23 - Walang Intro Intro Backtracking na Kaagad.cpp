#include <iostream>
#include <cmath>

using namespace std;

int sum_of_digits(int num) {
    int sum = 0;

    while(num > 0) {
        sum += num % 10;
        num /= 10;
    }

    return sum;
}

int check_solutions(int n, int d, int s) {
    if(s >= int(pow(10, d))) return 0;
    if(n < d) return 0;

    int solutions = 0;

    for(int i = int(pow(10, d - 1)); i < int(pow(10, d)); i++) {
        if(sum_of_digits(i) == s) solutions++;
    }

    return solutions;
}

int main() {
    int t;
    cin >> t;

    for(int i = 0; i < t; i++) {
        int n, d, s;
        cin >> n >> d >> s;
        cout << check_solutions(n, d, s) << '\n';
    }

    return 0;
}