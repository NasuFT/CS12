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

        //Twister Planet
        int x = 0, y = 0, k = 0;
        for(int i = 0; i < n * n; i++) {
            cout << arr[y][x] << " ";
            
            if(y - k == 0) {
                if(x == n - k - 1) y++;
                else x++;
            } else if(x + k == n - 1) {
                if(y == n - k - 1) x--;
                else y++;
            } else if(y + k == n - 1) {
                if(x - k == 0) y--;
                else x--;
            } else if(x - k == 0) {
                if(y - k - 1 == x - k) {
                    k++;
                    x++;
                } else y--;
            }
        }

        cout << endl;

        //Clean-up
        for(int i = 0; i < n; i++) delete [] arr[i];
        
        delete [] arr;
    }

    return 0;
}