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
