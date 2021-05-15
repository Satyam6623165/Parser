#ifndef __SYMTAB_H_INCLUDED__
#define __SYMTAB_H_INCLUDED__

#include<bits/stdc++.h>

using namespace std;

class Symtab {
    list<unordered_map<string, string>> List;

public:
    Symtab();
    void addNewScope();
    void addEntry(string, string);
    bool isPresent(string);
    void removeScope();
};

Symtab::Symtab() {
    List.push_back(unordered_map<string, string>());
}

void Symtab::addNewScope() {
    List.push_back(unordered_map<string,string>());
}

void Symtab::addEntry(string var, string type) {
    List.back().insert({var, type});
}

bool Symtab::isPresent(string var) {
    for(auto it = List.rbegin(); it != List.rend(); it++) {
        if((*it).find(var) != (*it).end()) {
            return true;
        }
    }
    return false;
}

void Symtab::removeScope() {
    List.pop_back();
}

#endif