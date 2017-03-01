#include "../compiler/compiler.h"
#include "../compiler/common.h"
#include "../compiler/HashTable.h"
#include "../compiler/Token.h"
#include "../compiler/SymbolTable.h"

using namespace std;

HashMap<SymbolTableRow *> symbolTable;


void insertIntoSymbolTable(Token& token) {


    SymbolTableRow *row = new SymbolTableRow;
    row->name = s;
    id = symbolTable.search(row);
    if (id != -1) {
       return Token::makeToken(IDENTIFIER, id);
   }
   /*
    skipWhitespaces();
    c = peek(fp,-1);
    if(c == '(') {
        row.type = "FUNC";
        row.returnType = lexemes.back().s;
        row.size = -1;
        int count = 0;
        string parameters;
        getNextChar();
        count++;
        while(1) {
            c = getNextChar();
            count++;
            if(c == ')') {
                break;
            }
            parameters.push_back(c);
        }
        while(count--) {
            getPreviousChar();
        }
        row.arguments = parameters;
        count = 0;
        if(parameters.size() > 0) {
            count++;
        }
        for(int i = 0;i<parameters.size();i++) {
            if(parameters[i] == ',') {
                count++;
            }
        }
        row.noOfArguments = count;
    }
    else {
        row.noOfArguments = -1;
        row.arguments = "";
        row.returnType = "\t";
        row.type = lexemes.back().s;
        if(row.type == "int") row.size = sizeof(int);
        else if(row.type == "char") row.size = sizeof(char);
        else if(row.type == "double") row.size = sizeof(double);
        else if(row.type == "float") row.size = sizeof(float);
        else if(row.type == "string") row.size = sizeof(string);
    }

*/
    id = symbolTable.insert(row);

    return Token::makeToken(IDENTIFIER, s);
}


int main() {
    char inputFileName[] = "input.txt";
    lex_initialize(inputFileName);
    Token *token;
    while (1) {
        token = getNextToken();
        if (token->type == TEOF) {
            break;
        }
        delete token;
    }

    lex_finalize();

    cout << "\nID\tName\n";
    symbolTable.print();

    return 0;

}


