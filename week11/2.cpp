#include "../include/compiler.h"
#include "../include/Token.h"
#include "../include/lex.h"
#include <iostream>
#include <vector>

using namespace std;

void push(vector < Token * > &stack, Token * item) {
	stack.push_back(item);
}


Token *pop(vector < Token * > &stack) {
	Token *item = stack.back();
	stack.erase(stack.end() - 1);

	return item;
}

void printStack(vector < Token * > &stack) {
	cout << "\tStack: ";
	for (const auto &item : stack) {
		cout << item->value.s << " ";
	}
	cout << "\n";
}

int main() {
	vector < Token * > stack;

	char inputFileName[] = "data/input.txt";
	compiler_initialize(inputFileName);

	Token *token, *temp;
	int result,first,second;
	vector<Token *> tokens;

	token = getNextToken();
	while (token->type != TEOF) {
		tokens.push_back(token);
		token = getNextToken();
	}
	reverse(tokens.begin(), tokens.end());

	for (auto token : tokens) {
		switch (token->type) {
		case NUMBER:
			push(stack, token);
			cout << "mov r" << stack.size() - 1 << "," << token->value.s << "\n";
			break;


		case PLUS:
		case MULT:
		case MINUS:
		case DIV:
			second = stoi(pop(stack)->value.s);
			first = stoi(pop(stack)->value.s);
			switch (token->type) {
			case PLUS:
				cout << "add";
				result = second + first;
				break;

			case MULT:
				cout << "mul";
				result = second * first;
				break;

			case DIV:
				cout << "div";
				result = second / first;
				break;

			case MINUS:
				cout << "sub";
				result = second - first;
				break;
			}
			cout << " r" << stack.size()<< ",r" << stack.size() + 1;
			temp = new Token;
			temp->type = NUMBER;
			temp->value.s = to_string(result);
			push(stack, temp);
			printStack(stack);
			break;
		}
	}

	cout << "Result: " << pop(stack)->value.s << "\n";
	compiler_finalize();
	return 0;

}