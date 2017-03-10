#include "../include/compiler.h"
#include "../include/Token.h"
#include "../include/lex.h"

using namespace std;

int main() {
    char inputFileName[] = "data/input.txt";
    compiler_initialize(inputFileName);
    Token token;
    while (1) {
        token = getNextToken();
        if (token.type == TEOF) {
            break;
        }
        if (token.type < 32) {
            cout << TYPE_MAPPING[token.type];
        }
    }

    compiler_finalize();


    return 0;

}

