#pragma once
#include <sstream>



enum {
    KEYWORD_AUTO, KEYWORD_BREAK, KEYWORD_CASE, KEYWORD_CHAR, KEYWORD_CONST,
    KEYWORD_CONTINUE, KEYWORD_DEFAULT, KEYWORD_DO, KEYWORD_DOUBLE, KEYWORD_ELSE,
    KEYWORD_ENUM, KEYWORD_EXTERN, KEYWORD_FLOAT, KEYWORD_FOR, KEYWORD_GOTO,
    KEYWORD_IF, KEYWORD_INT, KEYWORD_LONG, KEYWORD_REGISTER, KEYWORD_RETURN,
    KEYWORD_SHORT, KEYWORD_SIGNED, KEYWORD_SIZEOF, KEYWORD_STATIC, KEYWORD_STRUCT,
    KEYWORD_SWITCH, KEYWORD_TYPEDEF, KEYWORD_UNION, KEYWORD_UNSIGNED, KEYWORD_VOID,
    KEYWORD_VOLATILE, KEYWORD_WHILE,
    IDENTIFIER,
    INVALID,
    TEOF,
    EQ, NOT, GREATER, LESS, PLUS, MINUS, MULT, DIV,
    MOD, AND, OR, XOR, RSHIFT, LSHIFT, COMPL, AND_AND, OR_OR, QUERY, COLON,
    COMMA, OPEN_PAREN, CLOSE_PAREN, EQ_EQ, NOT_EQ,
    GREATER_EQ, LESS_EQ, PLUS_EQ, MINUS_EQ, MULT_EQ,
    DIV_EQ, MOD_EQ, AND_EQ, OR_EQ, XOR_EQ, RSHIFT_EQ,
    LSHIFT_EQ, OPEN_SQUARE, CLOSE_SQUARE, OPEN_BRACE, CLOSE_BRACE,
    SEMICOLON, PLUS_PLUS, MINUS_MINUS, DEREF,
    DOT, DEREF_STAR, DOT_STAR,
    NUMBER, CHAR, OTHER, STRING
};


class Token {
public:

    Type type;
    struct {
        std::string s;
        int id;
        char c;
        int number;
    } value;


    std::string getFormatted() {
        std::ostringstream stream;
        stream << '<';
        switch (type) {
            case Type::CHAR :
                stream << "CHAR," << value.c;
                break;
            case Type::NUMBER:
                stream << "num," << value.number;
                break;
            case Type::IDENTIFIER:
                stream << "id," << value.s;
                break;
            case Type::STRING:
                stream << "STRING," << value.s;
                break;
            case Type::INVALID:
                stream << "INVALID," << value.c;
        }
        if(type < 32) {
            stream << "KEYWORD," << value.s;
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
        t->value.s = s;
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

