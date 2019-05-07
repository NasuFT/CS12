#include <iostream>

using namespace std;

int get_sum(int *arr, int pos, int len) {
    int result = 0;

    for(int i = 0; i < len; i++) {
        result += arr[pos + i];
    }

    return result;
}

int get_sum(int *arr, int len) {
    return get_sum(arr, 0, len);
}

bool share(int n, int m, int *coins, int total_n = -1) {
    if(total_n == -1) total_n = get_sum(coins, n);
    if(total_n == m) return true;

    for(int i = n - 1; i >= 0; i--) {
        int *coins_arr = new int[n - 1];

        for(int j = 0; j < n - 1; j++) {
            if(j < i) coins_arr[j] = coins[j];
            else coins_arr[j] = coins[j + 1];
        }

        if(share(n - 1, m + coins[i], coins_arr, total_n - coins[i])) return true;

        delete [] coins_arr;
    }

    return false;
}

int main() {
    int t;
    cin >> t;
    
    for(int _ = 0; _ < t; _++) {
        int n, m;
        cin >> n >> m;
        int *coins = new int[n];

        for(int i = 0; i < n; i++) {
            int a;
            cin >> a;
            coins[i] = a;
        }

        cout << share(n, m, coins) << '\n';

        delete [] coins;
    }
}