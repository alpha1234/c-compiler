#include "compiler.h"
#include "common.h"
#include "Token.h"

using namespace std;

FILE *fp;
int filePointerLocation;


const vector <std::string> RESERVED_KEYWORDS = {
        "auto", "break", "case", "char", "const",
        "continue", "default", "do", "double", "else",
        "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return",
        "short", "signed", "sizeof", "static", "struct",
        "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while"
};


const vector<char> SPECIAL_SYMBOLS = {
        '(', ')', ',', ';', '[', ']', '{', '}', '?', '~', ':'
};

const vector<char> OPERATORS = {
        '+', '-', '/', '*', '%', '=', '>', '<', '&', '|',
};


template<typename T>
int indexOf(T s, vector <T> array) {
    for (int i = 0; i < array.size(); i++) {
        if (array[i] == s) {
            return i;
        }
    }
    return -1;
}

inline bool isSpecialSymbol(char c) {
    return indexOf(c, SPECIAL_SYMBOLS) != -1;
}

inline bool isOperator(char c) {
    return indexOf(c, OPERATORS) != -1;
}


Token *readOperator(char c) {
    char state = 0;
    while (1) {
        switch (state) {
            case 0:
                switch(c) {
                    case '-':state = 1;break;
                    case '+':state = 6;break;
                    case '!':state = 10;break;
                    case '~':state = 13;break;
                    case '/':state = 14;break;
                    case '%':state = 17;break;
                    case '<':state = 20;break;
                    case '>':state = 26;break;
                    case '=':state = 32;break;
                    default:
                        return nullptr;
                }
                break;
            case 1:
                c = next(fp);
                if (c == '>') state = 2;
                else if (c == '-') state = 3;
                else if(c == '=') state = 4;
                else state = 5;
                break;
            case 2:
                return Token::makeToken(Type::MEMBER_ACCESS_OPERATOR, "->");
            case 3:
                return Token::makeToken(Type::ARITH_OPERATOR, "--");
            case 4:
                return Token::makeToken(Type::ASSIGN_OPERATOR, "-=");
            case 5:
                shift(fp, -1);
                return Token::makeToken(Type::ARITH_OPERATOR, "-");
            case 6:
                c = next(fp);
                if (c == '+') state = 7;
                else if (c == '=') state = 8;
                else state = 9;
                break;
            case 7:
                return Token::makeToken(Type::ARITH_OPERATOR, "++");
            case 8:
                return Token::makeToken(Type::ASSIGN_OPERATOR,"+=");
            case 9:
                shift(fp, -1);
                return Token::makeToken(Type::ARITH_OPERATOR, "+");
            case 10:
                c = next(fp);
                if(c == '=') state = 11;
                else state = 12;
                break;
            case 11:
                return Token::makeToken(Type::REL_OPERATOR, "!=");
            case 12:
                shift(fp, -1);
                return Token::makeToken(Type::LOGICAL_OPERATOR, "!");
            case 13:
                return Token::makeToken(Type::BITWISE_OPERATOR, "~");
            case 14:
                c = next(fp);
                if(c == '=') state = 15;
                else state = 16;
                break;
            case 15:
                return Token::makeToken(Type::ASSIGN_OPERATOR, "/=");
            case 16:
                shift(fp, -1);
                return Token::makeToken(Type::ARITH_OPERATOR, "/");
            case 17:
                c = next(fp);
                if(c == '=') state = 18;
                else state = 19;
                break;
            case 18:
                return Token::makeToken(Type::ASSIGN_OPERATOR, "%");
            case 19:
                shift(fp, -1);
                return Token::makeToken(Type::ARITH_OPERATOR, "%");
            case 20:
                c = next(fp);
                if (c == '<') state = 21;
                else if (c == '=') state = 24;
                else state = 25;
                break;
            case 21:
                c = next(fp);
                if (c == '=') state = 22;
                else state = 23;
                break;
            case 22:
                return Token::makeToken(Type::ASSIGN_OPERATOR, "<<=");
            case 23:
                shift(fp,-1);
                return Token::makeToken(Type::BITWISE_OPERATOR, "<<");
            case 24:
                return Token::makeToken(Type::REL_OPERATOR, "<=");
            case 25:
                shift(fp,-1);
                return Token::makeToken(Type::REL_OPERATOR, "<");
            case 26:
                c = next(fp);
                if (c == '>') state = 27;
                else if (c == '=') state = 30;
                else state = 31;
                break;
            case 27:
                c = next(fp);
                if (c == '=') state = 28;
                else state = 29;
                break;
            case 28:
                return Token::makeToken(Type::ASSIGN_OPERATOR, ">>=");
            case 29:
                shift(fp,-1);
                return Token::makeToken(Type::BITWISE_OPERATOR, ">>");
            case 30:
                return Token::makeToken(Type::REL_OPERATOR, ">=");
            case 31:
                shift(fp,-1);
                return Token::makeToken(Type::REL_OPERATOR, ">");
            case 32:
                c = next(fp);
                if (c == '=') state = 33;
                else state = 34;
                break;
            case 33:
                return Token::makeToken(Type::REL_OPERATOR, "==");
            case 34:
                shift(fp,-1);
                return Token::makeToken(Type::ASSIGN_OPERATOR, "=");
        }
    }
}

