#pragma once

#include <string>

typedef struct {
    std::string name;
    std::string type;
    int size;
    char scope;
    int noOfArguments;
    std::string arguments;
    std::string returnType;
    int id;
} SymbolTableRow;


std::ostream &operator<<(std::ostream &o, const SymbolTableRow &a) {
    return o << a.name;
}


bool operator==(const SymbolTableRow &a, const SymbolTableRow &b) {
    return (a.name == b.name);
}
