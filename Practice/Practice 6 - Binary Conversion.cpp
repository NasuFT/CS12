#include <string>

using namespace std;

string dec2bin(unsigned int n) {
    unsigned int quotient = n / 2;
    unsigned int remainder = n % 2;
    
    if(n == 0) return to_string(0);

    if (quotient == 0) {
        return to_string(1);
    }

    return dec2bin(quotient) + to_string(remainder);
}