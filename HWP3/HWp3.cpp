// #include <bits/stdc++.h>
#include <string.h>

#include <algorithm>
#include <iostream>

#include "queue.h"
#include "stack.h"
#include "tree.h"
#ifdef _WIN32
#define cl "cls"
#define wait system("pause");
#else
#define cl "clear"
#define wait                                    \
    printf("Press Enter key to continue...\n"); \
    fgetc(stdin);                               \
    fflush(stdin);                              \
    system(cl);
#endif
// using namespace std;
bool test(char* str) {
    int64_t cnt = 0;
    bool ret = 0;
    for (int i = 0; str[i] != 0x00; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            if (ret) return 0;
            if (i - 1 >= 0 && str[i - 1] == ')') return 0;
            ret = 1;
        } else {
            if (!ret) {
                if (str[i] != '(' && !(i - 1 >= 0 && str[i - 1] == ')')) {
                    printf("1\n");
                    return 0;
                }
            }
            if (i - 1 >= 0 && str[i - 1] >= '0' && str[i - 1] <= '9' &&
                str[i] == '(') {
                printf("2\n");
                return 0;
            }

            ret = 0;
            if (str[i] == '(') {
                cnt++;
            } else if (str[i] == ')') {
                cnt--;
                if (cnt < 0) {
                    printf("3\n");
                    return 0;
                }
            }
        }
    }
    return cnt == 0 && ret;
}
int32_t priority(char now) {
    switch (now) {
        case '(':
            return 0;
        case '+':
        case '-':
            return 12;
        case '*':
        case '/':
            return 13;
        case ')':
            return 19;
        default:
            return -1;
    }
}
int main() {
    Stack<Tree> num;
    Stack<char> Sign;
    char input[100];
    while (1) {
        printf("Please enter an infix expression and press enter:\n");
        if (!(~(scanf("%s", input)))) {
            printf("stop\n");
            return 0;
        }
        if (!test(input)) {
            printf("Wrong input\n");
            wait system(cl);
        } else {
            for (int i = 0; input[i] != 0x00; ++i) {
                if (input[i] >= '0' && input[i] <= '9') {
                    Tree number;
                    number.setUp(input[i]);
                    num.push(number);
                } else {
                    if (Sign.empty()) {
                        Sign.push(input[i]);
                    } else {
                        if (input[i] == ')') {
                            while (Sign.top() != '(') {
                                char tmp = Sign.top();
                                Sign.pop();
                                Tree A;
                                A = num.top();
                                num.pop();
                                Tree B;
                                B = num.top();
                                num.pop();
                                num.push(A.merge(B, A, tmp));
                            }
                            Sign.pop();
                        } else if (input[i] != '(') {
                            while (priority(Sign.top()) >= priority(input[i])) {
                                char tmp = Sign.top();
                                Sign.pop();
                                if (tmp == '(') {
                                    Sign.push(tmp);
                                    break;
                                } else {
                                    Tree A;
                                    A = num.top();
                                    num.pop();
                                    Tree B;
                                    B = num.top();
                                    num.pop();
                                    num.push(A.merge(B, A, tmp));
                                }
                            }
                        }
                        if (input[i] != ')') {
                            Sign.push(input[i]);
                        }
                    }
                }
            }
            while (!Sign.empty()) {
                Tree A;
                A = num.top();
                num.pop();
                Tree B;
                B = num.top();
                num.pop();
                num.push(A.merge(B, A, Sign.top()));
                Sign.pop();
            }
            Tree ans;
            ans = num.top();
            printf("The postfix expression: %s\n", ans.postfix(*(ans.Root())));
            printf("The prefix expression: %s\n", ans.prefix(*(ans.Root())));
            printf("The level-order expression: %s\n", ans.level_order());
            printf("= %lf\n", ans.calculation(ans.Root()));
            while (!num.empty()) num.pop();
            while (!Sign.empty()) Sign.pop();
            wait system(cl);
        }
    }
    return 0;
}