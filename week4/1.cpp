#include "../include/compiler.h"
#include "../include/HashTable.h"
#include "../include/Token.h"
#include "../include/SymbolTable.h"
#include "../include/lex.h"

using namespace std;

HashMap<string, SymbolTableRow> symbolTable;
int lastInsertId = -1;

void insertIntoSymbolTable(Token &token) {

    SymbolTableRow row;

    bool result = symbolTable.get(token.value.s, row);
    if (result) {
        token.value.id = row.id;
    } else {
        lastInsertId++;
        row.id = lastInsertId;
        row.name = token.value.s;
        symbolTable.insert(row.name, row);
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
}


int main() {
    char inputFileName[] = "data/input.txt";
    compiler_initialize(inputFileName);
    Token token;
    while (1) {
        token = getNextToken();
        if (token.type == TEOF) {
            break;
        }
        if (token.type == IDENTIFIER) {
            insertIntoSymbolTable(token);
        }
    }

    compiler_finalize();

    cout << "\nID\tName\n";
    symbolTable.print();

    return 0;

}


