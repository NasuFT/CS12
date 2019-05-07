#include <iostream>
#include <string>

using namespace std;

bool findSubstr(string str1, string str2) {
    int index = 0;
    string substring = str1;

    for(int i = 0; i < str2.length(); i++) {
        if(substring.find(str2[i], 0) != string::npos) {
            index = substring.find(str2[i], 0);
            substring = substring.substr(index + 1);
        } else return false;
    }

    return true;
}

int main() {
    int t;
    cin >> t;
    cin.ignore(10, '\n');

    for(int _ = 0; _ < t; _++) {
        string str1;
        string str2;

        getline(cin, str2);
        getline(cin, str1);

        if(findSubstr(str1, str2)) cout << "Yes!\n";
        else cout << "Fetch more coffee\n";
    }

    return 0;
}