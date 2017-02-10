#pragma once


#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <array>
#include <typeinfo>
#include <string.h>
#include <unistd.h>
#include <fstream>


const std::vector <std::string> RESERVED_KEYWORDS = {
        "auto", "break", "case", "char", "const",
        "continue", "default", "do", "double", "else",
        "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return",
        "short", "signed", "sizeof", "static", "struct",
        "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while"
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
    MEMBER_ACCESS,
    ASSIGN_OPERATOR,
    LOGICAL_OPERATOR,
    BITWISE_OPERATOR,
    INVALID,
    NEWLINE,
    TEOF
};



