#include "compiler/compiler.h"
#include "compiler/Token.h"
#include "compiler/lex.h"
#include <map>

using namespace std;

int main() {


    char inputFileName[] = "week7/input.txt";
    lex_initialize(inputFileName);

    Token t = Token::makeToken(PLUS);
    lex_finalize();
    return 0;
}
