#include <iostream>

using namespace std;

int main() {
    cout << "Enter filename:";
    string filename;
    cin >> filename;
    FILE *fp = fopen(filename.c_str(), "r");
    FILE *output = fopen("4_output.txt", "w");
    if (fp == NULL) {
        cout << "Could not open file:" << filename;
        return 1;
    }
    char c;
    while ((c = fgetc(fp)) != EOF) {
        if (c != '\t' && c != '\n')
            fputc(c, output);
    }

    return 0;

}