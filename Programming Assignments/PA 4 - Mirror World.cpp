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

        //Mirror World
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(j > i) {
                    int _temp = arr[i][j];
                    arr[i][j] = arr[j][i];
                    arr[j][i] = _temp;
                }
            }
        }

        //Output matrix
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cout << arr[i][j] << " ";
            }

            cout << endl;
        }

        cout << endl;

        //Clean-up
        for(int i = 0; i < n; i++) delete [] arr[i];
        
        delete [] arr;
    }

    return 0;
}