#include "../compiler/compiler.h"
#include "../compiler/Token.h"
#include "../compiler/lex.h"

using namespace std;

bool lexp();
bool aterm();
bool list();
bool lexp_seq();
bool lexp_seq1();

Token *token;
bool lexp() {
    cout << "Inside lexp \n";

    if(aterm()) {
        return true;
    }

    return list();
}

bool aterm() {
    cout << "Inside aterm \n";

    token = getNextToken();
    if(token->type == Type::NUMBER) {
        return true;
    }
    else if(token->type == Type::IDENTIFIER) {
        return true;
    }
    return false;
}
bool list() {
    cout << "Inside list \n";
    token = getNextToken();
    if(token->getString() == "(") {
        if(lexp_seq()) {
            token = getNextToken();
            if(token->getString() == ")") {
                return true;
            }
        }
    }
    return false;
}
bool lexp_seq() {
    cout << "Inside lexp_seq \n";

    if(lexp()) {
        return lexp_seq1();
    }
    return false;
}

bool lexp_seq1() {
    if(lexp()) {
        return lexp_seq1();
    }

    return true;
}



int main() {

 char inputFileName[] = "input.txt";
    char outputFileName[] = "output.txt";
    lex_initialize(inputFileName,outputFileName);
        if(lexp()) {
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