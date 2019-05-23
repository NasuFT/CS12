#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    string str;
    getline(cin, str);
    stringstream ss(str);
    string sss;
    while(ss) {
        ss >> sss;
        cout << sss << " " << sss.length() << '\n';
    }
    return 0;
}