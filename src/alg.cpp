// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prioritet(char v) {
    int res = -1;
    switch (v) {
    case '(': res = 0;
        break;
    case ')': res = 1;
        break;
    case '+': res = 2;
        break;
    case '-': res = 2;
        break;
    case '*': res = 3;
        break;
    case '/': res = 3;
        break;
    }
    return res;
}

bool is_digit(char s) {
    bool res = false;
    if (s >= '0' && s <= '9') {
        res = true;
    }
    return res;
}

int calculator(char v, int a, int b) {
    int res = 0;
    switch (v) {
    case '*': res = a * b;
        break;
    case '/': res = a / b;
        break;
    case '-': res = a - b;
        break;
    case '+': res = a + b;
        break;
    }
    return res;
}

std::string infx2pstfx(std::string inf) {
    TStack <char, 100> S;
    std::string out;
    int i = 0, j = 0;
    int pr = 0;
    for (; inf[i] != '\0'; i++) {
        pr = prioritet(inf[i]);
        if (is_digit(inf[i])) {
            out.push_back(inf[i]);
        } else if (pr != -1) {
            if (out.length() != 0 && is_digit(out.back())) {
                out.push_back(' ');
            }
            if (pr == 1) {
                while (S.get() != '(' && !S.isEmpty()) {
                    out.push_back(S.get());
                    S.pop();
                }
                if (S.get() == '(') {
                    S.pop();
                }
            } else if (pr == 0 || pr > prioritet(S.get()) || S.isEmpty()) {
                S.push(inf[i]);
            } else {
                while (!S.isEmpty() && prioritet(S.get()) >= pr) {
                    out.push_back(S.get());
                    S.pop();
                }
                if (pr == 2 || pr == 3) {
                    S.push(inf[i]);
                }
            }
        }
    }
    while (!S.isEmpty()) {
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
    int dig = -1;
    int len = out.length();
    while (i < len) {
        if (prioritet(out[i]) == 2 || prioritet(out[i]) == 3) {
            if (dig == -1) {
                b = S.get();
                S.pop();
            } else {
                b = dig;
                dig = -1;
            }
            a = S.get();
            S.pop();
            S.push(calculator(out[i], a, b));
        } else if (out[i] == ' ') {
            S.push(dig);
            dig = -1;
        } else {
            if (is_digit(out[i])) {
                if (dig == -1) {
                    dig = 0;
                }
                dig = dig * 10 + static_cast<int>(out[i]) - 48;
            }
        }
        i++;
    }
    result = S.get();
    return result;
}
