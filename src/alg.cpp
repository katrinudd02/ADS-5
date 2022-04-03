// Copyright 2021 NNTU-CS
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

bool is_op(std::string pref) {
    for (size_t i = 0; i < pref.size(); ++i) {
        if (pref[i] == '+' || pref[i] == '-' || pref[i] == '*' || pref[i] == '/')
            return true;
    }
    return false;
}

bool is_digit(std::string pref) {
    for (size_t i = 0; i < pref.size(); ++i) {
        if (pref[i] < '0' || pref[i] > '9')
            return false;
    }
    return true;
}

int calculator(char symbol, int a, int b) {
    if (symbol == '+') {
        return (a + b);
    } else if (symbol == '-') {
        return (b - a);
    } else if (symbol == '*') {
        return (a * b);
    } else if ((symbol == '/') && (a != 0)) {
        return (b / a);
    } else {
        return 0;
    }
}

std::string infx2pstfx(std::string inf) {
    TStack <char, 100> S;
    std::string out;
    int i = 0, j = 0;
    for (; inf[i] != '\0'; i++) {
        int pr = prioritet(inf[i]);
        if (pr == -1) {
            if (!out.empty() && prioritet(inf[i - 1]) != -1) {
                out.push_back(' ');
            }
            out.push_back(inf[i]);
        } else if (pr == 0 || pr > prioritet(S.get()) || S.isEmpty()) {
            out.push_back(inf[i]);
        } else {
            if (pr == 1) {
                while (S.get() != '(') {
                    out.push_back(' ');
                    out.push_back(S.get());
                    S.pop();
                }
                S.pop();
            } else {
                while (prioritet(S.get()) >= pr) {
                    out.push_back(' ');
                    out.push_back(S.get());
                    S.pop();
                }
                S.push(inf[i]);
            }
        }
    }
    while (!S.isEmpty()) {
        out.push_back(' ');
        out.push_back(S.get());
        S.pop();
    }
    return out;
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
            resultStack.push(calculator(out[i], a, b));
        }
    }
    result = resultStack.get();
    return result;
}
