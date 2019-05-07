#include <iostream>
#include <string>

using namespace std;

string toWords(int n, bool capitalized = false) {
    if (n >= 1000) {
        if (n % 1000 != 0) return (toWords(n / 1000, true) + " thousand " + toWords(n % 1000));
        else return (toWords(n / 1000, true) + " thousand ");
    } else if (n >= 100) {
        if(capitalized) {
            if (n % 100 != 0) return toWords(n / 100, true) + " hundred " + toWords(n % 100);
            else return toWords(n / 100, true) + " hundred";
        } else {
            if (n % 100 != 0) return toWords(n / 100) + " hundred " + toWords(n % 100);
            else return toWords(n / 100) + " hundred";
        }
    } else if (n >= 20) {
        if(n >= 90) {
            if (n % 90 != 0) return (capitalized ? "Ninety " + toWords(n % 90) : "ninety " + toWords(n % 90));
            else return (capitalized ? "Ninety" : "ninety");
        } else if(n >= 80) {
            if (n % 80 != 0) return (capitalized ? "Eighty " + toWords(n % 80) : "eighty " + toWords(n % 80));
            else return (capitalized ? "Eighty" : "eighty");
        } else if(n >= 70) {
            if (n % 70 != 0) return (capitalized ? "Seventy " + toWords(n % 70) : "seventy " + toWords(n % 70));
            else return (capitalized ? "Seventy" : "seventy");
        } else if(n >= 60) {
            if (n % 60 != 0) return (capitalized ? "Sixty " + toWords(n % 60) : "sixty " + toWords(n % 60));
            else return (capitalized ? "Sixty" : "sixty");
        } else if(n >= 50) {
            if (n % 50 != 0) return (capitalized ? "Fifty " + toWords(n % 50) : "fifty " + toWords(n % 50));
            else return (capitalized ? "Fifty" : "fifty");
        } else if(n >= 40) {
            if (n % 40 != 0) return (capitalized ? "Forty " + toWords(n % 40) : "forty " + toWords(n % 40));
            else return (capitalized ? "Forty" : "forty");
        } else if(n >= 30) {
            if (n % 30 != 0) return (capitalized ? "Thirty " + toWords(n % 30) : "thirty " + toWords(n % 30));
            else return (capitalized ? "Thirty" : "thirty");
        } else {
            if (n % 20 != 0) return (capitalized ? "Twenty " + toWords(n % 20) : "twenty " + toWords(n % 20));
            else return (capitalized ? "Twenty" : "twenty");
        }
    } else {
        switch(n) {
            case 19:
                return (capitalized ? "Nineteen" : "nineteen");
            case 18:
                return (capitalized ? "Eighteen" : "eighteen");
            case 17:
                return (capitalized ? "Seventeen" : "seventeen");
            case 16:
                return (capitalized ? "Sixteen" : "sixteen");
            case 15:
                return (capitalized ? "Fifteen" : "fifteen");
            case 14:
                return (capitalized ? "Fourteen" : "fourteen");
            case 13:
                return (capitalized ? "Thirteen" : "thirteen");
            case 12:
                return (capitalized ? "Twelve" : "twelve");
            case 11:
                return (capitalized ? "Eleven" : "eleven");
            case 10:
                return (capitalized ? "Ten" : "ten");
            case 9:
                return (capitalized ? "Nine" : "nine");
            case 8:
                return (capitalized ? "Eight" : "eight");
            case 7:
                return (capitalized ? "Seven" : "seven");
            case 6:
                return (capitalized ? "Six" : "six");
            case 5:
                return (capitalized ? "Five" : "five");
            case 4:
                return (capitalized ? "Four" : "four");
            case 3:
                return (capitalized ? "Three" : "three");
            case 2:
                return (capitalized ? "Two" : "two");
            case 1:
                return (capitalized ? "One" : "one");
            case 0:
                return (capitalized ? "Zero" : "zero");
        }
    }
}

int main() {
    int t, n;

    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> n;

        cout << toWords(n, true).c_str() << endl;
    }

    return 0;
}