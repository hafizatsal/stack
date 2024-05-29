#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cctype>
#include <sstream>

using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0;
}

vector<string> infixToPostfix(const string &expression) {
    stack<char> operators;
    vector<string> output;
    string number;
    
    for (size_t i = 0; i < expression.length(); ++i) {
        char token = expression[i];
        
        if (isspace(token)) {
            continue;
        }
        
        if (isdigit(token) || (token == '-' && (i == 0 || expression[i-1] == '(' || isspace(expression[i-1])))) {
            number += token;
            if (i == expression.length() - 1 || !isdigit(expression[i + 1])) {
                output.push_back(number);
                number.clear();
            }
        } else if (token == '(') {
            operators.push(token);
        } else if (token == ')') {
            while (!operators.empty() && operators.top() != '(') {
                output.push_back(string(1, operators.top()));
                operators.pop();
            }
            operators.pop();
        } else {
            while (!operators.empty() && precedence(operators.top()) >= precedence(token)) {
                output.push_back(string(1, operators.top()));
                operators.pop();
            }
            operators.push(token);
        }
    }
    
    while (!operators.empty()) {
        output.push_back(string(1, operators.top()));
        operators.pop();
    }
    
    return output;
}

int evaluatePostfix(const vector<string> &postfix) {
    stack<int> values;
    
    for (const auto &token : postfix) {
        if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {
            values.push(stoi(token));
        } else {
            int b = values.top(); values.pop();
            int a = values.top(); values.pop();
            
            if (token == "+") values.push(a + b);
            if (token == "-") values.push(a - b);
            if (token == "*") values.push(a * b);
            if (token == "/") values.push(a / b);
            if (token == "%") values.push(a % b);
        }
    }
    
    return values.top();
}

int evaluateExpression(const string &expression) {
    vector<string> postfix = infixToPostfix(expression);
    return evaluatePostfix(postfix);
}

int main() {
    string expression;
    getline(cin, expression);
    cout << evaluateExpression(expression) << endl;
    return 0;
}
