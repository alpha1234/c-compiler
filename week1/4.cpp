#include <iostream>

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
	fseek(fp, 0L, SEEK_END);
	size_t sizeOfFile = ftell(fp);
	cout<<"Size:"<<sizeOfFile<<" "<<(sizeOfFile == 1 ? "Byte" : "Bytes")<<"\n";

	return 0;

}