#include "compiler.h"

char tempFileName[] = "temp.txt";


void preprocess(char fileName[]) {
    FILE *fp = openFile(fileName, "r");
    FILE *output = openFile(tempFileName, "w+");
    char c;
    bool isPreviousNonSpaceNewline = true;
    while ((c = fgetc(fp)) != EOF) {
        if(c == '"') {
            fputc('"', output);
            while((c = fgetc(fp)) != '"') {
                fputc(c, output);
            }
            fputc('"', output);
            continue;
        }
        if(c == '#' && isPreviousNonSpaceNewline) {
            while((c = fgetc(fp)) != '\n');
            isPreviousNonSpaceNewline = true;
        }
        if(c == '\n' || c == ' ' || c == '\t') {
            isPreviousNonSpaceNewline = true;
        } else {
            isPreviousNonSpaceNewline = false;
        }
        if(c == '/') {
            c = fgetc(fp);
            if(c == '*') {
                while((c = fgetc(fp)) != EOF) {
                    if(c == '\n') {
                        fputc(c,output);
                    }
                    else if( c == '*' && fgetc(fp) == '/') {
                        break;
                    }
                }
                continue;
            }
            else if(c == '/') {
                while(fgetc(fp) != '\n');
                fputc('\n',output);
                continue;
            }
            fputc('/',output);
        }
        fputc(c, output);
    }
    fclose(output);
    copyFile(tempFileName, fileName);

    }
/*
void removePreProcessorDirectives(char fileName[]) {
    FILE *fp = openFile(fileName, "r");
    FILE *output = openFile(tempFileName, "w+");
    char c;
    int flag = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c == '#')
            flag = 1;
        if (flag == 1) {
            if (c == '\n') {
                flag = 0;
                continue;
            }
        }
        if (flag == 0) {
            fputc(c, output);
        }
    }
    fclose(output);
    copyFile(tempFileName, fileName);
}

void removeComments(char fileName[]) {
    FILE *fp = fopen(fileName, "r");
    FILE *output = openFile(tempFileName, "w+");
    char c;
    bool insideDoubleQuotes = false;
    char prev = ' ';
    char prev_prev;
    bool insideSLComment = false;
    bool insideMLComment = false;
    while ((c = fgetc(fp)) != EOF) {
        if (!insideDoubleQuotes && !insideSLComment && !insideMLComment && c == '"') {
            insideDoubleQuotes = true;
        }
        if (insideDoubleQuotes && c == '"') {
            insideDoubleQuotes = false;
        }
        if (insideDoubleQuotes) {
            fputc(prev, output);
            continue;
        }
        if (c == '/' && prev == '/') {
            insideSLComment = true;
        } else if (c == '*' && prev == '/') {
            insideMLComment = true;
        }
        if (!insideSLComment && !insideMLComment) {
            fputc(prev, output);
        }
        if (insideSLComment && c == '\n') {
            insideSLComment = false;
        } else if (insideMLComment && prev_prev == '*' && prev == '/') {
            insideMLComment = false;
        }

        prev_prev = prev;
        prev = c;
    }
    fclose(output);
    copyFile(tempFileName, fileName);
}
void clean(char fileName[]) {
    FILE *fp = fopen(fileName, "r");
    FILE *output = openFile(tempFileName, "w+");
    char c;
    bool insideDoubleQuotes = false;
    while ((c = fgetc(fp)) != EOF) {

        if (!insideDoubleQuotes && c == '"') {
            insideDoubleQuotes = true;
        } else if (insideDoubleQuotes && c == '"') {
            insideDoubleQuotes = false;
        }
        if (insideDoubleQuotes) {
            fputc(c, output);
            continue;
        }

        if (c != '\n') {
            fputc(c, output);
        }

    }

    fclose(output);
    copyFile(tempFileName, fileName);
}
*/


