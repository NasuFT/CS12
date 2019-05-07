#include <iostream>
#include <string>

using namespace std;

// NO NUMBER IMPLEMENTATION

int substring(string str1, string str2) {
    int str1_len = str1.length();
    int str2_len = str2.length();

    //If there is no substring
    if(str2_len > str1_len) {
        cout << "no substring exists" << endl;
        return -1;
    }

    for(int i = 0; i < str2_len; i++) {
        if(str1.find(str2[i]) == string::npos) {
            cout << "no substring exists" << endl;
            return -1;
        }
    }

    //Else
    int str1_alph[26];
    int str2_alph[26];
    int index1 = -1;
    int index2 = 0;
    int pos1 = 0;
    int pos2 = 0;
    int str_len = str1_len;
    bool flag = false;
    bool loop = true;
    bool blank = false;

    for(int i = 0; i < 26; i++) {
        str1_alph[i] = 0;
        str2_alph[i] = 0;
    }

    for(int i = 0; i < str2_len; i++) {
        str2_alph[str2[i] - 'a']++;
    }

    while(loop) {
        if(!flag) {
            if(str2_alph[str1[pos2] - 'a'] > 0) str1_alph[str1[pos2] - 'a']++;

            blank = false;

            for(int i = 0; i < 26; i++) {
                if(str1_alph[i] < str2_alph[i]) {
                    if(pos2 < str1_len - 1) pos2++;
                    blank = true;
                    break;
                }
            }

            if(!blank || pos2 == str1_len - 1) {
                flag = true;
                if(pos2 == str1_len - 1) {
                    if(str2_alph[str1[pos2] - 'a'] > 0) str1_alph[str1[pos2] - 'a']++;
                }
            }
        } else {
            if(str2_alph[str1[pos1] - 'a'] > 0) str1_alph[str1[pos1] - 'a']--;
            pos1++;

            for(int i = 0; i < 26; i++) {
                if(str1_alph[i] < str2_alph[i]) {
                    if(pos2 - pos1 + 2 < str_len) {
                        index1 = pos1 - 1;
                        index2 = pos2;
                        str_len = index2 - index1 + 1;
                    }

                    if(pos2 == str1_len - 1) {
                        loop = false;
                        break;
                    } else {
                        flag = false;
                        pos2++;
                        break;
                    }
                }
            }
        }
    }

    if(index1 == -1) {
        cout << "no substring exists" << endl;
        return -1;
    }

    cout << str1.substr(index1, str_len).c_str() << endl;
    return 1;
}

int main() {
    int t;

    cin >> t;
    cin.ignore(10, '\n');

    for(int _ = 0; _ < t; _++) {
        string input;
        getline(cin, input);
        
        int index = input.find(',');
        string str1 = input.substr(0, index);
        string str2 = input.substr(index + 1);

        substring(str1, str2);
    }

    return 0;
}