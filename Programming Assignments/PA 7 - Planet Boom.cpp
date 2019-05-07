#include <iostream>

using namespace std;

int main() {
    int t;

    cin >> t;

    for(int _ = 0; _ < t; _++) {
        int m, n, e;
        cin >> m >> n >> e;

        //2-D Array Creation
        int **arr = new int*[m];
        for(int i = 0; i < m; i++) arr[i] = new int[n];

        //Input Matrix
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) cin >> arr[i][j];
        }

        //Planet Boom
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(arr[i][j] == 1) {
                    for(int y = i - (e - 1); y <= i + (e - 1); y++) {
                        for(int x = j - (e - 1); x <= j + (e - 1); x++) {
                            if(0 <= x && x < n && 0 <= y && y < m && arr[y][x] == 0) arr[y][x] = -1;
                        }
                    }
                }
            }
        }

        int count = 0;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(arr[i][j] == 0) count++;
            }
        }

        //Output
        if(count == 0) cout << "Go home!" << endl;
        else if(count == 1) cout << "There is 1 safe region." << endl;
        else cout << "There are " << count << " safe regions." << endl;

        //Cleaning up
        for(int i = 0; i < m; i++) delete [] arr[i];

        delete [] arr;
    }

    return 0;
}