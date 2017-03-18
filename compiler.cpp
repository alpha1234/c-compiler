#include "include/compiler.h"
#include "include/preprocessor.h"
#include "include/lex.h"
#include <iostream>

using namespace std;


void compiler_initialize(char *inputFileName) {
    processIncludes(inputFileName, TEMPFILE);

    lex_initialize(TEMPFILE);

}

void compiler_finalize() {
    lex_finalize();

}

