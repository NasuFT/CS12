#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;

pair<int, string> edit(string src, string dest) {
    string str;

    if(src.length() == 0 || dest.length() == 0) { // one of the strings is empty
        for(int i = 0; i < dest.length(); i++) {
            str += "add ";
            str += dest[i];
            str += '\n';
        }

        for(int i = 0; i < src.length(); i++) {
            str += "remove ";
            str += src[i];
            str += '\n';
        }

        return pair<int,string>(
            max(src.length(), dest.length()),
            str
        );
    }
    // Choice 1: Edit first character if needed
    pair<int,string> c1 = edit(src.substr(1), dest.substr(1));
    c1.first += (src[0] == dest[0] ? 0 : 1);
    if(src[0] != dest[0]) {
        str = "edit ";
        str += src[0];
        str += " to ";
        str += dest[0];
        str += '\n';
        c1.second.insert(0, str);
    }
    // Choice 2: Remove first character of src
    pair<int,string> c2 = edit(src.substr(1), dest);
    c2.first += 1;
    str = "remove ";
    str += src[0];
    str += '\n';
    c2.second.insert(0, str);

    // Choice 3 : Add a character to src
    pair<int,string> c3 = edit(src, dest.substr(1));
    c3.first += 1;
    str = "add ";
    str += dest[0];
    str += '\n';
    c3.second.insert(0, str);

    string which = c1.second;
    int mi = c1.first;
    if(c2.first < mi) {
        which = c2.second;
        mi = c2.first;
    }
    if(c3.first < mi) {
        which = c3.second;
        mi = c3.first;
    }

    return pair<int,string>(mi, which);
}


int main() {
    string str1("AGC");
    string str2("ATCG");
    pair<int, string> wheep = edit(str1, str2);
    cout << wheep.first << '\n' << wheep.second;
}