#include <iostream>
#include <string>
#include <vector>

using namespace std;

void infect(vector<string> &str, int x, int y) {
    if(x < 0 || x >= str.size() || y < 0 || y >= str[0].size()) return;
    if(str[x][y] != '.') return;

    str[x][y] = 'O';

    infect(str, x - 1, y);
    infect(str, x + 1, y);
    infect(str, x, y + 1);
    infect(str, x, y - 1);
}

int main() {
    int t;

    cin >> t;

    for(int i = 0; i < t; i++) {
        int rows, cols, x, y;
        vector<string> str;

        cin >> rows >> cols >> x >> y;
        cin.ignore();

        for(int i = 0; i < rows; i++) {
            string str2;
            getline(cin, str2);
            str.push_back(str2);
        }

        infect(str, x, y);

        for(int i = 0; i < rows; i++) {
            cout << str[i] << '\n';
        }
    }
}