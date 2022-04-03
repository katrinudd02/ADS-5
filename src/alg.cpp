// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
#include <iostream>
#include <cctype>
#include <stdlib.h>
#include <conio.h>
#include <cstdio>
#include <stack>

using namespace std;

int prioritet(char v)
{
    switch (v)
    {
    case '(': return 1;
    case '+':
    case '-': return 2;
    case '*':
    case '/': return 3;
    }
}

bool is_op(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

std::string infx2pstfx(std::string inf) {
    stack <char> S;
    char* out[256];
    //int c = getchar(inf);
    int i = 0, j = 0;
    for (; inf[i] != '\0'; ++i)
    {
        if (is_digit(inf[i]))
        {
            out[j] = inf[i];
            ++j;
        }
        else
        {
            if (j != 0 && out[j - 1] >= '0' && out[j - 1] <= '9')
            {
                out[j] = '_';
                ++j;
            }

            if (is_op(inf[i]))
            {
                if (S.empty() || prioritet(S.top()) < prioritet(inf[i]))
                {
                    S.push(inf[i]);
                }
                else
                {
                    while (!S.empty() && (prioritet(S.top()) >= prioritet(inf[i])))
                    {
                        out[j++] = S.top();
                        S.pop();
                    }
                    S.push(inf[i]);
                }
            }
            else
            {
                if (inf[i] == '(')
                {
                    S.push(inf[i]);
                }
                else
                {
                    if (inf[i] == ')')
                    {
                        if (S.empty() || S.top() == '(')
                        {
                            cout << "Input error!";
                            _getch();
                            exit(1);
                        }
                        else
                        {
                            while (S.top() != '(')
                            {
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
    while (!S.empty())
    {
        if (S.top() == '(')
        {
            cout << "Input error!";
            _getch(); exit(1);
        }
        else
        {
            out[j] = S.top();
            S.pop();
            j++;
        }
    }

}

int eval(std::string out)
{
    int j = 0, c = 0, r1 = 0, r2 = 0;
    stack <double> S;
    stack <double> S1;
    char num[256];
    char* pEnd = nullptr;
    while (out[j] != '\0')
    {
        if (out[j] == '_') {
            ++j;
            continue;
        }
        if (out[j] >= '0' && out[j] <= '9')
        {
            long iNum = strtol(&out[j], &pEnd, 10);
            S.push(iNum);
            j += pEnd - &out[j];
        }
        else
        {
            if (is_op(out[j]))
            {
                r1 = S.top(); S.pop();
                r2 = S.top(); S.pop();
                switch (out[j])
                {
                case '+': S.push(r2 + r1); break;
                case '-': S.push(r2 - r1); break;
                case '*': S.push(r2 * r1); break;
                case '/': S.push(r2 / r1); break;
                }
            }
            ++j;
        }
    }
    return 0;
}
