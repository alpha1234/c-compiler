#include "../include/compiler.h"
#include "../include/Token.h"
#include "../include/lex.h"
#include <map>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

Token *token;

void next() {
	token = getNextToken();
}


void push(vector<Token*> &stack,Token * item) {
	stack.push_back(item);
}


Token* pop(vector<Token*> &stack) {
	Token* item = stack.back();
	stack.erase(stack.end() - 1);

	return item;
}

void printStack(vector<Token*> &stack) {
	cout<<"\tStack: ";
	for(const auto &item : stack) {
		cout<<item->value.s<<" ";
	}
}

string intToString(int num) {
	string s;
	while(num) {
		s.push_back(num % 10 + '0');
		num /= 10;
	}

	return s;
}

int main() {
	vector<Token*> stack;

	char inputFileName[] = "data/input.txt";
	compiler_initialize(inputFileName);

	Token *token,*first,*second,*temp;
	string result;

	token = getNextToken();
	while(token->type != TEOF) {
		switch(token->type) {
			case NUMBER:
				push(stack,token);
				cout<<"mov r"<<stack.size() - 1<<","<<token->value.s;
				break;


			case PLUS :
			case MULT :
			case MINUS :
			case DIV :
				second =  pop(stack);
				first = pop(stack);
				switch(token->type) {
			case PLUS:
				cout<<"add r"<<stack.size()<<",r"<<stack.size() + 1;
				result = intToString(atoi(first->value.s.c_str()) + atoi(second->value.s.c_str()));
				break;
				
			case MULT:
				cout<<"mul r"<<stack.size()<<",r"<<stack.size() + 1;
				result = intToString(atoi(first->value.s.c_str()) * atoi(second->value.s.c_str()));
				break;

			case DIV:
				cout<<"div r"<<stack.size()<<",r"<<stack.size() + 1;
				result = intToString(atoi(first->value.s.c_str()) / atoi(second->value.s.c_str()));
				break;

			case MINUS:
				cout<<"sub r"<<stack.size()<<",r"<<stack.size() + 1;
				result = intToString(atoi(first->value.s.c_str()) - atoi(second->value.s.c_str()));
				break;
			}
				temp = new Token;
				temp->type = NUMBER;
				temp->value.s = result;
				push(stack,temp);
				printStack(stack);
				break;
		}
		cout<<"\n";
		token = getNextToken();
	}

	cout<<"Result: "<<pop(stack)->value.s<<"\n";
	compiler_finalize();
	return 0;

}