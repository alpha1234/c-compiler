#include "../include/compiler.h"
#include "../include/token.h"
#include "../include/lex.h"

using namespace std;

bool lexp();

bool aterm();

bool list();

bool lexp_seq();

bool lexp_seq1();

Token *token;

bool lexp() {
    cout << "Inside lexp \n";

    if (aterm()) {
        return true;
    }

    return list();
}

bool aterm() {
    cout << "Inside aterm \n";

    token = getNextToken();
    if (token->type == NUMBER) {
        return true;
    } else if (token->type == IDENTIFIER) {
        return true;
    }
    return false;
}

bool list() {
    cout << "Inside list \n";
    token = getNextToken();
    if (token->type == OPEN_PAREN) {
        if (lexp_seq()) {
            token = getNextToken();
            if (token->type == CLOSE_PAREN) {
                return true;
            }
        }
    }
    return false;
}

bool lexp_seq() {
    cout << "Inside lexp_seq \n";

    if (lexp()) {
        return lexp_seq1();
    }
    return false;
}

bool lexp_seq1() {
    if (lexp()) {
        return lexp_seq1();
    }

    return true;
}


int main() {

    char inputFileName[] = "data/input.txt";
    compiler_initialize(inputFileName);
    if (lexp()) {
        token = getNextToken();
        if (token->type == TEOF) {
            cout << "Success";
        } else {
            cout << "Error";
        }
    } else {
        cout << "Error";
    }

    compiler_finalize();
    return 0;
}