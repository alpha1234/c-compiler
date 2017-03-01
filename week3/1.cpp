#include "../include/compiler.h"
#include "../include/Token.h"
#include "../include/lex.h"

#include "../common.cpp"

using namespace std;

int main() {
	char inputFileName[] = "data/input.txt";
	compiler_initialize(inputFileName);
	Token token;
	while (1) {
		token = getNextToken();
		if (token.type == TEOF) {
			break;
		}
		if(token.type == IDENTIFIER) {
			insertIntoSymbolTable(token);
		}
	}

	compiler_finalize();

	cout << "\nID\tName\n";
	symbolTable.print();

	return 0;

}

