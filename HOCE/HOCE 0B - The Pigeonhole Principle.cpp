#include <iostream>
#include <algorithm>

using namespace std;

int *cache;

int slowFunction(int N);

int main() {
    cache = new int[1002];
    fill(cache, cache + 1002, -1);
    int t;
    cin >> t;

    for(int i = 0; i < t; i++) {
        int n, answer;
        cin >> n;
        if(cache[n] != -1) {
            answer = cache[n];
        } else {
            answer = slowFunction(n);
            cache[n] = answer;
        }

        cout << answer << '\n';
    }

    delete [] cache;
}