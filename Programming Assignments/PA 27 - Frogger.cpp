#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

int *cache;

int minimum_cost(int stones, vector<int> &costs, int step, int current = 1) {
    if(cache[current - 1] != -1) return cache[current - 1];
    if(current == stones) return 0;

    int min_cost = numeric_limits<int>::max();

    for(int i = 1; i <= step; i++) {
        if(current + i > stones) break;

        int cost_to_step = abs(costs[current + i - 1] - costs[current - 1]) + minimum_cost(stones, costs, step, current + i);

        if(cost_to_step < min_cost) {
            min_cost = cost_to_step;
        }
    }

    cache[current - 1] = min_cost;

    return min_cost;
}

int main() {
    int t;
    cin >> t;

    for(int _ = 0; _ < t; _++) {
        int n, k;
        cin >> n >> k;

        vector<int> h(n);
        cache = new int[n];
        fill(cache, cache + n, -1);

        for(int i = 0; i < n; i++) {
            int n;
            cin >> n;
            h[i] = n;
        }

        cout << minimum_cost(n, h, k) << '\n';

        delete [] cache;
    }

    return 0;
}