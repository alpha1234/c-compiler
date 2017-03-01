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
    EQ, NOT, GREATER, LESS, PLUS, MINUS, MULT, DIV,
    MOD, AND, OR, XOR, RSHIFT, LSHIFT, COMPL, AND_AND, OR_OR, QUERY, COLON,
    COMMA, OPEN_PAREN, CLOSE_PAREN, EQ_EQ, NOT_EQ,
    GREATER_EQ, LESS_EQ, PLUS_EQ, MINUS_EQ, MULT_EQ,
    DIV_EQ, MOD_EQ, AND_EQ, OR_EQ, XOR_EQ, RSHIFT_EQ,
    LSHIFT_EQ, OPEN_SQUARE, CLOSE_SQUARE, OPEN_BRACE, CLOSE_BRACE,
    SEMICOLON, PLUS_PLUS, MINUS_MINUS, DEREF,
    DOT, DEREF_STAR, DOT_STAR,
    NUMBER, CHAR, OTHER, STRING,IDENTIFIER,
    INVALID,
    TEOF,
};

const char TYPE_MAPPING[] = {
        "KEYWORD_AUTO","KEYWORD_BREAK","KEYWORD_CASE","KEYWORD_CHAR","KEYWORD_CONST",
        "KEYWORD_CONTINUE","KEYWORD_DEFAULT","KEYWORD_DO","KEYWORD_DOUBLE","KEYWORD_ELSE",
        "KEYWORD_ENUM","KEYWORD_EXTERN","KEYWORD_FLOAT","KEYWORD_FOR","KEYWORD_GOTO",
        "KEYWORD_IF","KEYWORD_INT","KEYWORD_LONG","KEYWORD_REGISTER","KEYWORD_RETURN",
        "KEYWORD_SHORT","KEYWORD_SIGNED","KEYWORD_SIZEOF","KEYWORD_STATIC","KEYWORD_STRUCT",
        "KEYWORD_SWITCH","KEYWORD_TYPEDEF","KEYWORD_UNION","KEYWORD_UNSIGNED","KEYWORD_VOID",
        "KEYWORD_VOLATILE","KEYWORD_WHILE",
        "EQ","NOT","GREATER","LESS","PLUS","MINUS","MULT","DIV""",
        "MOD","AND","OR","XOR","RSHIFT","LSHIFT","COMPL","AND_AND","OR_OR","QUERY","COLON",
        "COMMA","OPEN_PAREN","CLOSE_PAREN","EQ_EQ","NOT_EQ",
        "GREATER_EQ","LESS_EQ","PLUS_EQ","MINUS_EQ","MULT_EQ",
        "DIV_EQ","MOD_EQ","AND_EQ","OR_EQ","XOR_EQ","RSHIFT_EQ",
        "LSHIFT_EQ","OPEN_SQUARE","CLOSE_SQUARE","OPEN_BRACE","CLOSE_BRACE",
        "SEMICOLON","PLUS_PLUS","MINUS_MINUS","DEREF",
        "DOT","DEREF_STAR","DOT_STAR",
        "NUMBER","CHAR","OTHER","STRING","IDENTIFIER",
        "INVALID",
        "TEOF",
};


class Token {
public:

    int type;
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
            case CHAR :
                stream << "CHAR," << value.c;
                break;
            case NUMBER:
                stream << "num," << value.number;
                break;
            case IDENTIFIER:
                stream << "id," << value.s;
                break;
            case STRING:
                stream << "STRING," << value.s;
                break;
            case INVALID:
                stream << "INVALID," << value.c;
                break;
            default:stream << "DEFAULT," << type;

        }
        if(type < 32) {
            stream << "KEYWORD," << value.s;
        }
        stream << '>';
        return stream.str();
    }
    static Token *makeToken(int type) {
        Token *t = new Token;
        t->type = type;
        return t;
    }

    static Token *makeToken(int type, std::string s) {
        Token *t = new Token;
        t->type = type;
        t->value.s = s;
        return t;
    }

    static Token *makeToken(int type, int value) {
        Token *t = new Token;
        t->type = type;
        if(type == IDENTIFIER) {
            t->value.id = value;
        }
        else if(type == NUMBER) {
            t->value.number = value;
        }
        return t;
    }

    static Token *makeToken(int type, char c) {
        Token *t = new Token;
        t->type = type;
        t->value.c = c;
        return t;
    }

};

