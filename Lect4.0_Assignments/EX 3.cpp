#include <iostream>

using namespace std;

bool isValid(string s) {
    char stack[1000]; 
    int top = -1;     
    int a = s.length(); 
    for (int i = 0; i < a; i++) {
        char c = s[i];

        if (c == '(' || c == '[' || c == '{') {
            stack[++top] = c;  
        } else {
          
            if (top == -1) return false;

            if ((c == ')' && stack[top] == '(') || 
                (c == ']' && stack[top] == '[') || 
                (c == '}' && stack[top] == '{')) {
                top--; 
            } else {
                return false;  
            }
        }
    }

    return (top == -1); 
}

int main() {
    string s;
    cin >> s;

    if (isValid(s))
        cout << "Valid" << endl;
    else
        cout << "Invalid" << endl;

    return 0;
}

