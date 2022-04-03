// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prioritet(char v) {
    switch (v) {
        case '(': return 0;
        case ')': return 1;
        case '+': return 2;
        case '-': return 2;
        case '*': return 3;
        case '/': return 3;
    }
    return -1;
}

bool is_digit(std::string pref) {
    for (size_t i = 0; i < pref.size(); ++i) {
        if (pref[i] < '0' || pref[i] > '9')
            return false;
    }
    return true;
}

int calculator(char symbol, int a, int b) {
    switch (symbol) {
        case '*': return a * b;
        case '/': return a / b;
        case '-': return a - b;
        case '+': return a + b;
        default: return -1;
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
    TStack <int, 100> S;
    int result = 0;
    int i = 0;
    int a = 0;
    int b = 0;
    while (i < out.length()) {
        if (prioritet(out[i]) == -1) {
            if (out[i] != ' ') {
                S.push(out[i] - '0');
            }
        } else if (prioritet(out[i]) < 4) {
            a = S.get();
            S.pop();
            b = S.get();
            S.pop();
            S.push(calculator(out[i], b, a));
        }
        i++;
    }
    result = S.get();
    return result;
}
