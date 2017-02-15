#include <iostream>
#include <stdio.h> 

using namespace std;


int main() {
	cout<<"Enter filename:";
	string filename;
	cin>>filename;
	FILE *fp = fopen(filename.c_str(),"r");
	if (fp == NULL) {
    	cout<<"Could not open file:"<<filename;
        return 1;
    }

	int c;
	int noOfCharacters = 0,noOfLines = 0;
	while((c = fgetc(fp)) != EOF) {
		if(c != '\n') {
			noOfCharacters++;
		}
		else {
			noOfLines++;
		}
	}
	cout<<"No of Lines:"<<noOfLines<<"\n";
	cout<<"No Of Characters:"<<noOfCharacters<<"\n";

	return 0;

}