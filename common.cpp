#include <iostream>


using namespace std;

/* extern variables */
int line, column;

FILE *openFile(const char *fileName, const char *mode) {
    FILE *fp = fopen(fileName, mode);
    column = 0;
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

void shift(FILE *fp, long int m) {
    column = column + m;
    fseek(fp, m, SEEK_CUR);
}

char peek(FILE *fp, long int m) {
    shift(fp, m - 1);
    char c = next(fp);
    shift(fp, -m);
    return c;
}
