#include <iostream>
#include <string>

using namespace std;

bool boggle_util(char grid[4][4], int row, int col, string str) {
    bool result = false;

    if(row < 0 || row > 3 || col < 0 || col > 3) return false;

    if(str == "") return true;

    if(str[0] == grid[row][col]) {
        grid[row][col] = '-';
        if(boggle_util(grid, row - 1, col - 1, str.substr(1))) result = true;
        if(boggle_util(grid, row, col - 1, str.substr(1))) result = true;
        if(boggle_util(grid, row + 1, col - 1, str.substr(1))) result = true;
        if(boggle_util(grid, row - 1, col, str.substr(1))) result = true;
        if(boggle_util(grid, row + 1, col, str.substr(1))) result = true;
        if(boggle_util(grid, row - 1, col + 1, str.substr(1))) result = true;
        if(boggle_util(grid, row, col + 1, str.substr(1))) result = true;
        if(boggle_util(grid, row + 1, col + 1, str.substr(1))) result = true;
        grid[row][col] = str[0];

        if(result) return true;
    }
    
    return false;
}

void boggle(char grid[4][4], string str) {
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(boggle_util(grid, i, j, str)) {
                cout << "Row " << i + 1 << ", Column " << j + 1 << '\n';
                return;
            }
        }
    }

    cout << "No\n";
}

int main() {
    int t;
    cin >> t;
    
    for(int i = 0; i < t; i++) {
        char grid[4][4];
        int queries;

        for(int i = 0; i < 4; i++) {
            string str;
            cin >> str;

            grid[i][0] = str[0];
            grid[i][1] = str[1];
            grid[i][2] = str[2];
            grid[i][3] = str[3];
        }

        cin >> queries;

        for(int i = 0; i < queries; i++) {
            string str;
            cin >> str;

            boggle(grid, str);
        }
    }


}