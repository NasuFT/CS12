#include <iostream>
#include <string>

using namespace std;

int main() {
    string str;
    int n;
    cin >> n;
    cout << n << '\n';
    getline(cin, str);
    cout << str.length() << '\n';
}