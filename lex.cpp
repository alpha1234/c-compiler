#include "compiler.h"

using namespace std;


vector<Token> lexemes;
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


bool iswhitespace(int c) {
    return c == ' ' || c == '\t' || c == '\f' || c == '\v';
}

bool isAlphabet(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

char skip_whitespaces(char c) {
    if (!iswhitespace(c)) {
        return c;
    }
    while (1) {
        c = getNextChar();
        if (!iswhitespace(c)) {
            return c;
        }
    }
}

Token makeToken(Type type) {
    Token token(type);
    return token;
}

Token makeToken(Type type, string value) {
    Token token(type,const_cast<char*>(value.c_str()));
    return token;
}

Token makeToken(Type type, char c) {
    Token token(type,c);
    return token;
}

Token makeToken(Type type, int id) {
    Token token(type,id);
    return token;
}

/*
Token readOperator(char c) {
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
                c = getNextChar();
                if (c == '=') state = 2;
                else if (c == '>') state = 3;
                else state = 4;
                break;
            case 2:
                return makeToken(Type::REL_OPERATOR, "<=");
            case 3:
                return makeToken(Type::REL_OPERATOR, "!=");
            case 4:
                getPreviousChar();
                return makeToken(Type::REL_OPERATOR, "<");
            case 5:
                c = getNextChar();
                if (c == '=') state = 9;
                else state = 10;
                break;
            case 6:
                c = getNextChar();
                if (c == '=') state = 7;
                else state = 8;
                break;
            case 7:
                return makeToken(Type::REL_OPERATOR, ">=");
            case 8:
                getPreviousChar();
                return makeToken(Type::REL_OPERATOR, ">");
            case 9:
                return makeToken(Type::REL_OPERATOR, "==");
            case 10:
                getPreviousChar();
                return makeToken(Type::REL_OPERATOR, "=");
        }
    }
}
*/

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
                c = getNextChar();
                if (c == '=') state = 2;
                else if (c == '>') state = 3;
                else state = 4;
                break;
            case 2:
                return makeToken(Type::REL_OPERATOR, "<=");
            case 3:
                return makeToken(Type::REL_OPERATOR, "!=");
            case 4:
                getPreviousChar();
                return makeToken(Type::REL_OPERATOR, "<");
            case 5:
                c = getNextChar();
                if (c == '=') state = 9;
                else state = 10;
                break;
            case 6:
                c = getNextChar();
                if (c == '=') state = 7;
                else state = 8;
                break;
            case 7:
                return makeToken(Type::REL_OPERATOR, ">=");
            case 8:
                getPreviousChar();
                return makeToken(Type::REL_OPERATOR, ">");
            case 9:
                return makeToken(Type::REL_OPERATOR, "==");
            case 10:
                getPreviousChar();
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
                c = getNextChar();
                if (c == '+') {
                    state = 2;
                } else {
                    state = 3;
                }
                break;
            case 2:
                return makeToken(Type::ARITH_OPERATOR, "++");
            case 3:
                getPreviousChar();
                return makeToken(Type::ARITH_OPERATOR, "+");
            case 4:
                c = getNextChar();
                if (c == '-') {
                    state = 5;
                } else {
                    state = 6;
                }
                break;
            case 5:
                return makeToken(Type::ARITH_OPERATOR, "--");
            case 6:
                getPreviousChar();
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

Token readNumber(char c) {
    string num;
    num.push_back(c);
    while (1) {
        c = getNextChar();
        if (c >= '0' && c <= '9') {
            num.push_back(c);
        } else {
            getPreviousChar();
            break;
        }
    }
    return makeToken(Type::NUMBER, num);
}


Token readStringLiteral() {
    string s;
    char c = getNextChar();
    while (c != '"') {
        s.push_back(c);
        c = getNextChar();
    }
    return makeToken(Type::STRING_LITERAL, s);
}


Token readChar() {
    char c = getNextChar();
    getNextChar();
    return makeToken(Type::CHAR_LITERAL, c);
}

Token readIdentifier(char c) {
    string s;
    s.push_back(c);

    while (1) {
        c = getNextChar();
        if (!(isAlphabet(c) || isDigit(c) || c == '_')) {
            getPreviousChar();
            break;
        }
        s.push_back(c);
    }
    int id = indexOf(s, RESERVED_KEYWORDS);
    if (id != -1) {
        return makeToken(Type::KEYWORD, s);
    }

    struct symbolTableRow row;
    row.name = s;
    if(curlyBracesCount == 0) {
        row.scope = 'G';
    }
    else {
        row.scope = 'L';
    }
    id = indexOfIdentifier(s,row.scope);
    if (id != -1) {
        return makeToken(Type::IDENTIFIER, id);
    }
    c = skip_whitespaces(getNextChar());
    getPreviousChar();
    if(c == '(') {
        row.type = "FUNC";
       // row.returnType = lexemes.back().s;
        row.size = -1;
        int count = 0;
        string parameters;
        getNextChar();
        count++;
        while(1) {
            c = getNextChar();
            count++;
            if(c == ')') {
                break;
            }
            parameters.push_back(c);
        }
        while(count--) {
            getPreviousChar();
        }
        row.arguments = parameters;
        count = 0;
        if(parameters.size() > 0) {
            count++;
        }
        for(int i = 0;i<parameters.size();i++) {
            if(parameters[i] == ',') {
                count++;
            }
        }
        row.noOfArguments = count;
    }
    else {
        row.noOfArguments = -1;
        row.arguments = "";
        row.returnType = "\t";
       // row.type = lexemes.back().s;
        if(row.type == "int") row.size = sizeof(int);
        else if(row.type == "char") row.size = sizeof(char);
        else if(row.type == "double") row.size = sizeof(double);
        else if(row.type == "float") row.size = sizeof(float);
        else if(row.type == "string") row.size = sizeof(string);
    }
    symbolTable.push_back(row);
    id = symbolTable.size() - 1;
    return makeToken(Type::IDENTIFIER, id);
}


Token getNextToken() {
    char c = getNextChar();
    c = skip_whitespaces(c);
    switch (c) {
        case '\n':
            return makeToken(Type::NEWLINE);
        case '>':
        case '<':
        case '=':
            return readRelationalOperator(c);
        case '+':
        case '-':
        case '/':
        case '*':
        case '%':
            return readArithOperator(c);
        case '0' ... '9':
            return readNumber(c);
        case '"':
            return readStringLiteral();
        case '\'':
            return readChar();
        case 'a' ... 'z':
        case 'A' ... 'Z' :
        case '_':
            return readIdentifier(c);
        case '(':
        case ')':
        case ',':
        case ';':
        case '[':
        case ']':
        case '{':
        case '}':
        case '?':
        case '~':
        case ':':
        if(c == '{') {
            curlyBracesCount++;
        }
        else if(c == '}') {
            curlyBracesCount--;
        }
            return makeToken(Type::SPECIAL_SYMBOL, c);
        case -1 :
            return makeToken(Type::TEOF);
       // default:
         // cout << "Not Matched " << (int)c << "\n";

    }

}

int main() {
    char filename[] = "input.txt";
    char outputFileName[] = "output.txt";
    copyFile(filename, outputFileName);
    preprocess(outputFileName);

    initialize(outputFileName);

    Token token;
    while (1) {
        token = getNextToken();
        if (token.type == Type::TEOF)
            break;
       token.print();
        //cout << "\n";
        lexemes.push_back(token);
    }

    closeFile();
        cout<<"ID\tType\tName\tArguments\tSize\tScope\tReturn Type\tNo Of Args\n";

    for (int i = 0; i < symbolTable.size(); i++) {
       cout <<i<<"\t"<<symbolTable[i].type <<"\t"<<symbolTable[i].name <<"\t"<<symbolTable[i].arguments<<"\t\t"<<symbolTable[i].size<<"\t"<< symbolTable[i].scope << "\t"<<symbolTable[i].returnType<<"\t"<<symbolTable[i].noOfArguments<<"\n";
    }
    return 0;
}

