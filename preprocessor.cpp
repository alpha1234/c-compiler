#include "include/compiler.h"
#include "include/common.h"
#include "include/preprocessor.h"
#include <string.h>


using namespace std;


void removeComments(const char *inputFileName, const char *outputFileName) {
    if(strcmp(inputFileName,outputFileName) == 0) {
        cout<<"Input and Outut filename cannot be same : removeComments()";
        exit(1);
    }

    FILE *input = openFile(inputFileName, "r");
    FILE *output = openFile(outputFileName, "w");
    char c,d;
    while ((c = next(input)) != EOF) {
        if (c == '"') {
            do {
                fputc(c, output);
                if (c == EOF) {
                    cout << "Unclosed double quote";
                    exit(1);
                }
            } while ((c = next(input)) != '"');
            fputc('"', output);
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


void processIncludes(const char inputFileName[],const char outputFileName[]) {
    if(strcmp(inputFileName,outputFileName) == 0) {
        cout<<"Input and Outut filename cannot be same : processIncludes()";
        exit(1);
    }
    FILE *input = openFile(inputFileName, "r");
    FILE *output = openFile(outputFileName, "w");
    bool isPreviousNonSpaceNewline = true;
    char c;
    while ((c = next(input)) != EOF) {
        if (isPreviousNonSpaceNewline && !isWhitespace(c)) {
            isPreviousNonSpaceNewline = false;
        }
        if (isPreviousNonSpaceNewline && c == '#') {
            while (1) {
                c = next(input);
                if (c == '\n' || c == EOF) {
                    break;
                }
            }
        }
        fputc(c, output);
    }
    fclose(output);
    fclose(input);

}