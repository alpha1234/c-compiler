#pragma once
#include <sstream>


enum class Type {
    KEYWORD,
    IDENTIFIER,
    STRING_LITERAL,
    CHAR_LITERAL,
    NUMBER,
    SPECIAL_SYMBOL,
    REL_OPERATOR,
    ARITH_OPERATOR,
    MEMBER_ACCESS_OPERATOR,
    ASSIGN_OPERATOR,
    LOGICAL_OPERATOR,
    BITWISE_OPERATOR,
    INVALID,
    NEWLINE,
    TEOF
};

struct Token {
    Type type;
    union {
        char *s;
        unsigned int id;
        char c;
        int number;
    } value;

    std::string getString() {
        if ((type == Type::CHAR_LITERAL) || type == Type::SPECIAL_SYMBOL) {
            std::string a;
            a.push_back(value.c);
            return a;
        }
        return std::string(value.s);
    }
    char getChar() {
        return value.c;
    }
    std::string getFormatted() {
        std::ostringstream stream;
        stream << '<';
        switch (type) {
            case Type::CHAR_LITERAL :
                stream << "CHAR_LITERAL," << value.c;
                break;
            case Type::SPECIAL_SYMBOL :
                stream << "SPECIAL_SYMBOL," << value.c;
                break;
            case Type::IDENTIFIER:
                stream << "id," << value.s;
                break;
            case Type::STRING_LITERAL:
                stream << "STRING_LITERAL," << value.s;
                break;
            case Type::KEYWORD:
                stream << "KEYWORD," << value.s;
                break;
            case Type::NUMBER:
                stream << "num," << value.number;
                break;
            case Type::REL_OPERATOR:
                stream << "REL_OPERATOR," << value.s;
                break;
            case Type::ARITH_OPERATOR:
                stream << "ARITH_OPERATOR," << value.s;
                break;
            case Type::MEMBER_ACCESS_OPERATOR:
                stream << "MEMBER_ACCESS," << value.s;
                break;
            case Type::ASSIGN_OPERATOR:
                stream << "ASSIGN_OPERATOR," << value.s;
                break;
            case Type::LOGICAL_OPERATOR:
                stream << "LOGICAL_OPERATOR," << value.s;
                break;
            case Type::BITWISE_OPERATOR:
                stream << "BITWISE_OPERATOR," << value.s;
                break;
            case Type::NEWLINE:
                return "\n";
            case Type::INVALID:
                stream << "INVALID," << value.c;
        }
        stream << '>';
        return stream.str();
    }

    static struct Token *makeToken(Type type) {
        Token *t = new Token;
        t->type = type;
        return t;
    }

    static struct Token *makeToken(Type type, std::string s) {
        Token *t = new Token;
        t->type = type;
        t->value.s = new char[s.size()];   //TODO Possible Memory leak on destruction of Token
        strcpy(t->value.s, const_cast<char *>(s.c_str()));
        return t;
    }

    static struct Token *makeToken(Type type, int value) {
        Token *t = new Token;
        t->type = type;
        if(type == Type::IDENTIFIER) {
            t->value.id = value;
        }
        else if(type == Type::NUMBER) {
            t->value.number = value;
        }
        return t;
    }

    static struct Token *makeToken(Type type, char c) {
        Token *t = new Token;
        t->type = type;
        t->value.c = c;
        return t;
    }
};

