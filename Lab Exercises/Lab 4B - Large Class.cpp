#include <iostream>
#include <string>

using namespace std;

string cipher(string str1, string str2) {
    int index = 0;
    string encryptedMessage;

    for(int i = 0; i < str1.length(); i++) {
        if(str1[i] == ' ') {
            encryptedMessage += str1[i];
        } else {
            int letter = str1[i] + (str2[index] - 'A');
            if(letter > 'Z') letter -= 26;

            encryptedMessage += letter;

            index = (index + 1) % str2.length();
        }
    }

    return encryptedMessage;
}

int main() {
    int t;
    cin >> t;
    cin.ignore(10, '\n');

    for(int _ = 0; _ < t; _++) {
        string str1;
        string str2;

        getline(cin, str1);
        getline(cin, str2);

        cout << cipher(str1, str2) << endl;
    }

    return 0;
}