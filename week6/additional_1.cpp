#include <iostream>
#include <vector>
#include <string>
using namespace std;



struct production {
    string lhs;
    vector<vector<string>> rhs;
};
typedef struct production Production;

void printGrammar(vector<Production>& grammar) {
        for(int i = 0;i<grammar.size();i++) {
            cout<<grammar[i].lhs<< " -> ";
            for(int j = 0;j<grammar[i].rhs.size();j++) {
                for(int k = 0;k<grammar[i].rhs[j].size();k++) {
                    cout<<grammar[i].rhs[j][k];
                }
                if(j != grammar[i].rhs.size() - 1) {
                    cout << " | ";
                }
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
void removeLeftRecursion(vector<Production>& grammar,int productionIndex,int ruleIndex) {
    Production temp;
    Production prodWithRecursion = grammar[productionIndex];
    grammar.erase(grammar.begin() + productionIndex);

    vector<string> tempRule;

    for(auto &item: prodWithRecursion.rhs) {
        auto i = &item - &prodWithRecursion.rhs[0];
         if(i == ruleIndex) {
             continue;
         }
        tempRule = item;
        tempRule.push_back(prodWithRecursion.lhs + "1");
        temp.rhs.push_back(tempRule);
    }
    temp.lhs = prodWithRecursion.lhs;
    grammar.push_back(temp);

  //  Production temp1;
    temp = {};

    tempRule.erase(tempRule.begin());
    tempRule.push_back(prodWithRecursion.lhs + "1");
    temp.rhs.push_back(tempRule);
    temp.rhs.push_back({"e"});
    temp.lhs = prodWithRecursion.lhs + "1";
    grammar.push_back(temp1);


    //grammar.erase(grammar.begin() + productionIndex);


}

int main() {

    vector <Production> grammar =
            {
                    {"E", {
                                  {"E", "+", "T"},
                                  {"T"},
                                  {"SS"}
                          }
                    },
                    {
                     "T", {
                                  {"T", "*", "F"},
                                  {"F"}
                          }
                    },
                    {
                     "F", {
                                  {"(", "E", ")"},
                                  {"id"}
                          }
                    }
            };

    //   grammar.push_back(p1);
    //   grammar.push_back(p2);
    //   grammar.push_back(p3);

    int temp;
    vector <vector<int>> rulesWithRecursion;
    for (int i = 0; i < grammar.size(); i++) {
        temp = isLeftRecursion(grammar[i]);
        if (temp != -1) {
            rulesWithRecursion.push_back({i, temp});
        }
    }
    for (auto &item: rulesWithRecursion) {
        removeLeftRecursion(grammar, item[0], item[1]);
    }

    printGrammar(grammar);
    return 0;
}