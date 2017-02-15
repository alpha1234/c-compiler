#include <iostream>
#include <stdio.h> 

using namespace std;


int main() {
	string filename;
	FILE *fp;
	int noOfTries = 0;
	while(noOfTries < 3) {
		cout<<"Enter filename:";
		cin>>filename;
		fp = fopen(filename.c_str(),"r");
		if (fp != NULL) {
			break;
		}
		cout<<"File not found."<<2 - noOfTries<<" tries left\n";
		noOfTries++;
	}
	if(fp == NULL) {
		cout<<"Only 3 tries are allowed\n";
		return 0;
	}
	cout<<"Success\n";

	
	return 0;

}