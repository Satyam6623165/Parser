#ifndef __PT_H_INCLUDED__
#define __PT_H_INCLUDED__

#include<bits/stdc++.h>
using namespace std;

class Ptree {
public:
    vector<string> tokenString;
    int index;

    Ptree() {}
    Ptree(string root) {
        tokenString.push_back("open");
        tokenString.push_back(root);
        tokenString.push_back("close");

        index = 0;
    }
    void insert(string src, vector<string> &tokens, unordered_set<string> &);
    void sync(string tok) {
        while(tokenString[index] != tok) index++;
        index++;
    }
    void writeJson();
    void jsonStringify(string &);
};

void Ptree::insert(string src, vector<string> &tokens, unordered_set<string> &nonTerminals) {
    sync(src);
    int pos = index;
    vector<string> temp = {"colon", "open"};
    for(int i = 0; i < tokens.size(); i++) {
        temp.push_back(tokens[i]);
        if(nonTerminals.find(tokens[i]) == nonTerminals.end()) {
            temp.push_back("colon");
            temp.push_back("EPSILON");
        }
        if(i < tokens.size()-1) temp.push_back("comma");
    }
    temp.push_back("close");
    tokenString.insert(tokenString.begin()+pos, temp.begin(), temp.end());
}

void Ptree::jsonStringify(string &str) {
    for(auto x : tokenString) {
        if(x == "open") str += "{";
        else if(x == "close") str += "}";
        else if(x == "comma") str += ",";
        else if(x == "colon") str += ":";
        else if(x == "EPSILON") str += "\"\"";
        else str += "\"" + x + "\"";
    }
}

void Ptree::writeJson() {
    string jsonString = "";
    jsonStringify(jsonString);
    ofstream file("../include/ParseTree/ptree.json");
    file << jsonString;
}

#endif