#include <iostream>

using namespace std;

/*
    PROBLEMS:

    -PARSING DATA
*/

int pow(int num1, int num2) {
    int result = 1;

    for(int i = 0; i < num2; i++) {
        result *= num1;
    }

    return result;
}

int length(char *str) {
    int k = 0;
    while(str[k] != '\0') k++;
    return k;
}

int charToNum(char *str) {
    int num = 0;

    for(int i = length(str); i > 0; i--) {
        num += (str[i - 1] - '0') * pow(10, length(str) - i);
    }

    return num;
}

char *concat(char *str1, char *str2) {
    int str1_len = length(str1);
    int str2_len = length(str2);

    char *str = new char [str1_len + str2_len + 1];

    for(int i = 0; i < str1_len; i++) {
        str[i] = str1[i];
    }

    for(int i = 0; i < str2_len; i++) {
        str[i + str1_len] = str2[i];
    }

    str[str1_len + str2_len] = '\0';

    return str;
}

char *erase(char *str1, int index, int len) {
    int str1_length = length(str1);
    char *str = new char[str1_length - len];

    for(int i = 0; i < (str1_length - len); i++) {
        if(i < index) str[i] = str1[i];
        else str[i] = str1[i + len];
    }

    return str;
}

int find(char *str1, char *str2) {
    for(int i = 0; i < length(str1) - length(str2) + 1; i++) {
        if(str2[0] == str1[i]) {
            if(length(str2) == 1) return i;
            else {
                for(int j = 1; j < length(str2); j++) {
                    if(str2[j] != str1[i + j]) break;
                    if(j == length(str2) - 1) return i;
                } 
            }
        }
    }

    return -1;
}

char* pop_back(char *str) {
    char *str_pop = new char [length(str)];

    for(int i = 0; i < length(str) - 1; i++) {
        str_pop[i] = str[i];
    }

    str_pop[length(str) - 1] = '\0';

    return str_pop;
}

char at(char *str, int index) {
    return str[index];
}

char *substr(char *str, int start, int length) {
    char *str_sub = new char [length + 1];
    for(int i = 0; i < length; i++) {
        str_sub[i] = str[start + i];
    }

    str_sub[length] = '\0';

    return str_sub;
}

void parse(char *str) {
    char __quote[] = {'"', 0};
    char __comma[] = {',', 0};
    char __function1[] = "length";
    char __function2[] = "pop_back";
    char __function3[] = "concat";
    char __function4[] = "at";
    char __function5[] = "find";
    char __function6[] = "substr";
    char __function7[] = "erase";


    if(find(str, __function1) != -1) {
        int index = find(str, __quote);
        char *substring = substr(str, index + 1, length(str) - index - 3);

        cout << length(substring) << endl;
    } else if(find(str, __function2) != -1) {
        int index = find(str, __quote);
        char *substring = substr(str, index + 1, length(str) - index - 3);

        cout << pop_back(substring) << endl;
    } else if(find(str, __function3) != -1) {
        int index1 = find(str, __quote);
        char *substring = substr(str, index1 + 1, length(str) - index1 - 1);
        index1 = find(substring, __quote);
        char *str1 = substr(substring, 0, index1);
        substring = substr(substring, index1 + 2, length(substring) - index1 - 3);
        index1 = find(substring, __quote);
        char *str2 = substr(substring, index1 + 1, length(substring) - index1 - 2);

        cout << concat(str1, str2) << endl;
    } else if(find(str, __function4) != -1) {
        int index1 = find(str, __quote);
        char *substring = substr(str, index1 + 1, length(str) - index1 - 1);
        index1 = find(substring, __quote);
        char *str1 = substr(substring, 0, index1);
        substring = substr(substring, index1 + 2, length(substring) - index1 - 3);
        int num = charToNum(substring);
        
        cout << at(str1, num) << endl;
    } else if(find(str, __function5) != -1) {
        int index1 = find(str, __quote);
        char *substring = substr(str, index1 + 1, length(str) - index1 - 1);
        index1 = find(substring, __quote);
        char *str1 = substr(substring, 0, index1);
        substring = substr(substring, index1 + 2, length(substring) - index1 - 3);
        index1 = find(substring, __quote);
        char *str2 = substr(substring, index1 + 1, length(substring) - index1 - 2);

        cout << find(str1, str2) << endl;
    } else if(find(str, __function6) != -1) {
        int index1 = find(str, __quote);
        char *substring = substr(str, index1 + 1, length(str) - index1 - 1);
        index1 = find(substring, __quote);
        char *str1 = substr(substring, 0, index1);
        substring = substr(substring, index1 + 2, length(substring) - index1 - 3);
        index1 = find(substring, __comma);
        int num1 = charToNum(substr(substring, 0, index1));
        substring = substr(substring, index1 + 1, length(substring) - index1 - 1);
        int num2 = charToNum(substring);

        cout << substr(str1, num1, num2) << endl;
    } else if(find(str, __function7) != -1) {
        int index1 = find(str, __quote);
        char *substring = substr(str, index1 + 1, length(str) - index1 - 1);
        index1 = find(substring, __quote);
        char *str1 = substr(substring, 0, index1);
        substring = substr(substring, index1 + 2, length(substring) - index1 - 3);
        index1 = find(substring, __comma);
        int num1 = charToNum(substr(substring, 0, index1));
        substring = substr(substring, index1 + 1, length(substring) - index1 - 1);
        int num2 = charToNum(substring);

        cout << erase(str1, num1, num2) << endl;
    }
}

int main() {
    int t;

    cin >> t;
    cin.ignore(10, '\n');
    char str[512];

    for(int _ = 0; _ < t; _++) {
        cin.getline(str, 512);

        parse(str);
    }

    return 0;
}