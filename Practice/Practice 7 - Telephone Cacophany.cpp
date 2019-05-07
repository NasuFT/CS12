#include <iostream>
#include <string>

using namespace std;

const int MAPPING_SIZE = 10;
const string MAPPING[] = {
    "0",
    "1",
    "ABC2",
    "DEF3",
    "HGI4",
    "JKL5",
    "MNO6",
    "PQRS7",
    "TUV8",
    "WXYZ9",
};

char convert(char ch) {
    for (int i = 0; i < MAPPING_SIZE; i++) {
        if (MAPPING[i].find(ch) != string::npos) {
            return ('0' + i);
        }
    }

    return ch;
}

string str_to_phone(string s) {
    size_t size = s.size();
    string result("");

    for (int i = 0; i < size; i++) {
        result = result + convert(s[i]);
    }

    return result;
}

int main() {
    string s;

    getline(cin, s);

    cout << str_to_phone(s) << "\n";
}