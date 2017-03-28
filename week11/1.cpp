#include "../include/compiler.h"
#include "../include/Token.h"
#include "../include/lex.h"
#include <iostream>
#include <vector>

using namespace std;


int main() {
	vector < Token * > stack;

	char inputFileName[] = "data/input.txt";
	compiler_initialize(inputFileName);

	Token *token, *first, *second, *operation;
	token = getNextToken();
	do {
		
		getNextToken(); //Skip =
		first = getNextToken();
		operation = getNextToken();
		cout << "mov r0," << first->value.s << "\n";

		if (operation->type != SEMICOLON) {
			second = getNextToken();
			cout << "mov r1," << second->value.s << "\n";


			switch (operation->type) {
			case PLUS:
				cout << "add";
				break;

			case MULT:
				cout << "mul";
				break;

			case DIV:
				cout << "div";
				break;

			case MINUS:
				cout << "sub";
				break;
			}
			cout << " r0,r1 \n";
			getNextToken(); //Skip semicolon
		}
		cout << "mov " << token->value.s << ",r0" << "\n";

		token = getNextToken();

	} while (token->type != TEOF);
	compiler_finalize();
	return 0;

}