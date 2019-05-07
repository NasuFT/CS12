#include <iostream>
#include <vector>
#include <math.h>
#include <errno.h>

// A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
// a^2 + b^2 = c^2
// For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.
// There exists exactly one Pythagorean triplet for which a + b + c = 1000.
// Find the product abc.

using namespace std;

double zeroOfQuadratic(int a = 0, int b = 0, int c = 0) {
    if(a == 0) return -1;
    double num = (-1 * b) - sqrt(pow(b, 2) - 4 * a * c);
    double dem = 2 * a;
    return num / dem;
}

vector<int> generatePythagoreanTriple(int num) {
    vector<int> triples;

    for(int i = 1; i < zeroOfQuadratic(-1, 0, num); i++) {
        int y = (num - i * i) / i;
        if((2 * i * i) + (2 * i * y) == num) {
            triples.push_back(abs(i * i - y * y));
            triples.push_back(2 * i * y);
            triples.push_back(i * i + y * y);
        }
    }

    return triples;
}

using namespace std;

int main() {
    vector<int> pairs = generatePythagoreanTriple(1000);

    for(int i = 0; i < pairs.size(); i++) {
        cout << pairs[i] << ' ';
    }

}