#include <iostream>
#include <vector>

using namespace std;

// TIME LIMIT EXCEEDED

bool isAllConquered(vector<vector<int>> &arr) {
    for(int i = 0; i < arr.size(); i++) {
        for(int j = 0; j < arr[0].size(); j++) {
            if(arr[i][j] != 1) return false;
        }
    }

    return true;
}

bool isInBounds(vector<vector<int>> arr, int x, int y) {
    return 0 <= x && x < arr.size() && 0 <= y && y < arr[0].size() ? true : false;
}

void spread(vector<vector<int>> &arr, int x, int y) {
    if(isInBounds(arr, x - 1, y) && arr[x - 1][y] == 0) arr[x - 1][y] = -1;
    if(isInBounds(arr, x + 1, y) && arr[x + 1][y] == 0) arr[x + 1][y] = -1;
    if(isInBounds(arr, x, y - 1) && arr[x][y - 1] == 0) arr[x][y - 1] = -1;
    if(isInBounds(arr, x, y + 1) && arr[x][y + 1] == 0) arr[x][y + 1] = -1;
}

void conquer(vector<vector<int>> &arr) {
    for(int i = 0; i < arr.size(); i++) {
        for(int j = 0; j < arr[0].size(); j++) {
            if(arr[i][j] == 1) {
                spread(arr, i, j);
            }
        }
    }

    for(int i = 0; i < arr.size(); i++) {
        for(int j = 0; j < arr[0].size(); j++) {
            if(arr[i][j] == -1) arr[i][j] = 1;
        }
    }
}

int main() {
    int rows, cols, n;
    int count = 1;
    vector<vector<int>> arr;
    cin >> rows >> cols >> n;

    for(int i = 0; i < rows; i++) {
        vector<int> vec;

        for(int j = 0; j < cols; j++) {
            vec.push_back(0);
        }

        arr.push_back(vec);
    }

    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;

        arr[a - 1][b - 1] = 1;
    }

    while(!isAllConquered(arr)) {
        conquer(arr);
        count++;
    }

    cout << count << '\n';

    return 0;
}