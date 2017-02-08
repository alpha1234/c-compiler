#include "compiler.h"

#define BUFFER_SIZE 10000


FILE *fp = nullptr;
/*
char buffer[2][BUFFER_SIZE + 1] = {0};
int currentlyLoadedBufferIndex = -1;
int currentCharIndex = -1;
int currentBufferIndex = 0;
*/

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
    FILE *f1 = fopen(source, "r");
    FILE *f2 = fopen(destination, "w");
    char buf[100];
    while (size_t size = fread(buf, 1, 100, f1)) {
        fwrite(buf, 1, size, f2);
    }
    fclose(f1);
    fclose(f2);
}

void initialize(char *filename) {
    fp = openFile(filename, "r");
    /*
    readNextBuffer();
    buffer[0][BUFFER_SIZE] = EOF;
    buffer[1][BUFFER_SIZE] = EOF;
     */
}


void closeFile() {
    fclose(fp);
}
/*
bool readNextBuffer() {
    currentlyLoadedBufferIndex = (currentlyLoadedBufferIndex + 1) % 2;
    size_t length = fread(buffer[currentlyLoadedBufferIndex], sizeof(char), BUFFER_SIZE, fp);
    if (ferror(fp) != 0) {
        cout << "Error in reading file";
        return false;
    } else {
        buffer[currentlyLoadedBufferIndex][length] = EOF;
    }
    return true;
}
*/
char getNextChar() {
    /*
    currentCharIndex++;
    if (buffer[currentBufferIndex][currentCharIndex] == EOF) {
        if (currentCharIndex < BUFFER_SIZE) {
            return EOF;
        }
        currentBufferIndex = (currentBufferIndex + 1) % 2;
        currentCharIndex = -1;
        readNextBuffer();
        return getNextChar();
    }
    return buffer[currentBufferIndex][currentCharIndex];
     */
    return fgetc(fp);
}

char getPreviousChar() {
    /*
    currentCharIndex--;
    if (currentCharIndex == -1) {
        currentCharIndex = BUFFER_SIZE - 1;
        currentBufferIndex = (currentBufferIndex + 1) % 2;
    }
    return buffer[currentBufferIndex][currentCharIndex];
     */
    fseek ( fp , -2 , SEEK_CUR );
    return fgetc(fp);
}

