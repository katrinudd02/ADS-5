#include <string>
#include <map>
#include "tstack.h"

int prioritet(char v) {
    switch (v) {
        case '(':
        case ')': return 1;
        case '+':
        case '-': return 2;
        case '*':
        case '/': return 3;
    }
    return -1;
}

bool is_op(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

int calculator(char symbol, int a, int b) {
    if (symbol == '+') {
        return (a + b);
    } else if (symbol == '-') {
        return (b - a);
    } else if (sembol == '*') {
        return (a * b);
    } else if ((symbol == '/') && (a != 0)) {
        return (b / a);
    } else {
        return 0;
    }
}

std::string infx2pstfx(std::string inf) {
    stack <char> S;
    std::string out;
    //int c = getchar(inf);
    int i = 0, j = 0;
    for (; inf[i] != '\0'; ++i) {
        if (is_digit(inf[i])) {
            out[j] = inf[i];
            ++j;
        } else {
            if (j != 0 && out[j - 1] >= '0' && out[j - 1] <= '9') {
                out[j] = '_';
                ++j;
            }
            if (is_op(inf[i])) {
                if (S.empty() || prioritet(S.top()) < prioritet(inf[i])) {
                    S.push(inf[i]);
                } else {
                    while (!S.empty() && (prioritet(S.top()) 
                                          >= prioritet(inf[i]))) {
                        out[j++] = S.top();
                        S.pop();
                    }
                    S.push(inf[i]);
                }
            } else {
                if (inf[i] == '(') {
                    S.push(inf[i]);
                } else {
                    if (inf[i] == ')') {
                        if (S.empty() || S.top() == '(') {
                            cout << "Input error!";
                            _getch();
                            exit(1);
                        } else {
                            while (S.top() != '(') {
                                out[j] = S.top();
                                S.pop();
                                j++;
                            }
                        }
                        S.pop();
                    }
                }
            }
        }
    }
    while (!S.empty()) {
        if (S.top() == '(') {
            cout << "Input error!";
            _getch(); exit(1);
        } else {
            out[j] = S.top();
            S.pop();
            j++;
        }
    }
}

int eval(std::string out) {
    int result = 0;
    TStack <int, 100> resultStack;
    int i = 0;
    int a = 0;
    int b = 0;
    for (; i < out.size(); i++) {
        if (prioritet(out[i]) == -1) {
            resultStack.push(out[i] - '0');
        } else if (prioritet(out[i]) < 4) {
            a = resultStack.get();
            resultStack.pop();
            b = resultStack.get();
            resultStack.pop();
            resultStack.push(calculator(out[k], a, b));
        }
    }
    result = resultStack.get();    
    return result;
}
