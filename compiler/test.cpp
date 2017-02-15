#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "common.h"

int main () {
   FILE * f = openFile("data//input.txt","r");
std::cout<<next(f)<<next(f);
    std::cout<<peek(f,-1);
    std::cout<<next(f);
    return 0;
}