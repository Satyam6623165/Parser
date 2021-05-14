#ifndef __SYMTAB_H_INCLUDED__
#define __SYMTAB_H_INCLUDED__

#include<bits/stdc++.h>

using namespace std;

class Symtab {
    list<unordered_map<string, string>> list;

public:
    Symtab();
    void addNewNode();
    void addEntry(string, string);
    bool isPresent(string);
};

Symtab::Symtab() {
    list.push_back(unordered_map<string, string>());
}

void Symtab::addNewNode() {
    list.push_back(unordered_map<string,string>());
}

void Symtab::addEntry(string var, string type) {
    list.back().insert({var, type});
}

bool Symtab::isPresent(string var) {
    for(auto it = list.rbegin(); it != list.rend(); it++) {
        if((*it).find(var) != (*it).end()) {
            return true;
        }
    }
    return false;
}

#endif