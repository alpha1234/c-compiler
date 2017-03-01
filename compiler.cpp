#include "include/compiler.h"
#include "include/preprocessor.h"
#include "include/lex.h"



void compiler_initialize(char *inputFileName) {
    removeComments(inputFileName,TEMPFILE);
    processIncludes(inputFileName,TEMPFILE);

    lex_initialize(TEMPFILE);
}

void compiler_finalize() {
    lex_finalize();
}