#include "include/compiler.h"
#include "include/parser.h"


int main() {

    char inputFileName[] = "data/input.txt";
    compiler_initialize(inputFileName);

    parser_initialize();


    compiler_finalize();
    return 0;
}
