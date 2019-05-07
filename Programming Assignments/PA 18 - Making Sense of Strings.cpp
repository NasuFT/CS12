#include <iostream>
#include <string>

using namespace std;

bool isInDict(string *dict, int n, string str) {
    for(int i = 0; i < n; i++) {
        if(dict[i] == str) return true;
    }

    return false;
}

void sense(string *dict, int n, string str, int sz, string result = "") {
    for(int i = 1; i <= sz; i++) {
        string s = str.substr(0, i);
        if(isInDict(dict, n, s)) {
            if(i == sz) {
                result += s;
                cout << '(' << result << ')';
                return;
            }

            sense(dict, n, str.substr(i, sz - i), sz - i, result + s + ' ');
        }
    }
}

int main() {
    int t;
    cin >> t;

    for(int _ = 0; _ < t; _++) {
        int n;
        cin >> n;
        string *dict = new string[n];

        for(int i = 0; i < n; i++) {
            string str;
            cin >> str;
            dict[i] = str;
        }

        string str;
        cin >> str;

        sense(dict, n, str, str.size());

        delete [] dict;

        cout << '\n';
    }
}