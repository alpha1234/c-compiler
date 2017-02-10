#include "compiler.h"
#include "common.h"
#include "HashTable.h"
#include "Token.h"
#include "SymbolTable.h"

using namespace std;

HashMap<SymbolTableRow> symbolTable;
FILE *fp;

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
                c = next(fp);
                if (c == '=') state = 2;
                else if (c == '>') state = 3;
                else state = 4;
                break;
            case 2:
                return Token::makeToken(Type::REL_OPERATOR, "<=");
            case 3:
                return Token::makeToken(Type::REL_OPERATOR, "!=");
            case 4:
                prev(fp);
                return Token::makeToken(Type::REL_OPERATOR, "<");
            case 5:
                c = next(fp);
                if (c == '=') state = 9;
                else state = 10;
                break;
            case 6:
                c = next(fp);
                if (c == '=') state = 7;
                else state = 8;
                break;
            case 7:
                return Token::makeToken(Type::REL_OPERATOR, ">=");
            case 8:
                prev(fp);
                return Token::makeToken(Type::REL_OPERATOR, ">");
            case 9:
                return Token::makeToken(Type::REL_OPERATOR, "==");
            case 10:
                prev(fp);
                return Token::makeToken(Type::REL_OPERATOR, "=");
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
                c = next(fp);
                if (c == '=') state = 2;
                else if (c == '>') state = 3;
                else state = 4;
                break;
            case 2:
                return Token::makeToken(Type::REL_OPERATOR, "<=");
            case 3:
                return Token::makeToken(Type::REL_OPERATOR, "!=");
            case 4:
                prev(fp);
                return Token::makeToken(Type::REL_OPERATOR, "<");
            case 5:
                c = next(fp);
                if (c == '=') state = 9;
                else state = 10;
                break;
            case 6:
                c = next(fp);
                if (c == '=') state = 7;
                else state = 8;
                break;
            case 7:
                return Token::makeToken(Type::REL_OPERATOR, ">=");
            case 8:
                prev(fp);
                return Token::makeToken(Type::REL_OPERATOR, ">");
            case 9:
                return Token::makeToken(Type::REL_OPERATOR, "==");
            case 10:
                prev(fp);
                return Token::makeToken(Type::REL_OPERATOR, "=");
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
                c = next(fp);
                if (c == '+') {
                    state = 2;
                } else {
                    state = 3;
                }
                break;
            case 2:
                return Token::makeToken(Type::ARITH_OPERATOR, "++");
            case 3:
                prev(fp);
                return Token::makeToken(Type::ARITH_OPERATOR, "+");
            case 4:
                c = next(fp);
                if (c == '-') {
                    state = 5;
                } else {
                    state = 6;
                }
                break;
            case 5:
                return Token::makeToken(Type::ARITH_OPERATOR, "--");
            case 6:
                prev(fp);
                return Token::makeToken(Type::ARITH_OPERATOR, "-");
            case 7:
                return Token::makeToken(Type::ARITH_OPERATOR, "/");
            case 8:
                return Token::makeToken(Type::ARITH_OPERATOR, "*");
            case 9:
                return Token::makeToken(Type::ARITH_OPERATOR,"%");
        }
    }
}
*/
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
    return Token::makeToken(Type::NUMBER, num);
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
    int id = indexOf(s, RESERVED_KEYWORDS);
    if (id != -1) {
        return Token::makeToken(Type::KEYWORD, s);
    }

    SymbolTableRow row;
    row.name = s;
    id = symbolTable.search(row);
    if (id != -1) {
        return Token::makeToken(Type::IDENTIFIER, id);
    }
    id = symbolTable.insert(row);
    return Token::makeToken(Type::IDENTIFIER, id);
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
    char c = next(fp);
    if (c == '\n') {
        return Token::makeToken(Type::NEWLINE);
    }
    if (isOperator(c)) {
        //  return readOperator(c);
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

int main() {
    char inputFileName[] = "data\\input.txt";
    char outputFileName[] = "data\\output.txt";
    char tempFileName[] = "data\\temp.txt";
    preprocess(inputFileName, outputFileName);

    fp = openFile(outputFileName, "r");
    ofstream output(tempFileName, ios::out);

    Token *token;
    while (1) {
        token = getNextToken();
        if (token->type == Type::TEOF) {
            break;
        }
        output << token->print();
        delete token;
    }
    output.close();
    fclose(fp);
    copyFile(tempFileName, outputFileName);

    cout << "\nID\tName\n";
    symbolTable.print();

    return 0;

}

