#include <iostream>
#include <stdio.h> 

using namespace std;



string readLine1(FILE *fp) {
	string output;
	char c;
	while((c = fgetc(fp)) != EOF) {
		output.push_back(c);
		if(c == '\n') {
			break;
		}
	}
	return output;
}
int main() {
	string file1,file2,file3 = "result.txt";
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
	FILE *fp3 = fopen(file3.c_str(),"w");
	if (fp2 == NULL) {
		cout<<"Could not open file:"<<file3;
		return 1;
	}
	int file1Finished = 0,file2Finished = 0;
	string line,output;
	char c;
	while(1) {
		if(!file1Finished) {
			line.clear();		
			while(c = fgetc(fp1)) {
				if(c == EOF) {
					file1Finished = 1;
					break;
				}
				line.push_back(c);
				if(c == '\n') {
					break;
				}
			}
			output.append(line);

		}

		if(!file2Finished) {
			line.clear();		
			while(c = fgetc(fp2)) {
				if(c == EOF) {
					file2Finished = 1;
					break;
				}
				line.push_back(c);
				if(c == '\n') {
					break;
				}

			}
			output.append(line);

		}
		
		if(file1Finished && file2Finished) {
			break;
		}
	}
	cout<<output;

	return 0;

}