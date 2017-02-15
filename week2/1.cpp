#include <iostream>
#include <stdio.h> 

using namespace std;


int main() {
	cout<<"Enter filename:";
	string filename;
	cin>>filename;
	FILE *fp = fopen(filename.c_str(),"r");
	FILE *output = fopen("1_output.txt","w");
	if (fp == NULL) {
    	cout<<"Could not open file:"<<filename;
        return 1;
    }

	int c;
	while((c = fgetc(fp)) != EOF) {
		if(c != ' ')
			fputc(c,output);
	}
		
	return 0;

}