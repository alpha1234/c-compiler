#pragma once

FILE *openFile(std::string a, const char *b);

void copyFile(char *, char *);

char next(FILE *);

char prev(FILE *);

void undo(FILE *, char);

void shift(FILE *, int);

void ab(FILE *);

char peek(FILE *,int);

void preprocess(char *, char *);


inline bool isWhitespace(int c) {
    return c == ' ' || c == '\t' || c == '\f' || c == '\v';
}

inline bool isAlphabet(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

inline bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}