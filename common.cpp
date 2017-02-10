#include "compiler.h"

#define BUFFER_SIZE 10000


FILE *fp = nullptr;

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
    while (size_t size = fread(buf, 1, sizeof(buf)/sizeof(buf[0]), f1)) {
        fwrite(buf, 1, size, f2);
    }
    fclose(f1);
    fclose(f2);
}

void initialize(char *filename) {
    fp = openFile(filename, "r");
}


void finalize() {
    fclose(fp);
}

char next() {
    return fgetc(fp);
}

char prev() {
    if(ftell(fp) == 1) {
        fseek(fp, -1, SEEK_CUR);
    }
    else {
        fseek(fp, -2, SEEK_CUR);
    }
    return fgetc(fp);
}

void shift(int m) {
    fseek ( fp , m , SEEK_CUR );
}

void undo(char c) {
    ungetc(c,fp);
}

void ab() {
    cout<<"Position "<<ftell(fp)<<"\n";
}


void skipWhitespaces() {
    char c;
    while(c = next()) {
        if( c == EOF)
            break;
        if(!isWhitespace(c)){
            shift(-1);
            break;
        }
    }
}