#include "../compiler.h"
#include "../Token.h"
#include "../lex.h"

using namespace std;

bool S();
bool T();
bool T1();

Token *token;
bool S() {
    token = getNextToken();
    if(token->getString() == "a") {
        return true;
    }
    else if(token->getString() == "->") {
        return true;
    }
    else if(token->getChar() == '(') {
        if(T()) {
            token = getNextToken();
            if (token->getChar() == ')') {
                return true;
            }
        }
    }
    return false;

}

bool T() {
    if(S()) {
        return T1();
    }
    return false;
}

bool T1() {
    token = getNextToken();
    if(token->getChar() == ',') {
        if(S()) {
            return T1();
        }
    }
    else {
        undoTokenGet();
        return true;
    }
    return false;
}


int main() {

    lex_initialize();
    if(S()) {
        token = getNextToken();
        if(token->type == Type::TEOF) {
            cout << "Success";
        }
        else {
            cout<<"Error";
        }
    }
    else {
        cout<<"Error";
    }

    lex_finalize();
    return 0;
}
