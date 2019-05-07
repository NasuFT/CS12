#include <iostream>
#include <string>

using namespace std;

int main() {
    char arr[20][20];

    //Input grid
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 20; j++) cin >> arr[i][j];
    }

    //Searching algorithm
    for(int _ = 0; _ < 10; _++) {
        string str;
        cin >> str;

        bool found = false;

        for(int y = 0; y < 20; y++) {
            for(int x = 0; x < 20; x++) {
                if(str[0] == arr[y][x]) {
                    if(str.length() == 1) found = true;
                    else {
                        int dx = 0;
                        int dy = 0;

                        for(int i = -1; i <= 1; i++) {
                            for(int j = -1; j <= 1; j++) {
                                if(0 <= y + i && y + i < 20 && 0 <= x + j && x + j < 20) {
                                    if(str[1] == arr[y + i][x + j]) {
                                        dx = j;
                                        dy = i;
                                    }
                                }
                            }
                        }

                        if(dx != 0 || dy != 0) {
                            if(str.length() == 2) found = true;
                            else {
                                found = true;

                                for(int k = 2; k < str.length(); k++) {
                                    if(str[k] != arr[y + (k * dy)][x + (k * dx)]) found = false; 
                                }
                            }
                        }
                    }
                }

                if(found) break;
            }
            if(found) break;
        }

        if(found) cout << "PRESENT" << endl;
        else cout << "ABSENT" << endl;
    } 

    return 0;
}