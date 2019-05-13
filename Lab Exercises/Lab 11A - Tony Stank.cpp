#include <iostream>
#include <vector>

using namespace std;

int max_unique_designs(vector<int> costs) {
    int max_designs = 1;
    int cost_sum = 0;

    for(unsigned int i = 0; i < costs.size() - 1; i++) {
        if(cost_sum + costs[i] < costs[i + 1]) {
            cost_sum += costs[i];
            max_designs++;
        }
    }

    return max_designs;
}

int main() {
    int t;
    cin >> t;

    for(int _ = 0; _ < t; _++) {
        int suits;
        cin >> suits;
        vector<int> costs(suits);

        for(int i = 0; i < suits; i++) {
            int cost;
            cin >> cost;
            costs[i] = cost;
        }

        cout << max_unique_designs(costs) << '\n';
    }

    return 0;
}