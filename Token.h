#pragma once

struct Token {
    Type type;
    union {
        char *s;
        unsigned int id;
        char c;
        int number;
    } value;

    std::string print() {
        std::string output = "<";
        switch (type) {
            case Type::CHAR_LITERAL :
                output = output + "CHAR_LITERAL," + value.c;
                break;
            case Type::SPECIAL_SYMBOL :
                output = output + "SPECIAL_SYMBOL," + value.c;
                break;
            case Type::IDENTIFIER:
                output = output + "id," + std::to_string(value.id);
                break;
            case Type::STRING_LITERAL:
                output = output + "STRING_LITERAL," + value.s;
                break;
            case Type::KEYWORD:
                output = output + "KEYWORD," + value.s;
                break;
            case Type::NUMBER:
                output = output + "num," + value.s;
                break;
            case Type::REL_OPERATOR:
                output = output + "REL_OPERATOR," + value.s;
                break;
            case Type::ARITH_OPERATOR:
                output = output + "ARITH_OPERATOR," + value.s;
                break;
            case Type::NEWLINE:
                return "\n";
            case Type::INVALID:
                output = output + "INVALID," + value.c;
        }
        output += '>';
        return output;

    }

    static struct Token *makeToken(Type type) {
        Token *t = new Token;
        t->type = type;
        return t;
    }

    static struct Token *makeToken(Type type, std::string s1) {
        Token *t = new Token;
        t->type = type;
        t->value.s = new char[s1.size()];   //TODO Possible Memory leak on destruction of Token
        strcpy(t->value.s, const_cast<char *>(s1.c_str()));
        return t;
    }

    static struct Token *makeToken(Type type, int id1) {
        Token *t = new Token;
        t->type = type;
        t->value.id = id1;
        return t;
    }

    static struct Token *makeToken(Type type, char c1) {
        Token *t = new Token;
        t->type = type;
        t->value.c = c1;
        return t;
    }
};

