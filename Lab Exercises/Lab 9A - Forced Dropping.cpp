#include <iostream>
#include <string>

using namespace std;

int count(const char chr, string str) {
    int count = 0;

    while(str.find(chr) != string::npos) {
        str = str.substr(str.find(chr) + 1);
        count++;
    }

    return count;
}

void drop(int absences, int late_count, string tally = string()) {
    if(count('A', tally) + (count('L', tally) / late_count) >= absences) {
        cout << tally << '\n';
        return;
    }

    drop(absences, late_count, tally + "A");
    drop(absences, late_count, tally + "L");
}

int main() {
    int a, l;
    cin >> a >> l;
    drop(a, l);
    return 0;
}