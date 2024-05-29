#include <iostream>
#include <string>
using namespace std;

string strToInfix (string& infix) {
	string formatedInfix = "";
	for (size_t i = 0; i < infix.length(); ++i) {
		char c = infix[i];
		
		if (c == '-' && (i == 0 || infix[i-1] == '(' )) {
			formatedInfix += c;
		
		} else if (c == '-' && i + 1 < infix.length() && infix[i+1] == '(' ) {
			formatedInfix += " -1 * ( ";
			++i;
		

		} else if (c == '-' || c == '+' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')') {
			formatedInfix += ' ';
			formatedInfix += c;
			formatedInfix += ' ';
			
		} else {
			formatedInfix += c;
		}
	}
	
	string result = "";
	bool space = false;
	for (char c : formatedInfix) {
		if (c == ' '){
			if (!space) {
				result += c;
				space = true;
			}
		} else {
			result += c;
			space = false;
		}
	}
	
	
	return result;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

int getPriority(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        default:
            return 0;
    }
}

vector<string> infixToPostfix(vector<string>& tokens) {
    stack<string> ops;
    vector<string> output;

    for (string& token : tokens) {
        if (isdigit(token[0]) || (token.size() > 1 && isdigit(token[1]))) {
            output.push_back(token);
        } else if (token == "(") {
            ops.push(token);
        } else if (token == ")") {
            while (!ops.empty() && ops.top() != "(") {
                output.push_back(ops.top());
                ops.pop();
            }
            if (!ops.empty()) ops.pop();
        } else if (isOperator(token[0])) {
            while (!ops.empty() && getPriority(ops.top()[0]) >= getPriority(token[0])) {
                output.push_back(ops.top());
                ops.pop();
            }
            ops.push(token);
        }
    }
    while (!ops.empty()) {
        output.push_back(ops.top());
        ops.pop();
    }
    return output;
}

vector<string> tokenize(const string& infix) {
    vector<string> tokens;
    size_t i = 0;
    while (i < infix.size()) {
        if (isspace(infix[i])) {
            i++;
            continue;
        }

        if (isdigit(infix[i])) {
            string num;
            while (i < infix.size() && isdigit(infix[i])) {
                num += infix[i++];
            }
            tokens.push_back(num);
        } else if (isOperator(infix[i])) {
            if (infix[i] == '-' && (i == 0 || isOperator(infix[i - 1]) || infix[i - 1] == '(')) {
                tokens.push_back("-1");
                tokens.push_back("*");
                i++;
            } else {
                tokens.push_back(string(1, infix[i++]));
            }
        } else if (infix[i] == '(' || infix[i] == ')') {
            tokens.push_back(string(1, infix[i++]));
        } else {
            i++;
        }
    }
    return tokens;
	
    vector<string> tokens = tokenize(formattedInfix);
    vector<string> postfix = infixToPostfix(tokens);
    cout << "Postfix : " << endl;
    for (const auto& token : postfix) {
        cout << token << " ";
    }
    cout << endl << endl;
}

int main() {
	string infix = "-49 - 17%5 * 2";
	
	cout << "Ekpression : " << endl;
	cout << infix <<endl;
	cout <<endl;
	
	string formatedInfix = strToInfix(infix);
	cout << "Infix : " << endl;
	cout << formatedInfix;
	
	return 0;
}
