#ifndef __FIRSTNFOLLOW_H_INCLUDED__
#define __FIRSTNFOLLOW_H_INCLUDED__

#include<bits/stdc++.h>
#include "grammar.h"
using namespace std;

class FirstAndFollow {
    void computeFirstOf(string);
    void computeFollowOf(string);
public:
    unordered_map<string, unordered_set<string>> firstOf;
    unordered_map<string, unordered_set<string>> followOf;
    Grammar cfg;

    FirstAndFollow(Grammar cfg) {
        this->cfg = cfg;
    }

    void first();
    void follow();
    void printFirstSets() {
        cout << "\n------------------------------------------------------------------\n";
        cout << setw(35) << left << "Non-Terminal" << right << "First Set" << "\n";
        cout << "------------------------------------------------------------------\n";
        for(auto p : firstOf) {
            cout << setw(25) << left << p.first << right << "[ ";
            for(auto x : p.second) cout << x << " ";
            cout << "]\n";
        }
    }

    void printFollowSets() {
        cout << "\n------------------------------------------------------------------\n";
        cout << setw(35) << left << "Non-Terminal" << right << "Follow Set" << "\n";
        cout << "------------------------------------------------------------------\n";
        for(auto p : followOf) {
            cout << setw(25) << left << p.first << right << "[ ";
            for(auto x : p.second) cout << x << " ";
            cout << "]\n";
        }
    }
};

void FirstAndFollow::computeFirstOf(string var) {
    if(firstOf.find(var) == firstOf.end()) {
        unordered_set<string> temp;
        for(auto production : cfg.allProductions[var]) {
            bool found = false;
            for(auto tok : production) {
                if(cfg.nonTerminals.find(tok) == cfg.nonTerminals.end()) {
                    found = true;
                    temp.insert(tok);
                    break;   
                }
                else if(tok != var){
                    computeFirstOf(tok);
                    bool isEpsPresent = false;
                    for(auto x : firstOf[tok]) {
                        if(x == "EPSILON") isEpsPresent = true;
                        else temp.insert(x);
                    }
                    if(!isEpsPresent) {
                        found = true;
                        break;
                    }
                }   
            }
            if(!found) temp.insert("EPSILON");
        }
        firstOf[var] = temp;
    }
}

void FirstAndFollow::computeFollowOf(string var) {
    for(auto rule : cfg.grammar) {
        bool found = false;
        auto it = rule.production.begin();
        for(; it != rule.production.end(); it++) {
            if(*it == var) {
                found = true;
                break;
            }
        }
        if(it != rule.production.end()) it++;

        for(; it != rule.production.end(); it++) {
            if(cfg.nonTerminals.find(*it) == cfg.nonTerminals.end()) {
                followOf[var].insert(*it);
                break;
            }
            else {
                bool epsPresent = false;
                for(auto x : firstOf[*it]) {
                    if(x == "EPSILON") {
                        epsPresent = true;
                    }
                    else followOf[var].insert(x);
                }

                if(!epsPresent) break;
            }
        }

        if(found == true && it == rule.production.end() && rule.source != var) {
            for(auto x : followOf[rule.source]) followOf[var].insert(x);
        }
    }
}

void FirstAndFollow::first() {
    for(auto var : cfg.nonTerminals) {
        computeFirstOf(var);
    }
}

void FirstAndFollow::follow() {
    for(auto x : cfg.nonTerminals) followOf[x] =  unordered_set<string>();
    followOf[cfg.start].insert("$");

    unordered_map<string, unordered_set<string>> temp = followOf;
    
    while(true) {
        for(auto var : cfg.nonTerminals) {
            computeFollowOf(var);
        }

        bool diff = false;
        for(auto p : temp) {
            if(p.second.size() < followOf[p.first].size()) {
                diff = true;
                break;
            }
        }

        if(!diff) break;
        temp = followOf;
    }
}

#endif