#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> permute(string str) {
    vector<string> ret;

    if(str.length() == 1) {
        ret.push_back(str);
        return ret;
    }

    vector<string> temp = permute(str.substr(1));

    for(int i = 0; i < str.length(); i++) {
        for(int j = 0; j < temp.size(); j++) {
            string str2 = temp[j];
            str2.insert(str2.begin() + i, str[0]);
            ret.push_back(str2);
        }
    }

    return ret;
}

template <class T>
void print_vector(vector<T> arr) {
    for(int i = 0; i < arr.size(); i++) {
        cout << arr[i] << '\n';
    } 
}

int main() {
    string str = "AIH";
    print_vector<string>(permute(str));
    return 0;
}