#include <iostream>
#include <string>
#include <map>

using namespace std;

int main() {
    int t;
    cin >> t;
    cin.ignore();
    int count = 1;

    while(t > 0) {
        map<string, int> mapping;

        for(int i = 0; i < t; i++) {
            string str;
            getline(cin, str);
            while(str.find(' ') != string::npos) {
                int x = str.find(' ');
                str = str.substr(x + 1);
            }

            for(int i = 0; i < str.size(); i++) {
                if('A' <= str[i] && str[i] <= 'Z') {
                    str[i] = char((str[i] - 'A') + 'a');
                }
            }

            mapping[str]++;
        }

        cout << "List " << count++ << ":\n";
        for(map<string, int>::iterator it = mapping.begin(); it != mapping.end(); it++) {
            cout << it->first << " | " << it->second << '\n';
        }

        cin >> t;
        cin.ignore();
    }

    return 0;
}