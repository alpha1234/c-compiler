#include "include/compiler.h"
#include "include/common.h"

using namespace std;

/* extern variables */
int line,column;

FILE *openFile(const char * fileName, const char *mode) {
    FILE *fp = fopen(fileName, mode);
    column = 1;
    line = 1;
    if (fp == NULL) {
        cout << "Could not open file:" << fileName;
        exit(1);
    }
    return fp;
}

void copyFile(const char *source, const char *destination) {
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
    column++;
    return fgetc(fp);
}

void shift(FILE *fp, int m) {
    column = column + m;
    fseek(fp, m, SEEK_CUR);
}

void undo(FILE *fp, char c) {
    column--;
    ungetc(c, fp);
}

char peek(FILE *fp,int m) {
    shift(fp,m-1);
    char c = next(fp);
    shift(fp,-m );
    return c;
}


int indexOf(vector<string> array,string s) {
    for(int i= 0;i< array.size();i++) {
        if(array[i] == s) {
            return i;
        }
    }
    return -1;
}

bool inArray(vector<string> array,string s) {
    for(int i= 0;i< array.size();i++) {
        if(array[i] == s) {
            return true;
        }
    }
    return false;
}


/*
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
                c = next(input);
            } else if (d == '/') {
                while (1) {
                    d = next(input);
                    if(d == '\n' || d == EOF) {
                        isPreviousNonSpaceNewline = true;

                        break;
                    }
                }
                fputc('\n', output);
                c = next(input);
            }
        }
        fputc(c, output);
    }
    fclose(output);
    fclose(input);

}

 */