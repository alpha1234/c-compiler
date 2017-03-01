#include "../include/compiler.h"
#include "../include/Token.h"
#include "../include/lex.h"

using namespace std;

bool E();
bool E1();
bool T();
bool T1();
bool F();

Token token;
bool E() {
    cout << "Inside E \n";

    if(T()) {
        return E1();
    }
    undoTokenGet();
    return false;
}

bool E1() {
    cout << "Inside E1 \n";

    token = getNextToken();
    if(token.type == PLUS) {
        if(T()) {
            return E1();
        }
    }
    undoTokenGet();
    return true;
}
bool T() {
    cout << "Inside T \n";

    if(F()) {
        return T1();
    }
    return false;
}
bool T1() {
    cout << "Inside T1 \n";

    token = getNextToken();
    if(token.type == MULT) {
        if(F()) {
            return T1();
        }
    }
    undoTokenGet();
    return true;
}

bool F() {
    cout << "Inside F \n";

    token = getNextToken();
    if (token.type == OPEN_PAREN) {
        if (E()) {
            token = getNextToken();
            if (token.type == CLOSE_PAREN) {
                return true;
            }
        }
    } else {
        return token.type == IDENTIFIER;
    }

    return false;

}


int main() {

 char inputFileName[] = "input.txt";
    lex_initialize(inputFileName);
        if(E()) {
        token = getNextToken();
        if(token.type == TEOF) {
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