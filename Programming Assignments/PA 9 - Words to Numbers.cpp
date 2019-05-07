#include <iostream>
#include <string>

using namespace std;

void printNum(int num) {
    if(num == 1000000) cout << "1,000,000" << endl;
    else if(num >= 1000) {
        int pad = 0;

        if(num % 100 == num % 1000) pad++;
        if(num % 10 == num % 1000) pad++;

        cout << num / 1000 << ",";

        for(int i = 0; i < pad; i++) cout << "0";

        cout << num % 1000 << endl;
    } else cout << num << endl;
}

int wordsToNumber(string str) {
    if(str[0] == ' ') str = str.substr(1);

    if(str.find("million") != string::npos) return 1000000;
    else if(str.find("thousand") != string::npos) {
        int index = str.find("thousand");
        return wordsToNumber(str.substr(0, index)) * 1000 + wordsToNumber(str.substr(index + 8));
    } else if(str.find("hundred") != string::npos) {
        int index = str.find("hundred");
        return wordsToNumber(str.substr(0, index)) * 100 + wordsToNumber(str.substr(index + 7));
    } else if(str.find("ninety") != string::npos) {
        int index = str.find("ninety");
        return 90 + wordsToNumber(str.substr(index + 6));
    } else if(str.find("eighty") != string::npos) {
        int index = str.find("eighty");
        return 80 + wordsToNumber(str.substr(index + 6));
    } else if(str.find("seventy") != string::npos) {
        int index = str.find("seventy");
        return 70 + wordsToNumber(str.substr(index + 7));
    } else if(str.find("sixty") != string::npos) {
        int index = str.find("sixty");
        return 60 + wordsToNumber(str.substr(index + 5));
    } else if(str.find("fifty") != string::npos) {
        int index = str.find("fifty");
        return 50 + wordsToNumber(str.substr(index + 5));
    } else if(str.find("forty") != string::npos) {
        int index = str.find("forty");
        return 40 + wordsToNumber(str.substr(index + 5));
    } else if(str.find("thirty") != string::npos) {
        int index = str.find("thirty");
        return 30 + wordsToNumber(str.substr(index + 6));
    } else if(str.find("twenty") != string::npos) {
        int index = str.find("twenty");
        return 20 + wordsToNumber(str.substr(index + 6));
    }

    else if(str.find("nineteen") != string::npos) return 19;
    else if(str.find("eighteen") != string::npos) return 18;
    else if(str.find("seventeen") != string::npos) return 17;
    else if(str.find("sixteen") != string::npos) return 16;
    else if(str.find("fifteen") != string::npos) return 15;
    else if(str.find("fourteen") != string::npos) return 14;
    else if(str.find("thirteen") != string::npos) return 13;
    else if(str.find("twelve") != string::npos) return 12;
    else if(str.find("eleven") != string::npos) return 11;
    else if(str.find("ten") != string::npos) return 10;
    else if(str.find("nine") != string::npos) return 9;
    else if(str.find("eight") != string::npos) return 8;
    else if(str.find("seven") != string::npos) return 7;
    else if(str.find("six") != string::npos) return 6;
    else if(str.find("five") != string::npos) return 5;
    else if(str.find("four") != string::npos) return 4;
    else if(str.find("three") != string::npos) return 3;
    else if(str.find("two") != string::npos) return 2;
    else if(str.find("one") != string::npos) return 1;

    return 0;
}

int main() {
    int t;
    cin >> t;
    cin.ignore(10, '\n');

    for(int _ = 0; _ < t; _++) {
        string str;
        getline(cin, str);

        printNum(wordsToNumber(str));
    }

    return 0;
}