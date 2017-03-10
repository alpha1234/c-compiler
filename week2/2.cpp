#include <iostream>

using namespace std;


int main() {
    cout << "Enter filename:";
    string filename;
    cin >> filename;
    FILE *fp = fopen(filename.c_str(), "r");
    FILE *output = fopen("2_output.txt", "w");
    if (fp == NULL) {
        cout << "Could not open file:" << filename;
        return 1;
    }

    char c;
    string pattern = "#include ";
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
    return 0;

}

