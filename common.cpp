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

void ab(FILE *fp) {
    cout << "Position " << ftell(fp) << "\n";
}


void preprocess(char inputFileName[], char outputFileName[]) {
    FILE *input = openFile(inputFileName, "r");
    FILE *output = openFile(outputFileName, "w");
    char c;
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
        if (c == '#' && isPreviousNonSpaceNewline) {
            while ((c = next(input)) != '\n');
            isPreviousNonSpaceNewline = true;
        }
        if (isWhitespace(c)) {
            isPreviousNonSpaceNewline = true;
        } else {
            isPreviousNonSpaceNewline = false;
        }
        if (c == '/') {
            c = next(input);
            if (c == '*') {
                while ((c = next(input)) != EOF) {
                    if (c == '\n') {
                        fputc(c, output);
                    } else if (c == '*' && next(input) == '/') {
                        break;
                    }
                }
                continue;
            } else if (c == '/') {
                while (next(input) != '\n');
                fputc('\n', output);
                continue;
            }
            fputc('/', output);
        }
        fputc(c, output);
    }
    fclose(output);
    fclose(input);

}