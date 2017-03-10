#include <iostream>

using namespace std;


int main() {
    cout << "Enter filename:";
    string filename;
    cin >> filename;
    FILE *fp = fopen(filename.c_str(), "r");
    if (fp == NULL) {
        cout << "Could not open file:" << filename;
        return 1;
    }
    char choice;
    string output;
    int noOfLinesRead = 0;
    while (1) {
        cout << "Enter - \n";
        cout << "		C, to continue\n";
        cout << "		Q, to quit\n";
        cin >> choice;
        if (choice == 'Q') {
            return 0;
        }

        int c;
        noOfLinesRead = 0;
        output.clear();
        while (((c = fgetc(fp)) != EOF) && noOfLinesRead <= 5) {
            if (c == '\n') {
                noOfLinesRead++;
            }
            output.push_back(c);

        }
        cout << output;
    }
    return 0;

}