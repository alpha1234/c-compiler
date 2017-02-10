#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <typeinfo>
#include <string.h>
#include <unistd.h>

#include "HashTable.h"


using namespace std;

const vector<string> RESERVED_KEYWORDS = {
        "auto", "break", "case", "char", "const",
        "continue", "default", "do", "double", "else",
        "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return",
        "short", "signed", "sizeof", "static", "struct",
        "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while"
};


const vector <string> LOGICAL_OPERATORS = {
        "&&", "||", "!"
};

const vector <string> ASSIGNMENT_OPERATORS = {
        "=", "+=", "-=", "*=", "/=",
        "%=", "<<=", ">>=", "&=", "^=",
        "|="
};




enum class Type {
    KEYWORD,
    IDENTIFIER,
    STRING_LITERAL,
    CHAR_LITERAL,
    NUMBER,
    SPECIAL_SYMBOL,
    REL_OPERATOR,
    ARITH_OPERATOR,
    INVALID,
    NEWLINE,
    TEOF
};

struct token {
    Type type;
   // int line;
   // int column;
    token() {}
    union {
        char * s;
        unsigned int id;
        char c;
        int number;
    };
    token(Type t) {
        type = t;
    }
    token(Type t,string s1) {
        type = t;
        s = (char *)malloc(sizeof(char) * sizeof(s1));
        strcpy(s,const_cast<char*>(s1.c_str()));
    }
    token(Type t,int id1) {
        type = t;
        id = id1;
    }
    token(Type t,char c1) {
        type = t;
        c = c1;
    }
    void print() {
        switch (type) {
            case Type::CHAR_LITERAL :
                cout << "<CHAR_LITERAL," << c << ">";
                break;
            case Type::SPECIAL_SYMBOL :
                cout << "<SPECIAL_SYMBOL," << c << ">";
                break;
            case Type::IDENTIFIER:
                cout << "<id," << id << ">";
                break;
            case Type::STRING_LITERAL:
                cout << "<STRING_LITERAL," << s << ">";
                break;
            case Type::KEYWORD:
                cout << "<KEYWORD," << s << ">";
                break;
            case Type::NUMBER:
                cout << "<num," << s << ">";
                break;
            case Type::REL_OPERATOR:
                cout << "<REL_OPERATOR,'" << s << "'>";
                break;
            case Type::ARITH_OPERATOR:
                cout << "<ARITH_OPERATOR,'" << s << "'>";
                break;
            case Type::NEWLINE:
                cout << "\n";
        }
    }

};

typedef struct token Token;


/* Header Files for common.cpp */

FILE *openFile(string fileName, const char mode[]);
void copyFile(char source[], char destination[]);
void initialize(char *filename);
void finalize();
char next();
char prev();
void undo(char c);
void shift(int c);
void skipWhitespaces();
void ab();

inline bool isWhitespace(int c) {
    return c == ' ' || c == '\t' || c == '\f' || c == '\v';
}

inline bool isAlphabet(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

inline bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

/* -----------------------------------  */

/* Header Files for preprocessor.cpp */

void preprocess(char fileName[]);

/* -----------------------------------  */


/* Header Files for lex.cpp */
Token * getNextToken();
/* -----------------------------------  */


/* Header Files for symbol_table.cpp */


struct symbolTableRow {
    string name;
    string type;
    int size;
    char scope;
    int noOfArguments;
    string arguments;
    string returnType;

};

typedef struct symbolTableRow SymbolTableRow;

//extern HashMap<SymbolTableRow *> symbolTable;

/* -----------------------------------  */


inline ostream& operator<<(ostream& o, const SymbolTableRow* a) {
    return o << a->name <<"\n";
}