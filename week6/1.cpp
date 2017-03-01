#include "../compiler/compiler.h"
#include "../compiler/Token.h"
#include "../compiler/lex.h"

using namespace std;

bool S();
bool T();
bool T1();

Token *token;
bool S() {
    cout << "Inside S \n";
    token = getNextToken();
    if(token->value.s == "a") {
        return true;
    }
    else if(token->type == DEREF) {
        return true;
    }
    else if(token->type == OPEN_PAREN) {
        if(T()) {
            token = getNextToken();
            if (token->type == CLOSE_PAREN) {
                return true;
            }
        }
    }
    return false;

}

bool T() {
    cout << "Inside T \n";

    if(S()) {
        return T1();
    }
    return false;
}

bool T1() {
    cout << "Inside T1 \n";

    token = getNextToken();
    if(token->type == COMMA) {
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
  char inputFileName[] = "input.txt";
    lex_initialize(inputFileName);
    if(S()) {
        token = getNextToken();
        if(token->type == TEOF) {
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
