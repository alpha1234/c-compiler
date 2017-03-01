#include "../include/compiler.h"
#include "../include/Token.h"
#include "../include/lex.h"
#include <map>

using namespace std;

void S();
void DECLARATIONS();
void DATA_TYPE();
void IDENTIFIER_LIST();
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

Token token;

map<string,vector<int>> FIRST;


bool inArray(int val,vector<int> list) {
    for (const auto& i : list) {
        if (val == i) {
            return true;
        }
    }
    return false;
}

void next() {
    token = getNextToken();
}

void error(string message) {
    cout<<"\nERROR on line "<<token.line<<" column "<<token.column<<"\n";
    cout<<"Expected: "<<message<<" Found: "<<token.getFormatted()<<"\n";
    lex_finalize();
    exit(0);
}

bool accept(int type) {
    if (token.type == type) {
        next();
        return true;
    }
    return false;
}

bool accept(string s) {
    if (token.value.s == s) {
        next();
        return true;
    }
    return false;
}


void expect(int type) {
    if (!accept(type)) {
        error(to_string(type));
    }
}


void S() {
    cout<<"S\n";

    if(accept("main")) {
        expect(OPEN_PAREN);
        expect(CLOSE_PAREN);
        expect(OPEN_BRACE);
        DECLARATIONS();
        STATEMENT_LIST();
        expect(CLOSE_BRACE);
    }
}

void DECLARATIONS() {
    cout<<"DECLARATIONS\n";
    if(inArray(token.type,FIRST["DECLARATIONS"])) {
        DATA_TYPE();
        IDENTIFIER_LIST();
        expect(SEMICOLON);
        DECLARATIONS();
    }
}



void DATA_TYPE() {
    cout<<"DATA_TYPE\n";

    if(accept(KEYWORD_INT) || accept(KEYWORD_CHAR)) {}
    else {
        error("int or char");
        next();
    }
}


void IDENTIFIER_LIST() {
    cout<<"IDENTIFIER_LIST\n";

    if(accept(IDENTIFIER)) {
        if (accept(COMMA)) {
            IDENTIFIER_LIST();
        } else if (accept(OPEN_SQUARE)) {
            expect(NUMBER);
            expect(CLOSE_BRACE);
            if (accept(COMMA)) {
                IDENTIFIER_LIST();
            }
        }
        else if(accept(EQ)) {
            EXPN();
            if(accept(COMMA)) {
                IDENTIFIER_LIST();
            }
        }
    }
    else {
        error("IDENTIFIER");
        next();
    }
}


void STATEMENT_LIST() {
    cout<<"STATEMENT_LIST\n";

    if(inArray(token.type,FIRST["STATEMENT_LIST"])) {
        STATEMENT();
        STATEMENT_LIST();
    }
}


void STATEMENT() {
    cout<<"STATEMENT\n";

    if(token.type == IDENTIFIER) {
        ASSIGN_STAT();
        expect(SEMICOLON);
    }
    else if(token.type == KEYWORD_IF) {
        DECISION_STAT();
    }
    else if(inArray(token.type,FIRST["STATEMENT"])) {
        LOOPING_STAT();
    }
    else {
        error("id, if, while, for");
    }
}

void ASSIGN_STAT() {
    cout<<"ASSIGN_STAT\n";

    expect(IDENTIFIER);
    expect(EQ);
    EXPN();
}

void EXPN() {
    cout<<"EXPN\n";

    SIMPLE_EXPN();
    EPRIME();
}
void EPRIME() {
    cout<<"EPRIME\n";
        if(inArray(token.type,FIRST["EPRIME"])) {
            RELOP();
        SIMPLE_EXPN();
    }
}

void SIMPLE_EXPN() {
    cout<<"SIMPLE_EXPN\n";

    TERM();
    SEPRIME();
}
void SEPRIME() {
    cout<<"SEPRIME\n";

    if(inArray(token.type,FIRST["SEPRIME"])) {
        ADDOP();
        TERM();
        SEPRIME();
    }
}

void TERM() {
    cout<<"TERM\n";

    FACTOR();
    TPRIME();
}

void TPRIME() {
    cout<<"TPRIME\n";
    if(inArray(token.type,FIRST["TPRIME"])) {
        MULOP();
        FACTOR();
        TPRIME();
    }
}

void FACTOR() {
    cout<<"FACTOR\n";
    if(accept(IDENTIFIER) || accept(NUMBER)) {
    }
    else {
        error("IDENTIFIER OR NUMBER");
    }
}
void DECISION_STAT() {
    cout<<"DECISION_STAT\n";

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
    cout<<"DPRIME\n";

    if(accept(KEYWORD_ELSE)) {
        expect(OPEN_BRACE);
        STATEMENT_LIST();
        expect(CLOSE_BRACE);
    }
}

void LOOPING_STAT() {
    cout<<"LOOPING_STAT\n";
    if(accept(KEYWORD_WHILE)) {
        expect(OPEN_PAREN);
        EXPN();
        expect(CLOSE_PAREN);
        expect(OPEN_BRACE);
        STATEMENT_LIST();
        expect(CLOSE_BRACE);
    }
    else if(accept(KEYWORD_FOR)) {
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
    }
    else {
        error("while,for");
    }


}

void RELOP() {
    cout<<"RELOP\n";
    if(accept(EQ_EQ) || accept(NOT_EQ) || accept(LESS_EQ) ||
            accept(GREATER_EQ) || accept(GREATER) || accept(LESS)) {

    }
    else {
        error("==,!=,<=,>=,>,<");
    }

}

void ADDOP() {
    cout << "ADDOP\n";

    if (accept(PLUS) || accept(MINUS)) {
    } else {
        error("+,-");
    }

}

void MULOP() {
    cout << "MULOP\n";

    if (accept(MULT) || accept(DIV) || accept(MOD)) {
    } else {
        error("*,/,%");
    }

}




int main() {

    FIRST = {
            {"DECLARATIONS", {KEYWORD_INT,KEYWORD_CHAR} },
            {"TPRIME", {MULT,DIV,MOD}},
            {"STATEMENT_LIST",{IDENTIFIER,KEYWORD_IF,KEYWORD_WHILE,KEYWORD_FOR}},
            {"STATEMENT",{KEYWORD_WHILE,KEYWORD_FOR}},
            {"EPRIME",{EQ_EQ,NOT_EQ,LESS_EQ,GREATER_EQ,GREATER,LESS}},
            {"SEPRIME",{PLUS,MINUS}},
            {"TPRIME",{MULT,DIV,MOD}}
    };

    char inputFileName[] = "input.txt";
    lex_initialize(inputFileName);

    next();
    S();
    expect(TEOF);
    cout<< "Success";
    lex_finalize();
    return 0;
}
