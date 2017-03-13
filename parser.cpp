#include "include/compiler.h"
#include "include/Token.h"
#include "include/lex.h"
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

void S();

void DECLARATIONS();

void DATA_TYPE();

void NAME_LIST();

void STATEMENT_LIST();

void STATEMENT();

void ASSIGN_STAT();

void EXPN();

void EPRIME();

void SIMPLE_EXPN();

void SEPRIME();

void TERM();

void TPRIME();

void FACTOR();

void DECISION_STAT();

void DPRIME();

void LOOPING_STAT();

void RELOP();

void ADDOP();

void MULOP();

Token *token;

map <string, vector<int>> FIRST;

bool errorFound = false;

bool inFirst(Token *token, string name) {
    return find(FIRST[name].begin(), FIRST[name].end(), token->type) != FIRST[name].end();

}

void next() {
    delete token;
    token = getNextToken();
}

void parse_error(string message) {
    cout << "\nParse Error on line " << token->line << " column " << token->column << "\n";
    cout << "Expected: " << message << " Found: " << token->getFormatted() << "\n";
    errorFound = true;
}

bool accept(int type) {
    if (token->type == type) {
        next();
        return true;
    }
    return false;
}


void expect(int type) {
    if (!accept(type)) {
        parse_error(TYPE_MAPPING[type]);
    }
}


void S() {
    // cout<<"S\n";

    if (accept(NAME)) {
        expect(OPEN_PAREN);
        expect(CLOSE_PAREN);
        expect(OPEN_BRACE);
        DECLARATIONS();
        STATEMENT_LIST();
        expect(CLOSE_BRACE);
    }
}

void DECLARATIONS() {
    // cout<<"DECLARATIONS\n";
    if (inFirst(token, "DECLARATIONS")) {
        DATA_TYPE();
        NAME_LIST();
        expect(SEMICOLON);
        DECLARATIONS();
    }
}


void DATA_TYPE() {
    // cout<<"DATA_TYPE\n";

    if (!(accept(KEYWORD_INT) || accept(KEYWORD_CHAR))) {
        parse_error("int or char");
    }
}


void NAME_LIST() {
    //cout<<"NAME_LIST\n";

    if (accept(NAME)) {
        if (accept(COMMA)) {
            NAME_LIST();
        } else if (accept(OPEN_SQUARE)) {
            expect(NUMBER);
            expect(CLOSE_BRACE);
            if (accept(COMMA)) {
                NAME_LIST();
            }
        } else if (accept(EQ)) {
            EXPN();
            if (accept(COMMA)) {
                NAME_LIST();
            }
        }
    } else {
        parse_error("NAME");
    }
}


void STATEMENT_LIST() {
    // cout<<"STATEMENT_LIST\n";

    if (inFirst(token, "STATEMENT_LIST")) {
        STATEMENT();
        STATEMENT_LIST();
    }
}


void STATEMENT() {
    //cout<<"STATEMENT\n";

    if (token->type == NAME) {
        ASSIGN_STAT();
        expect(SEMICOLON);
    } else if (token->type == KEYWORD_IF) {
        DECISION_STAT();
    } else if (inFirst(token, "STATEMENT")) {
        LOOPING_STAT();
    } else {
        parse_error("id, if, while, for");
    }
}

void ASSIGN_STAT() {
    //cout<<"ASSIGN_STAT\n";

    expect(NAME);

    if (!(
            accept(EQ) || accept(PLUS_EQ) || accept(MINUS_EQ) || accept(MULT_EQ) || accept(DIV_EQ) ||
            accept(MOD_EQ) || accept(AND_EQ) || accept(OR_EQ) || accept(XOR_EQ) ||
            accept(RSHIFT_EQ) || accept(LSHIFT_EQ) || accept(EQ_EQ) || accept(NOT_EQ) || accept(LESS_EQ) ||
            accept(GREATER_EQ)  || accept(LESS) || accept(EQ_EQ) || accept(NOT_EQ)
    )) {
        parse_error("Expected Assignment Operator");
    }
    EXPN();
}

void EXPN() {
    // cout<<"EXPN\n";

    SIMPLE_EXPN();
    EPRIME();
}

