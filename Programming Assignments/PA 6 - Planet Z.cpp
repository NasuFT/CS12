#include <iostream>

using namespace std;

int main() {
    int t;

    cin >> t;

    for (int a = 0; a < t; a++) {
        int n;
        cin >> n;

        //2-D array creation
        int **arr = new int*[n];
        for(int i = 0; i < n; i++) arr[i] = new int[n];

        //Input matrix
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) cin >> arr[i][j];
        }

        //Planet Z
        int x = 0, y = 0;
        for(int i = 0; i < n * n; i++) {
            cout << arr[y][x] << "\t";

            if(x == n - 1) {
                x = y + 1;
                y = n - 1;
                cout << endl;
            } else if(y == 0) {
                y = x + 1;
                x = 0;
                cout << endl;
            } else {
                x++;
                y--;
            }
        }

        cout << endl;

        //Clean-up
        for(int i = 0; i < n; i++) delete [] arr[i];
        
        delete [] arr;
    }

    return 0;
}