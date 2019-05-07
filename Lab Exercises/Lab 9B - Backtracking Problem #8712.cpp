#include <iostream>
#include <vector>
#include <string>

using namespace std;

int max_words(vector<string> dict, string str, int words = 0) {
    int maxwords = words;

    if(str.empty()) return maxwords;

    for(int i = 0; i < dict.size(); i++) {
        if(str.find(dict[i]) == 0) {
            int depth_tmp = max_words(dict, str.substr(dict[i].length()), words + 1);
            if(maxwords < depth_tmp) maxwords = depth_tmp;
        }
    }

    return maxwords;
}

int main() {
    int t;
    cin >> t;

    for(int _ = 0; _ < t; _++) {
        int n;
        vector<string> dict;
        string str;

        cin >> n;
        
        for(int _ = 0; _ < n; _++) {
            string s;
            cin >> s;
            dict.push_back(s);
        }

        cin >> str;

        cout << max_words(dict, str) << '\n';
    }
}