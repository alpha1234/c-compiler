#include <iostream>
#include <vector>
#include <algorithm>

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

    vector<string> keywords = {"main","while","for","int","char"};
    vector<string> output;
	char c;
	int count = 0;
	string word;
	int found = 0;
	while((c = fgetc(fp)) != EOF) {
		for(int i = 0;i < keywords.size(); i++) {
			count = 0;
			word.erase();
			found = 0;
			while(c == keywords[i][count]) {
				word.push_back(c);
				if((count + 1)== keywords[i].size()) {
					output.push_back(word);
					found = 1;
					break;
				}
				c = fgetc(fp);
				count++;
			}
			if(found == 1) {
				break;
			}
			if(count != 0) {
				fseek(fp, ftell(fp) - count ,SEEK_SET);
			}
		}
	}

	for(int i = 0;i<output.size();i++) {
		transform(output[i].begin(), output[i].end(),output[i].begin(), ::toupper);
		cout<<output[i].c_str()<<"\n";
	}

	return 0;

}

