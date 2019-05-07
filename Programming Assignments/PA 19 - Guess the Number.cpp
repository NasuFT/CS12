#include <iostream>

using namespace std;

int answer(int a, int b) {
    int m = a + ((b - a) / 2);
    int x = guess(m);

    if(x < 0) return answer(m + 1, b);
    else if(x > 0) return answer(a, m - 1);

    return m;
}

int guess(int n) {

}

int main() {

}