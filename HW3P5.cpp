#include <bits/stdc++.h>
#define ll long long

using namespace std;
char input[10000];
int priority_stack[300];
stack<string> number;
stack<int> sign;
void fun(int now, int r) {
    if (r) {
        while (sign.top() != '(') {
            string b = number.top();
            number.pop();
            string a = number.top();
            number.pop();
            number.push(sign.top() + a + b);
            sign.pop();
        }
        sign.pop();
    } else {
        while (priority_stack[input[now]] <= priority_stack[sign.top()]) {
            string b = number.top();
            number.pop();
            string a = number.top();
            number.pop();
            number.push(sign.top() + a + b);
            sign.pop();
        }
    }
}
void reset() {
    priority_stack['('] = 0;
    priority_stack['+'] = 12;
    priority_stack['-'] = 12;
    priority_stack['*'] = 13;
    priority_stack['/'] = 13;
    priority_stack['%'] = 13;
    priority_stack[')'] = 19;
}
int main() {
    int i = 0;
    reset();
    scanf("%s", input);
    sign.push('(');
    for (i = 0; input[i] != 0x00; ++i) {
        if ((input[i] <= '9' && input[i] >= 0) ||
            (input[i] >= 'A' && input[i] <= 'Z') ||
            (input[i] >= 'a' && input[i] <= 'z')) {
            number.push(i);
        } else if (input[i] == '(') {
            sign.push(i);
        } else if (input[i] == ')') {
            fun(i, 1);
        } else {
            if (priority_stack[input[i]] <= priority_stack[sign.top()]) {
                fun(i, 0);
            }
            sign.push(i)
        }
    }
    input[i] = ')';
    fun(i, 1);
    printf("%s", number.top());
    return 0;
}