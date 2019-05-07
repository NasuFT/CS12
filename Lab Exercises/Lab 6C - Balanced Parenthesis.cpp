#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool check(string &str) {
    stack<char> stack_str;
    stack<char> stack_str2;

    for(int i = 0; i < str.size(); i++) {
        stack_str.push(str[i]);
    }

    for(int i = 0; stack_str.size(); i++) {
        if(stack_str.top() == ')') {
            stack_str2.push('(');
        } else if(stack_str.top() == ']') {
            stack_str2.push('[');
        } else if(stack_str.top() == '}') {
            stack_str2.push('{');
        } else if(stack_str.top() == '(') {
            if(stack_str2.empty() || stack_str2.top() != '(') return false;
            else stack_str2.pop();
        } else if(stack_str.top() == '[') {
            if(stack_str2.empty() || stack_str2.top() != '[') return false;
            else stack_str2.pop();
        } else if(stack_str.top() == '{') {
            if(stack_str2.empty() || stack_str2.top() != '{') return false;
            else stack_str2.pop();
        }

        stack_str.pop();
    }

    if(stack_str2.empty()) return true;
    return false;
}

int main() {
    int t;
    cin >> t;

    for(int i = 0; i < t; i++) {
        string str;
        cin >> str;

        if(check(str)) cout << "BALANCED" << "\n";
        else cout << "NOT BALANCED" << "\n";
    }

    return 0;
}