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
};

class Grammar {
public:
    string start;
    vector<Rule> grammar;
    vector<string> nonTerminals;

    Grammar() {}

    Grammar(string path) {
        ifstream file(path);
        string line, word; 

        getline(file, start);
        getline(file, line);
        nonTerminals = stringTokens(line);

        while(getline(file, line)) {
            if(line.size() > 0) {
                vector<string> temp = stringTokens(line);
                grammar.push_back(Rule(temp[0], vector<string>(temp.begin()+2, temp.end())));
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