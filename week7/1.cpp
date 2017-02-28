#include "../compiler/compiler.h"
#include "../compiler/Token.h"
#include "../compiler/lex.h"

using namespace std;

void S();
void DECLARATIONS();
bool DATA_TYPE();
void IDENTIFIER_LIST();
void STATEMENT();

Token *token;



void next() {
    token = getNextToken();
    cout<<token->getFormatted();
}

void error(string message) {
    cout<<message;
    exit(0);
}

bool accept(Type type) {
    if (token->type == type) {
        next();
        return true;
    }
    return false;
}

bool accept(string s) {
    if (token->value.s == s) {
        next();
        return true;
    }
    return false;
}


void expect(Type type) {
    if (!accept(type)) {
        cout<<type;
        error(" Unexpected symbol");
    }
}


bool expect(string c) {
    if (accept(c))
        return true;
    error("Unexpected symbol:" + c);
    return 0;
}


void S() {
    next();
    if(accept("main")) {
        expect(Type::OPEN_PAREN);
        expect(Type::CLOSE_PAREN);
        expect(Type::OPEN_BRACE);
        DECLARATIONS();
        expect(Type::CLOSE_BRACE);
    }
}

void DECLARATIONS() {
    if(token->type == Type::KEYWORD_INT|| token->type == Type::KEYWORD_CHAR) {
        DATA_TYPE();
        IDENTIFIER_LIST();
        expect(Type::SEMICOLON);
        DECLARATIONS();
    }
}


bool DATA_TYPE() {
    if(accept(Type::KEYWORD_INT) || accept(KEYWORD_CHAR)) {}
    else {
        error("int or char");
        next();
    }
}


void IDENTIFIER_LIST() {
    if(accept(Type::IDENTIFIER)) {
        if (accept(Type::COMMA)) {
            IDENTIFIER_LIST();
        } else if (accept(Type::OPEN_SQUARE)) {
            expect(Type::NUMBER);
            expect(Type::CLOSE_BRACE);
            if (accept(Type::COMMA)) {
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
    STATEMENT();
    STATEMENT_LIST();
}


void STATEMENT() {
    ASSIGN_STAT();
    expect(Type::SEMICOLON);
}



int main() {
    char inputFileName[] = "input.txt";
    lex_initialize(inputFileName);

    S();
    expect(Type::TEOF);
    cout<< "Success";
    lex_finalize();
    return 0;
}
