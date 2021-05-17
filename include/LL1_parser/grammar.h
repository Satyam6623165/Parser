#ifndef __GRAMMAR_H_INCLUDED__
#define __GRAMMAR_H_INCLUDED__

#include<bits/stdc++.h>
using namespace std;

vector<string> stringTokens(string line) {
    stringstream ss(line);
    string word;

    vector<string> res;
    while(ss >> word) res.push_back(word);

    return res;
}

class Rule {
public:
    string source;
    vector<string> production;

    Rule() {}

    Rule(string source, vector<string> production) {
        this->source = source;
        this->production = production;
    }

    void printRule() {
        cout << source << " : [ ";
        for(auto x : production) cout << x << " ";
        cout << "]\n";
    }

    bool find(string var);
};

bool Rule::find(string var) {
    bool found = false;
    for(auto x : production) {
        if(x == var) {
            found = true;
            break;
        }
    }

    return found;
}

class Grammar {
public:
    string start;
    vector<Rule> grammar;
    unordered_set<string> nonTerminals;
    unordered_map<string, vector<vector<string>>> allProductions;

    Grammar() {}

    Grammar(string path) {
        ifstream file(path);
        string line, word; 

        getline(file, start);
        getline(file, line);
        auto List = stringTokens(line);
        nonTerminals = unordered_set<string>(List.begin(), List.end());

        while(getline(file, line)) {
            if(line.size() > 0) {
                vector<string> temp = stringTokens(line);
                grammar.push_back(Rule(temp[0], vector<string>(temp.begin()+2, temp.end())));
                allProductions[temp[0]].push_back(vector<string>(temp.begin()+2, temp.end()));
            }
        }
    }

    void printGrammar() {
        cout << "\nStart symbol : " << start << "\n";
        cout << "\nNon Terminals : [ ";
        for(auto x : nonTerminals) cout << x << " ";
        cout << "]\n";
        cout << "\nGrammar : \n";
        for(auto x : grammar) x.printRule();
    }

};

#endif