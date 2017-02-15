#include <iostream>
#include <stdio.h> 

using namespace std;


int main() {
	string file1,file2;
	cout<<"Enter file 1:";
	cin>>file1;
	cout<<"Enter file 2:";
	cin>>file2;
	FILE *fp1 = fopen(file1.c_str(),"r");
	if (fp1 == NULL) {
		cout<<"Could not open file:"<<file1;
		return 1;
	}

	FILE *fp2 = fopen(file2.c_str(),"r");
	if (fp2 == NULL) {
		cout<<"Could not open file:"<<file2;
		return 1;
	}
	char c1,c2;
	while((c1 = fgetc(fp1)) && (c2 = fgetc(fp2))) {
		if(c1 == EOF || c2 == EOF) {
			break;
		}
		if(c1 != c2) {
			break;
		}
	}
	if(c1 != c2) {
		cout<<"Files are not identical\n";
	}
	else {
		cout<<"Files are identical\n";
	}

	return 0;

}