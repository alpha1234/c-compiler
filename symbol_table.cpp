#include "compiler.h"

using namespace std;


vector<symbolTableRow *> symbolTable;

int indexOfIdentifier(string s) {
    for (int i = 0; i < symbolTable.size(); i++) {
        if (symbolTable[i]->name == s) {
            return i;
        }
    }
    return -1;
}

