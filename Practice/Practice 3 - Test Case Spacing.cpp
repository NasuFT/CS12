#include <iostream>
#include <string>

using namespace std;

int main() {
    int n, k;
    string str;
    
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cout << "Test Case #" << i + 1 << ":" << endl;
        cin >> k;
        
        for (int j = 0; j < k; j++) {
            cin >> str;
            cout << str << endl;
        }
        
        cout << endl;
    }
    
    return 0;
}