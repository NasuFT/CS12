#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    int tw;
    cin >> tw;
    cin.ignore();
    set<string> cs12_takers;

    for(int i = 0; i < tw; i++) {
        string name;
        getline(cin, name);
        cs12_takers.insert(name);
    }

    int th;
    cin >> th;
    cin.ignore();
    set<string> cs31_takers;

    for(int i = 0; i < th; i++) {
        string name;
        getline(cin, name);
        cs31_takers.insert(name);
    }

    int pw;
    cin >> pw;
    cin.ignore();
    set<string> cs12_passers;

    for(int i = 0; i < pw; i++) {
        string name;
        getline(cin, name);
        cs12_passers.insert(name);
        cs12_takers.insert(name);
    }

    int ph;
    cin >> ph;
    cin.ignore();
    set<string> cs31_passers;

    for(int i = 0; i < ph; i++) {
        string name;
        getline(cin, name);
        cs31_passers.insert(name);
        cs31_takers.insert(name);
    }

    set<string> total_takers;
    set<string> cs1231_takers;
    set<string> cs1231_passers;
    set<string> dualtaker_cs12passer;
    set<string> dualtaker_cs12onlypasser;
    set<string> dualtaker_cs31passer;
    set<string> dualtaker_cs31onlypasser;
    set<string> cs1231_failers;
    set<string> cs1231_failers2;
    set<string> cs12only_takers;
    set<string> cs12only_passers;
    set<string> cs31only_takers;
    set<string> cs31only_passers;
    set_union(cs12_takers.begin(), cs12_takers.end(), cs31_takers.begin(), cs31_takers.end(), inserter(total_takers, total_takers.begin()));
    set_intersection(cs12_takers.begin(), cs12_takers.end(), cs31_takers.begin(), cs31_takers.end(), inserter(cs1231_takers, cs1231_takers.begin()));
    set_intersection(cs12_passers.begin(), cs12_passers.end(), cs31_passers.begin(), cs31_passers.end(), inserter(cs1231_passers, cs1231_passers.begin()));
    set_intersection(cs1231_takers.begin(), cs1231_takers.end(), cs12_passers.begin(), cs12_passers.end(), inserter(dualtaker_cs12passer, dualtaker_cs12passer.begin()));
    set_difference(dualtaker_cs12passer.begin(), dualtaker_cs12passer.end(), cs31_passers.begin(), cs31_passers.end(), inserter(dualtaker_cs12onlypasser, dualtaker_cs12onlypasser.begin()));
    set_intersection(cs1231_takers.begin(), cs1231_takers.end(), cs31_passers.begin(), cs31_passers.end(), inserter(dualtaker_cs31passer, dualtaker_cs31passer.begin()));
    set_difference(dualtaker_cs31passer.begin(), dualtaker_cs31passer.end(), cs12_passers.begin(), cs12_passers.end(), inserter(dualtaker_cs31onlypasser, dualtaker_cs31onlypasser.begin()));
    set_difference(cs1231_takers.begin(), cs1231_takers.end(), cs12_passers.begin(), cs12_passers.end(), inserter(cs1231_failers, cs1231_failers.begin()));
    set_difference(cs1231_failers.begin(), cs1231_failers.end(), cs31_passers.begin(), cs31_passers.end(), inserter(cs1231_failers2, cs1231_failers2.begin()));
    set_difference(cs12_takers.begin(), cs12_takers.end(), cs31_takers.begin(), cs31_takers.end(), inserter(cs12only_takers, cs12only_takers.begin()));
    set_intersection(cs12only_takers.begin(), cs12only_takers.end(), cs12_passers.begin(), cs12_passers.end(), inserter(cs12only_passers, cs12only_passers.begin()));
    set_difference(cs31_takers.begin(), cs31_takers.end(), cs12_takers.begin(), cs12_takers.end(), inserter(cs31only_takers, cs31only_takers.begin()));
    set_intersection(cs31only_takers.begin(), cs31only_takers.end(), cs31_passers.begin(), cs31_passers.end(), inserter(cs31only_passers, cs31only_passers.begin()));
    
    cout << "Total students: " << total_takers.size() << "\n";
    cout << "Passing both: " << cs1231_passers.size() << " / " << cs1231_takers.size() << "\n";
    cout << "Taking both, but passing only CS 12: " << dualtaker_cs12onlypasser.size() << " / " << cs1231_takers.size() << "\n";
    cout << "Taking both, but passing only CS 31: " << dualtaker_cs31onlypasser.size() << " / " << cs1231_takers.size() << "\n";
    cout << "Failing both: " << cs1231_failers2.size() << " / " << cs1231_takers.size() << "\n";
    cout << "Taking and passing only CS 12: " << cs12only_passers.size() << " / " << cs12only_takers.size() << "\n";
    cout << "Taking and passing only CS 31: " << cs31only_passers.size() << " / " << cs31only_takers.size() << "\n";

    return 0;
}