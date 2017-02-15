#include <iostream>
#include <vector>
#include <string>
using namespace std;



struct production {
    string lhs;
    vector<vector<string>> rhs;
};
typedef struct production Production;

vector<Production> grammar;

void printGrammar() {
        for(int i = 0;i<grammar.size();i++) {
            cout<<grammar[i].lhs<< "->";
            for(int j = 0;j<grammar[i].rhs.size();j++) {
                for(int k = 0;k<grammar[i].rhs[j].size();k++) {
                    cout<<grammar[i].rhs[j][k];
                }
                cout<<"|";
            }
            cout<<"\n";
    }
}


int isLeftRecursion(Production production) {
    for(int i = 0;i<production.rhs.size();i++) {
        if(production.rhs[i][0] == production.lhs) {
            return i;
        }
    }
    return -1;
}
void removeLeftRecursion(int productionIndex,int ruleIndex) {
    Production temp;
    vector<string> tempRule;
    for(int i = 0;i<grammar[productionIndex].rhs.size();i++) {
        if(i == ruleIndex) {
                continue;
        }
        tempRule = grammar[productionIndex].rhs[i];
        tempRule.push_back(grammar[productionIndex].lhs + "1");
        temp.rhs.push_back(tempRule);
    }
    temp.lhs = grammar[productionIndex].lhs;
    grammar.push_back(temp);

    Production temp1;
    tempRule = grammar[productionIndex].rhs[ruleIndex];
    tempRule.erase(tempRule.begin());
    tempRule.push_back(grammar[productionIndex].lhs + "1");
    temp1.rhs.push_back(tempRule);
    temp1.lhs = grammar[productionIndex].lhs + "1";
    grammar.push_back(temp1);


    grammar.erase(grammar.begin() + productionIndex);


}

int main() {

    Production p1 = {"E",{
        {"E","+","T"},
        {"T"}
    }};

    Production p2 = {"T",{
        {"T","*","F"},
        {"F"}
    }};

    Production p3 = {"F",{
        {"(","E",")"},
        {"id"}
    }};

    grammar.push_back(p1);
    grammar.push_back(p2);
    grammar.push_back(p3);


vector<vector<int>> ruleIndexes;
for(int i  =0;i<grammar.size();i++) {
    ruleIndex = -1;
    ruleIndex = isLeftRecursion(grammar[i]);
    if(ruleIndex != -1) {
        ruleIndexes.push_back()
        cout<<ruleIndex<<"\n";
        removeLeftRecursion(i,ruleIndex);

    }
}

printGrammar();
    return 0;
}