Token *readNumber(char c) {
    string num;
    num.push_back(c);
    while (1) {
        c = next(fp);
        if (c >= '0' && c <= '9') {
            num.push_back(c);
        } else {
            move(-1);
            break;
        }
    }
    return Token::makeToken(Type::NUMBER, atoi(num.c_str()));
}


Token *readStringLiteral() {
    string s;
    char c = next(fp);
    while (c != '"') {
        if (c == EOF) {
            cout << "Unclosed double quote";
            exit(1);
        }
        s.push_back(c);
        c = next(fp);
    }
    return Token::makeToken(Type::STRING_LITERAL, s);
}

char readEscapedChar() {
    switch (next(fp)) {
        case 'a':
            return '\a';
        case 'b':
            return '\b';
        case 'f':
            return '\f';
        case 'n':
            return '\n';
        case 'r':
            return '\r';
        case 't':
            return '\t';
        case 'v':
            return '\v';
        case '\\':
            return '\\';
    }
}


Token *readChar() {
    char c = next(fp);
    if (c == '\\') {
        /* Escaped Char */
        c = readEscapedChar();
    }
    next(fp);
    return Token::makeToken(Type::CHAR_LITERAL, c);
}


Token *readIdentifier(char c) {
    string s;
    s.push_back(c);

    while ((c = next(fp))) {
        if (c == EOF) {
            break;
        }
        if (!(isAlphabet(c) || isDigit(c) || c == '_')) {
            shift(fp, -1);
            break;
        }
        s.push_back(c);
    }
    return Token::makeToken(Type::IDENTIFIER, s);
}

void skipWhitespaces() {
    char c;
    while (c = next(fp)) {
        if (c == EOF)
            break;
        if (!isWhitespace(c)) {
            shift(fp, -1);
            break;
        }
    }
}


Token *getNextToken() {
    skipWhitespaces();
    filePointerLocation = ftell(fp);

    char c = next(fp);
    if (c == '\n') {
        return Token::makeToken(Type::NEWLINE);
    }
    Token * token = readOperator(c);
    if (token != nullptr) {
        return token;
    }
    if (isDigit(c)) {
        return readNumber(c);
    }
    if (c == '"') {
        return readStringLiteral();
    }
    if (c == '\'') {
        return readChar();
    }
    if (isAlphabet(c)) {
        return readIdentifier(c);
    }
    if (isSpecialSymbol(c)) {
        return Token::makeToken(Type::SPECIAL_SYMBOL, c);
    }
    if (c == EOF) {
        return Token::makeToken(Type::TEOF);
    }
    return Token::makeToken(Type::INVALID, c);


}

void undoTokenGet() {
    fseek ( fp , filePointerLocation , SEEK_SET );
}

void lex_initialize(char *inputFileName,char *outputFileName) {
    preprocess(inputFileName, outputFileName);
    fp = openFile(outputFileName, "r");
}

void lex_finalize() {
    fclose(fp);
}



