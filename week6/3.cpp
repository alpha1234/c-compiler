#include "../include/compiler.h"

using namespace std;

bool S();
bool A();
bool A1();
bool B();

string buffer;
int i = -1;

bool S() {
    cout << "Inside S \n";
    i++;
    if (buffer[i] == 'a') {
        if (A()) {
            i++;
            if (buffer[i] == 'c') {
                if (B()) {
                    i++;
                    if (buffer[i] == 'e') {
                        return true;
                    }
                }
            }
        }
    } else {
        i--;
    }
    return false;
}

bool A() {
    cout << "Inside A \n";
    i++;
    if (buffer[i] == 'b') {
        return A1();
    }
    i--;
    return true;
}
bool A1() {
    cout << "Inside A1 \n";
    i++;
    if (buffer[i] == 'b') {
        return A1();
    }
    i--;
    return true;
}
bool B() {
    cout << "Inside B \n";
    i++;
    if(buffer[i] == 'd') {
        return true;
    }
    return false;
}


int main() {
    buffer = "abcde$";
    if(S()) {
        i++;
        if(buffer[i] == '$') {
            cout << "Success";
        }
        else {
            cout<<"Error";
        }
    }
    else {
        cout<<"Error";
    }

    return 0;
}