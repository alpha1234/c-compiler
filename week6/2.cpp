#include "../compiler/compiler.h"
#include "../compiler/Token.h"
#include "../compiler/lex.h"

using namespace std;

bool E();
bool E1();
bool T();
bool T1();
bool F();

Token *token;
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
    if(token->getString() == "+") {
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
    if(token->getString() == "*") {
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
    if (token->getString() == "(") {
        if (E()) {
            token = getNextToken();
            if (token->getString() == ")") {
                return true;
            }
        }
    } else {
        return token->type == Type::IDENTIFIER;
    }

    return false;

}


int main() {

 char inputFileName[] = "input.txt";
    char outputFileName[] = "output.txt";
    lex_initialize(inputFileName,outputFileName);
        if(E()) {
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