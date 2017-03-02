#include "include/compiler.h"
#include "include/preprocessor.h"
#include "include/lex.h"

using namespace std;

void compiler_initialize(char *inputFileName) {
    string tempFile = tmpnam(nullptr);
    removeComments(inputFileName,tempFile.c_str());

    processIncludes(tempFile.c_str(),TEMPFILE);

    lex_initialize(TEMPFILE);
}

void compiler_finalize() {
    lex_finalize();
}