void EPRIME() {
    // cout<<"EPRIME\n";
    if (inFirst(token, "EPRIME")) {
        RELOP();
        SIMPLE_EXPN();
    }
}

void SIMPLE_EXPN() {
    // cout<<"SIMPLE_EXPN\n";

    TERM();
    SEPRIME();
}

void SEPRIME() {
    // cout<<"SEPRIME\n";

    if (inFirst(token, "SEPRIME")) {
        ADDOP();
        TERM();
        SEPRIME();
    }
}

void TERM() {
    // cout<<"TERM\n";

    FACTOR();
    TPRIME();
}

void TPRIME() {
    //  cout<<"TPRIME\n";
    if (inFirst(token, "TPRIME")) {
        MULOP();
        FACTOR();
        TPRIME();
    }
}

void FACTOR() {
    // cout<<"FACTOR\n";
    if (!(accept(NAME) || accept(NUMBER) || accept(STRING)) || accept(CHAR)) {
        parse_error("NAME OR NUMBER OR STRING OR CHAR");
    }
}

void DECISION_STAT() {
    // cout<<"DECISION_STAT\n";

    expect(KEYWORD_IF);
    expect(OPEN_PAREN);
    EXPN();
    expect(CLOSE_PAREN);
    expect(OPEN_BRACE);
    STATEMENT_LIST();
    expect(CLOSE_BRACE);
    DPRIME();
}

void DPRIME() {
    // cout<<"DPRIME\n";

    if (accept(KEYWORD_ELSE)) {
        expect(OPEN_BRACE);
        STATEMENT_LIST();
        expect(CLOSE_BRACE);
    }
}

void LOOPING_STAT() {
    // cout<<"LOOPING_STAT\n";
    if (accept(KEYWORD_WHILE)) {
        expect(OPEN_PAREN);
        EXPN();
        expect(CLOSE_PAREN);
        expect(OPEN_BRACE);
        STATEMENT_LIST();
        expect(CLOSE_BRACE);
    } else if (accept(KEYWORD_FOR)) {
        expect(OPEN_PAREN);
        ASSIGN_STAT();
        expect(SEMICOLON);
        EXPN();
        expect(SEMICOLON);
        ASSIGN_STAT();
        expect(CLOSE_PAREN);
        expect(OPEN_BRACE);
        STATEMENT_LIST();
        expect(CLOSE_BRACE);
    } else {
        parse_error("while,for");
    }


}

void RELOP() {
    //cout<<"RELOP\n";
    if (!(accept(EQ_EQ) || accept(NOT_EQ) || accept(LESS_EQ) ||
          accept(GREATER_EQ) || accept(GREATER) || accept(LESS) ||
          accept(EQ_EQ) || accept(NOT_EQ))) {
        parse_error("==,!=,<=,>=,>,<,==,!=");
    }

}

void ADDOP() {
    //cout << "ADDOP\n";

    if (!(accept(PLUS) || accept(MINUS))) {
        parse_error("+,-");
    }

}

void MULOP() {
    // cout << "MULOP\n";

    if (!(accept(MULT) || accept(DIV) || accept(MOD))) {
        parse_error("*,/,%");
    }

}


int main() {

    FIRST = {
            {"DECLARATIONS",   {KEYWORD_INT,   KEYWORD_CHAR}},
            {"TPRIME",         {MULT,          DIV,        MOD}},
            {"STATEMENT_LIST", {NAME,    KEYWORD_IF, KEYWORD_WHILE, KEYWORD_FOR}},
            {"STATEMENT",      {KEYWORD_WHILE, KEYWORD_FOR}},
            {"EPRIME",         {EQ_EQ,         NOT_EQ,     LESS_EQ,       GREATER_EQ, GREATER, LESS}},
            {"SEPRIME",        {PLUS,          MINUS}},
            {"TPRIME",         {MULT,          DIV,        MOD}}
    };

    char inputFileName[] = "data/input.txt";
    compiler_initialize(inputFileName);

    next();
    S();
    expect(TEOF);
    if (!errorFound)
        cout << "\nGrammar Correct\n";
    else
        cout << "\nGrammar Incorrect\n";

    compiler_finalize();
    return 0;
}
