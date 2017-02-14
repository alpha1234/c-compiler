#include "compiler.h"
#include "common.h"

using namespace std;


FILE *openFile(string fileName, const char mode[]) {
    FILE *fp = fopen(fileName.c_str(), mode);
    if (fp == NULL) {
        cout << "Could not open file:" << fileName;
        exit(1);
    }
    return fp;
}

void copyFile(char source[], char destination[]) {
    FILE *f1 = openFile(source, "r");
    FILE *f2 = openFile(destination, "w");
    char buf[1000];
    while (size_t size = fread(buf, 1, sizeof(buf) / sizeof(buf[0]), f1)) {
        fwrite(buf, 1, size, f2);
    }
    fclose(f1);
    fclose(f2);
}

char next(FILE *fp) {
    return fgetc(fp);
}

char prev(FILE *fp) {
    if (ftell(fp) == 1) {
        fseek(fp, -1, SEEK_CUR);
    } else {
        fseek(fp, -2, SEEK_CUR);
    }
    return fgetc(fp);
}

void shift(FILE *fp, int m) {
    fseek(fp, m, SEEK_CUR);
}

void undo(FILE *fp, char c) {
    ungetc(c, fp);
}

char peek(FILE *fp,int m) {
    shift(fp,m-1);
    char c = next(fp);
    shift(fp,-m );
    return c;
}

void ab(FILE *fp) {
    cout << "Position " << ftell(fp) << "\n";
}


void preprocess(char inputFileName[], char outputFileName[]) {
    FILE *input = openFile(inputFileName, "r");
    FILE *output = openFile(outputFileName, "w");
    char c,d;
    bool isPreviousNonSpaceNewline = true;
    while ((c = next(input)) != EOF) {
        if (c == '"') {
            fputc('"', output);
            while ((c = next(input)) != '"') {
                fputc(c, output);
            }
            fputc('"', output);
            continue;
        }
        if(isPreviousNonSpaceNewline && !isWhitespace(c)) {
            isPreviousNonSpaceNewline = false;
        }
        if (c == '#') {
            while (1) {
                c = next(input);
                if(c == '\n' || c == EOF) {
                    isPreviousNonSpaceNewline = true;
                    break;
                }
            }
            continue;
        }
        if (c == '/') {
            d = peek(input,1);
            if (d == '*') {
                while ((d = next(input)) != EOF) {
                    if (d == '\n') {
                        fputc('\n', output);
                    } else if (d == '*' && next(input) == '/') {
                        break;
                    }
                }
                continue;
            } else if (d == '/') {
                while (1) {
                    d = next(input);
                    if(d == '\n' || d == EOF) {
                        isPreviousNonSpaceNewline = true;

                        break;
                    }
                }
                fputc('\n', output);
                continue;
            }
        }
        fputc(c, output);
    }
    fclose(output);
    fclose(input);

}