#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maximum_sum(vector<vector<int>> triangle) {
    int max_sum = 0;

    vector<vector<int>> cache(triangle.size());

    for(int i = 0; i < cache.size(); i++) {
        cache[i].resize(i + 1);
    }
    
    for(int i = triangle.size() - 1; i >= 0; i--) {
        for(int j = 0; j < triangle[i].size(); j++) {
            if(i == triangle.size() - 1) {
                cache[i][j] = triangle[i][j];
            } else {
                cache[i][j] = triangle[i][j] + max(cache[i + 1][j], cache[i + 1][j + 1]);
            }

            if(cache[i][j] > max_sum) {
                max_sum = cache[i][j];
            }
        }
    }

    return max_sum;
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> triangle(n);

    for(int i = 0; i < n; i++) {
        triangle[i].resize(i + 1);

        for(int j = 0; j < i + 1; j++) {
            int x;
            cin >> x;

            triangle[i][j] = x;
        }
    }

    cout << maximum_sum(triangle) << '\n';
}