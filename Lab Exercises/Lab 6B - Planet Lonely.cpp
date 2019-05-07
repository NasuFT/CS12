#include <iostream>
#include <string>
#include <map>

using namespace std;

void query(map<string, string> &friends, string &name) {
    int size = friends.size();
    string name2 = friends[name];

    if(name2 == string("lonely")) {
        cout << "Nothing to see here" << "\n";
        return;
    }

    if(friends[name2] == name) {
        cout << "Hide!" << "\n";
        return;
    }
    
    for(int i = 0; i < friends.size(); i++) {
        name2 = friends[name2];
        if(friends[name2] == name) {
            cout << "Ring of friendship!" << "\n";
            return;
        }
    }

    cout << "Nothing to see here" << "\n";
}

int main() {
    int t;
    cin >> t;
    map<string, string> friends;
    for(int i = 0; i < t; i++) {
        string name1, name2;
        cin >> name1;
        cin >> name2;

        friends[name1] = name2;
    }

    int q;
    cin >> q;
    for(int i = 0; i < q; i++) {
        string name;
        cin >> name;

        query(friends, name);
    }

    return 0;
}