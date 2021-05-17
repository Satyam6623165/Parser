#ifndef __PTABLE_H_INCLUDED__
#define __PTABLE_H_INCLUDED__

#include<bits/stdc++.h>
#include "first_and_follow.h"
using namespace std;

class ParsingTable {
    map<pair<string, string>, int> table;

public:
    ParsingTable() {};
    ParsingTable(Grammar);
    int prodIndex(string, string);
    void printTable();
};

ParsingTable::ParsingTable(Grammar cfg) {
    FirstAndFollow FF(cfg);
    FF.first();
    FF.follow();

    FF.printFirstSets();
    FF.printFollowSets();

    int index = 0;
    for(auto rule : FF.cfg.grammar) {
        bool endReached = true;
        for(auto x : rule.production) {
            if(FF.cfg.nonTerminals.find(x) == FF.cfg.nonTerminals.end()) {
                if(x != "EPSILON") {
                    table[{rule.source, x}] = index;
                    endReached = false;
                    break;
                }
            }
            else {
                bool epsPresent = false;
                for(auto var : FF.firstOf[x]) {
                    if(var == "EPSILON") {
                        epsPresent = true;
                    }
                    else table[{rule.source, var}] = index;
                }
                if(!epsPresent) {
                    endReached = false;
                    break;
                }
            }
        }
        if(endReached) {
            for(auto x : FF.followOf[rule.source]) table[{rule.source, x}] = index;
        }
        index++;
    }
}

int ParsingTable::prodIndex(string nonTerm, string term) {
    auto it = table.find({nonTerm, term});
    if(it == table.end()) return -1;
    
    return it->second; 
}

void ParsingTable::printTable() {
    cout << "\n----------------------------------\n";
    cout << "Parsing Table Entries\n";
    cout << "------------------------------------\n";

    for(auto p : table) {
        cout << "{ " << p.first.first << ", " << p.first.second << " } ------> " << p.second << "\n";
    }
}

#endif