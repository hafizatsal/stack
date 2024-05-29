#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

bool isOperator(char c){
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

int getPriority(char op){
    switch (op){
        case '+': case '-': return 1;
        case '*': case '/': case '%': return 2;
        default: return 0;
    }
}

vector<string> infixToPostfix(vector<string>& tokens){
    stack<string> ops;
    vector<string> output;
    
    for (string& token : tokens){
        if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1]))) {
            output.push_back(token);
        }else if (token == "("){
            ops.push(token);
        }else if (token == ")") {
            while (!ops.empty() && ops.top() != "("){
                output.push_back(ops.top());
                ops.pop();
            }
            if (!ops.empty()) ops.pop();
        }else if (isOperator(token[0])){
            while (!ops.empty() && getPriority(ops.top()[0]) >= getPriority(token[0])){
                output.push_back(ops.top());
                ops.pop();
            }
            ops.push(token);
        }
    }
    while (!ops.empty()){
        output.push_back(ops.top());
        ops.pop();
    }
    return output;
}

