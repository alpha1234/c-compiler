#include "compiler.h"
#include "common.h"
//#include "HashTable.h"
//#include "Token.h"
//#include "SymbolTable.h"

using namespace std;

int main() {
    string s;
    char c = 'f';
    s = s + "<CHAR_LITERAL," + c + ">";
    cout << s;
    return 0;
}