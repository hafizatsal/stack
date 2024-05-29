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

vector<string> tokenize(const string& infix){
    vector<string> tokens;
    size_t i = 0;
    while (i< infix.size()){
        if (isspace(infix[i])){
            i++;
            continue;
        }
        
        if (isdigit(infix[i])){
            string num;
            while (i < infix.size() && isdigit(infix[i])){
                num += infix[i++];
            }
            tokens.push_back(num);
        }else if (isOperator(infix[i])){
            if (infix[i] == '-' && (i == 0 || isOperator(infix[i-1]) || infix[i-1] == '(')){
                tokens.push_back("-1");
                tokens.push_back("*");
                i++;
            }else{
                tokens.push_back(string(1, infix[i++]));
            }
        }else if (infix[i] == '(' || infix[i] == ')'){
            tokens.push_back(string(1, infix[i++]));
        }else{
            i++;
        }
    }
    return tokens;
}

int main() {
    string infix;
    getline(cin, infix);
    
    vector<string> tokens = tokenize(infix);
    vector<string> postfix = infixToPostfix(tokens);
    
    for (size_t i=0; i<postfix.size(); ++i){
        if(i>0) cout << " ";
        cout << postfix[i];
    }
    cout << endl;
    
    return 0;
}

