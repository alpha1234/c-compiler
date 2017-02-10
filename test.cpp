#include "compiler.h"


int main() {
    HashMap<SymbolTableRow *> hmap;
    SymbolTableRow *row = new SymbolTableRow;
    row->name = "Gdgh";
    cout<<row;

    return 0;
}