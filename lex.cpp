#include "compiler.h"

using namespace std;
HashMap<SymbolTableRow *> symbolTable;

const vector<char> SPECIAL_SYMBOLS = {
        '(', ')', ',', ';', '[', ']', '{', '}', '?', '~', ':'
};

const vector<char> OPERATORS = {
        '+', '-', '/', '*','%', '=','>','<','&','|',
};

vector<Token *> lexemes;
int curlyBracesCount = 0;

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
    return indexOf(c,SPECIAL_SYMBOLS) != -1;
}

inline bool isOperator(char c) {
    return indexOf(c,OPERATORS) != -1;
}


inline Token * makeToken(Type type) {
    Token *token = new Token(type);
    return token;
}

template <typename T>
inline Token * makeToken(Type type, T c) {
    Token *token = new Token(type,c);
    return token;
}


Token * readOperator(char c) {
    char state = 0;
    while (1) {
        switch (state) {
            case 0:
                if (c == '>') state = 1;
                else if (c == '<') state = 5;
                else if (c == '=') state = 6;
                else if (c == '!') state = 6;
                else if (c == '>') state = 6;
                else if (c == '>') state = 6;
                else if (c == '>') state = 6;
                else if (c == '>') state = 6;
                else if (c == '>') state = 6;
                else if (c == '>') state = 6;

                break;
            case 1:
                c = next();
                if (c == '=') state = 2;
                else if (c == '>') state = 3;
                else state = 4;
                break;
            case 2:
                return makeToken(Type::REL_OPERATOR, "<=");
            case 3:
                return makeToken(Type::REL_OPERATOR, "!=");
            case 4:
                prev();
                return makeToken(Type::REL_OPERATOR, "<");
            case 5:
                c = next();
                if (c == '=') state = 9;
                else state = 10;
                break;
            case 6:
                c = next();
                if (c == '=') state = 7;
                else state = 8;
                break;
            case 7:
                return makeToken(Type::REL_OPERATOR, ">=");
            case 8:
                prev();
                return makeToken(Type::REL_OPERATOR, ">");
            case 9:
                return makeToken(Type::REL_OPERATOR, "==");
            case 10:
                prev();
                return makeToken(Type::REL_OPERATOR, "=");
        }
    }
}

/*

Token readRelationalOperator(char c) {
    char state = 0;
    while (1) {
        switch (state) {
            case 0:
                if (c == '<') state = 1;
                else if (c == '=') state = 5;
                else if (c == '>') state = 6;
                break;
            case 1:
                c = next();
                if (c == '=') state = 2;
                else if (c == '>') state = 3;
                else state = 4;
                break;
            case 2:
                return makeToken(Type::REL_OPERATOR, "<=");
            case 3:
                return makeToken(Type::REL_OPERATOR, "!=");
            case 4:
                prev();
                return makeToken(Type::REL_OPERATOR, "<");
            case 5:
                c = next();
                if (c == '=') state = 9;
                else state = 10;
                break;
            case 6:
                c = next();
                if (c == '=') state = 7;
                else state = 8;
                break;
            case 7:
                return makeToken(Type::REL_OPERATOR, ">=");
            case 8:
                prev();
                return makeToken(Type::REL_OPERATOR, ">");
            case 9:
                return makeToken(Type::REL_OPERATOR, "==");
            case 10:
                prev();
                return makeToken(Type::REL_OPERATOR, "=");
        }
    }
}

Token readArithOperator(char c) {
    char state = 0;
    while (1) {
        switch (state) {
            case 0:
                if (c == '+') state = 1;
                else if (c == '-') state = 4;
                else if (c == '/') state = 7;
                else if (c == '*') state = 8;
                else if (c == '%') state = 9;

                break;
            case 1:
                c = next();
                if (c == '+') {
                    state = 2;
                } else {
                    state = 3;
                }
                break;
            case 2:
                return makeToken(Type::ARITH_OPERATOR, "++");
            case 3:
                prev();
                return makeToken(Type::ARITH_OPERATOR, "+");
            case 4:
                c = next();
                if (c == '-') {
                    state = 5;
                } else {
                    state = 6;
                }
                break;
            case 5:
                return makeToken(Type::ARITH_OPERATOR, "--");
            case 6:
                prev();
                return makeToken(Type::ARITH_OPERATOR, "-");
            case 7:
                return makeToken(Type::ARITH_OPERATOR, "/");
            case 8:
                return makeToken(Type::ARITH_OPERATOR, "*");
            case 9:
                return makeToken(Type::ARITH_OPERATOR,"%");
        }
    }
}
*/
Token * readNumber(char c) {
    string num;
    num.push_back(c);
    while (1) {
        c = next();
        if (c >= '0' && c <= '9') {
            num.push_back(c);
        } else {
            move(-1);
            break;
        }
    }
    return makeToken(Type::NUMBER, num);
}


Token * readStringLiteral() {
    string s;
    char c = next();
    while (c != '"') {
        if(c == EOF) {
            cout<<"Unclosed double quote";
            exit(1);
        }
        s.push_back(c);
        c = next();
    }
    return makeToken(Type::STRING_LITERAL, s);
}

char readEscapedChar() {
    switch (next()) {
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


Token * readChar() {
    char c = next();
    if(c == '\\') {
        /* Escaped Char */
        c = readEscapedChar();
    }
    next();
    return makeToken(Type::CHAR_LITERAL, c);
}



Token * readIdentifier(char c) {
    string s;
    s.push_back(c);

    while ((c = next())) {
        if(c == EOF) {
            break;
        }
        if (!(isAlphabet(c) || isDigit(c) || c == '_')) {
            shift(-1);
            break;
        }
        s.push_back(c);
    }
    int id = indexOf(s, RESERVED_KEYWORDS);
    if (id != -1) {
        return makeToken(Type::KEYWORD, s);
    }

    SymbolTableRow *row = new SymbolTableRow;
    row->name = s;
    id = symbolTable.search(row);
    if (id != -1) {
        return makeToken(Type::IDENTIFIER, id);
    }
    id = symbolTable.insert(row);
    return makeToken(Type::IDENTIFIER, id);
}


Token * getNextToken() {
    skipWhitespaces();
    char c = next();
    if(c == '\n') {
        return makeToken(Type::NEWLINE);
    }
    if(isOperator(c)) {
      //  return readOperator(c);
    }
    if(isDigit(c)) {
        return readNumber(c);
    }
    if(c == '"') {
        return readStringLiteral();
    }
    if(c == '\'') {
        return readChar();
    }
    if(isAlphabet(c)) {
        return readIdentifier(c);
    }
    if(isSpecialSymbol(c)) {
        if(c == '{') {
            curlyBracesCount++;
        }
        else if(c == '}') {
            curlyBracesCount--;
        }
        return makeToken(Type::SPECIAL_SYMBOL, c);
    }
    if(c == EOF) {
        return makeToken(Type::TEOF);
    }
    cout<<"NOt MATCHED "<<(int)c<<"\n";


}

int main() {
    char filename[] = "input.txt";
    char outputFileName[] = "output.txt";
    copyFile(filename, outputFileName);
    preprocess(outputFileName);

    initialize(outputFileName);

    Token *token;
    while (1) {
        token = getNextToken();
        if (token->type == Type::TEOF)
            break;
        token->print();
        lexemes.push_back(token);
    }

    finalize();
    cout << "\nName\n";
    symbolTable.print();
    return 0;
}

