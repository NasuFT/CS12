#include <iostream>
using namespace std;

int main() {
    int take, product = 1; 
    
    cin >> take;
    if (take == 0) {
        cout << "0";
        return 0;
    } else {
        while (take != 0) {
            product *= take;
            cin >> take;
        }
        
        cout << product;
        return 0;
    }
}