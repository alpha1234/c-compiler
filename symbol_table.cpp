#include "compiler.h"

using namespace std;


vector<struct symbolTableRow> symbolTable;

int indexOfIdentifier(string s,char scope) {
    for (int i = 0; i < symbolTable.size(); i++) {
        if (symbolTable[i].name == s && symbolTable[i].scope == scope) {
            return i;
        }
    }
    return -1;
}

