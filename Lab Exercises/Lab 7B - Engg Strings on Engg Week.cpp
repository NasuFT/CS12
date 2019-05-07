#include <iostream>
#include <string>

using namespace std;

bool engg(string S) {
    if((S[0] != 'E' && S[0] != 'e') || S[1] != 'N') return false;

    int index = 1;

    while(S[index++] == 'N');

    if(S.substr(index).compare("GG") == 0 || engg(S.substr(index))) return true;

    return false;
}

int main() {
    string str;

    while(true) {
        cin >> str;
        if(str.compare("") == 0) break;
        cout << engg(str) << '\n';
    }

    return 0;
}