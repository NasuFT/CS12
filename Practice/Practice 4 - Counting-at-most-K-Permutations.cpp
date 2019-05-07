#include <iostream>
#include <vector>

using namespace std;

int permutations(vector<int> set, int k) {
    if(k == 0) return 1;

    
}

int main() {
    int t;
    cin >> t;

    for(int i = 0; i < t; i++) {
        int n, k;
        cin >> n >> k;

        vector<int> set(n);

        for(int i = 0; i < n; i++) {
            set[i] = i + 1;
        }

        int k_permutations = 0;

        for(int i = 0; i <= k; i++) {
            k_permutations += permutations(set, i);
        }

        cout << k_permutations << '\n';
    }

    return 0;
}