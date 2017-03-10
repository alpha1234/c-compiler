
#include "include/common.h"
#include "include/preprocessor.h"
#include <string.h>

using namespace std;


void removeComments(const char inputFileName[], const char outputFileName[]) {
    if (strcmp(inputFileName, outputFileName) == 0) {
        cout << "Input and Outut filename cannot be same : removeComments()";
        exit(1);
    }
    FILE *input = openFile(inputFileName, "r");
    FILE *output = openFile(outputFileName, "w");
    char c, d;
    while ((c = next(input)) != EOF) {
        if (c == '"') {
            do {
                if (c == EOF) {
                    cout << "Unclosed double quote \n";
                    exit(1);
                }
                fputc(c, output);
                c = next(input);
            } while (c != '"');
            fputc('"', output);
            continue;
        }
        if (c == '/') {
            d = peek(input, 1);
            if (d == '*') {
                while ((d = next(input)) != EOF) {
                    if (d == '\n') {
                        fputc('\n', output);
                    } else if (d == '*') {
                        d = next(input);
                        if (d == '/') {
                            break;
                        }
                        if (d == '\n') {
                            fputc('\n', output);
                        }
                    }
                }
                continue;
            } else if (d == '/') {
                while (1) {
                    d = next(input);
                    if (d == '\n' || d == EOF) {
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


void processIncludes(const char inputFileName[], const char outputFileName[]) {
    if (strcmp(inputFileName, outputFileName) == 0) {
        cout << "Input and Outut filename cannot be same : processIncludes()";
        exit(1);
    }
    FILE *input = openFile(inputFileName, "r");
    FILE *output = openFile(outputFileName, "w");
    bool isPreviousNonSpaceNewline = true;
    char c;
    while ((c = next(input)) != EOF) {
        if (c == '\n') {
            isPreviousNonSpaceNewline = true;
        }
        if (isPreviousNonSpaceNewline) {
            if (!isWhitespace(c) && c != '\n') {
                isPreviousNonSpaceNewline = false;
            }
            if (c == '#') {
                while ((c = next(input)) != EOF) {
                    if (c == '\n') {
                        isPreviousNonSpaceNewline = true;
                        break;
                    }
                }
            }
        }
        fputc(c, output);
    }
    fclose(output);
    fclose(input);

}