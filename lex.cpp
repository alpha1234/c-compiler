/*
 * TODO Concatenate adjacent string literals
 */

#include "include/compiler.h"
#include "include/common.h"
#include "include/Token.h"

using namespace std;

FILE *fp,*tokensOutput;
int filePointerLocation;
extern int line;
extern int column;
int tokenBeginColumn,tokenBeginLine;


const vector <std::string> RESERVED_KEYWORDS = {
        "auto", "break", "case", "char", "const",
        "continue", "default", "do", "double", "else",
        "enum", "extern", "float", "for", "goto",
        "if", "int", "long", "register", "return",
        "short", "signed", "sizeof", "static", "struct",
        "switch", "typedef", "union", "unsigned", "void",
        "volatile", "while"
};


Token readNumber(char c) {
    tokenBeginLine = line;
    tokenBeginColumn = column;
    string num;
    num.push_back(c);
    c = next(fp);
    while((isDigit(c) || c == '.') && c != EOF) {
        num.push_back(c);
        c = next(fp);
    }
    shift(fp,-1);

    return Token::makeToken(NUMBER, atoi(num.c_str()));
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

Token readStringLiteral() {
    tokenBeginLine = line;
    tokenBeginColumn = column;

    string s;
    char c = next(fp);
    char prev = 0;
    while (c != '"' || prev == '\\') {
        if(c == '\\') {
            c = readEscapedChar();
        }
        s.push_back(c);
        c = next(fp);
        prev = c;
    }
    return Token::makeToken(STRING, s);
}

Token readChar() {
    tokenBeginLine = line;
    tokenBeginColumn = column;
    char c = next(fp);
    if (c == '\\') {
        c = readEscapedChar();
    }
    next(fp);
    return Token::makeToken(CHAR, c);
}


Token readIdentifier(char c) {
    tokenBeginLine = line;
    tokenBeginColumn = column;
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
    auto index = distance( RESERVED_KEYWORDS.begin(),
                          find(RESERVED_KEYWORDS.begin(), RESERVED_KEYWORDS.end(), s));

    if(index < RESERVED_KEYWORDS.size())
        return Token::makeToken(index);

    return Token::makeToken(IDENTIFIER, s);
}


void skipWhitespaces() {
    char c;
    while ((c = next(fp)) != EOF) {
        if (!isWhitespace(c)) {
            shift(fp, -1);
            break;
        }
        if(c == '\t') {
            column += 3;   //Don't increment by 4. next() function will increment by 1.
        }
    }
}



Token temp() {
    filePointerLocation = ftell(fp);

    char c;
    skipWhitespaces();
    c = next(fp);
    tokenBeginLine = line;
    tokenBeginColumn = column;
    cout<<"h1 \n";
    switch (c) {
        case '\n':
            line++;
            column = 0;
            return temp();

        case '0' ... '9':
            return readNumber(c);
        case '"':
            return readStringLiteral();
        case '\'' :
            return readChar();

        case 'a' ... 'z':
        case 'A' ... 'Z':
        case '_':
            cout<<"h2 \n";
            return readIdentifier(c);

        case ',':
            return Token::makeToken(COMMA);
        case '(':
            return Token::makeToken(OPEN_PAREN);
        case ')':
            return Token::makeToken(CLOSE_PAREN);
        case '[':
            return Token::makeToken(OPEN_SQUARE);
        case ']':
            return Token::makeToken(CLOSE_SQUARE);
        case '{':
            return Token::makeToken(OPEN_BRACE);
        case '}':
            return Token::makeToken(CLOSE_BRACE);
        case ';':
            return Token::makeToken(SEMICOLON);

        case '-':
            c = next(fp);
            if (c == '>') return Token::makeToken(DEREF);
            else if (c == '-') return Token::makeToken(MINUS_MINUS);
            else if (c == '=') return Token::makeToken(MINUS_EQ);
            else {
                shift(fp, -1);
                return Token::makeToken(MINUS);
            }
        case '+':
            c = next(fp);
            if (c == '+') return Token::makeToken(PLUS_PLUS);
            else if (c == '=') return Token::makeToken(PLUS_EQ);
            else {
                shift(fp, -1);
                return Token::makeToken(PLUS);
            }
        case '!':
            c = next(fp);
            if (c == '=') return Token::makeToken(NOT_EQ);
            else {
                shift(fp, -1);
                return Token::makeToken(NOT);
            }
        case '~':
            return Token::makeToken(COMPL);

        case '/':
            c = next(fp);
            if (c == '=') return Token::makeToken(DIV_EQ);

            else {
                shift(fp, -1);
                return Token::makeToken(DIV);
            }
        case '*':
            c = next(fp);
            if (c == '=') return Token::makeToken(MULT_EQ);

            else {
                shift(fp, -1);
                return Token::makeToken(MULT);
            }
        case '%':
            c = next(fp);
            if (c == '=') return Token::makeToken(MOD_EQ);

            else {
                shift(fp, -1);
                return Token::makeToken(MOD);
            }
        case '<':
            c = next(fp);
            if (c == '<') {
                c = next(fp);
                if (c == '=') return Token::makeToken(LSHIFT_EQ);

                else {
                    shift(fp, -1);
                    return Token::makeToken(LSHIFT);
                }
            } else if (c == '=') return Token::makeToken(LESS_EQ);

            else {
                shift(fp, -1);
                return Token::makeToken(LESS);
            }

        case '>':
            c = next(fp);
            if (c == '>') {
                c = next(fp);
                if (c == '=') return Token::makeToken(RSHIFT_EQ);

                else {
                    shift(fp, -1);
                    return Token::makeToken(RSHIFT);
                }
            } else if (c == '=') return Token::makeToken(GREATER_EQ);

            else {
                shift(fp, -1);
                return Token::makeToken(GREATER);
            }
        case '=':
            c = next(fp);
            if (c == '=') return Token::makeToken(EQ_EQ);

            else {
                shift(fp, -1);
                return Token::makeToken(EQ);
            }
        case '&':
            c = next(fp);
            if (c == '&') return Token::makeToken(AND_AND);
            if (c == '=') return Token::makeToken(AND_EQ);

            shift(fp, -1);
            return Token::makeToken(LESS);


        case EOF:
            return Token::makeToken(TEOF);
    }
    return Token::makeToken(INVALID, c);
}

Token getNextToken() {
    Token t = temp();
    t.line = tokenBeginLine;
    t.column = tokenBeginColumn;
    fputs(t.getFormatted().c_str(), tokensOutput);
    fputc('\n',tokensOutput);
    return t;
}

void undoTokenGet() {
    fseek ( fp , filePointerLocation , SEEK_SET );
}

void lex_initialize(const char *inputFileName) {
    fp = openFile(inputFileName, "r");
    tokensOutput = openFile("data/tokens.txt", "w");
}

void lex_finalize() {
    fclose(fp);
    fclose(tokensOutput);
}



