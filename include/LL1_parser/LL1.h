#ifndef __LL1_H_INCLUDED__
#define __LL1_H_INCLUDED__

#include<bits/stdc++.h>
#include "parsing_table.h"
#include "grammar.h"
#include "../Lexer/lexer.h"
#include "../Token/token.h"
using namespace std;

void printStackState(stack<string> left, stack<int> right, ofstream &file) {
    file << "Stack : [ ";
    while(left.size() > 0) {
        file << left.top() << " ";
        left.pop();
    }
    file << "]\n" << "Input : [ ";
    while(right.size() > 0) {
        file << enumToStr[(Token)right.top()] << " ";
        right.pop();
    }
    file << "]\n\n";
} 

class Parser {
    bool lexErr;
    ParsingTable pTab;
    Grammar cfg;
    stack<int> tokStack;
public:
    Parser() {};
    Parser(string, string);
    void parse();
};

Parser::Parser(string codeFile, string grammarFile) {
    Lexer lexer(codeFile);
	auto p = lexer.tokenise();

    vector<pair<int, string>> tokens;
    tokens = p.first, lexErr = p.second;

    if(!lexErr) {
        tokStack.push(Token::END);
        for(int i = tokens.size()-1; i >= 0; i--) tokStack.push(tokens[i].first);
        cfg = Grammar(grammarFile);
        pTab = ParsingTable(cfg);
    }
}

void Parser::parse() {
    if(lexErr) {
        cout << "\nLexical Error found. Aborting ...\n";
    }
    else {
        ofstream file("../include/LL1_parser/p.out");
        stack<string> pStack;
        pStack.push("$");
        pStack.push(cfg.start);
        file << "\n-----------------------------------------------------------------------------\n";
        file << "Parsing Phase Output\n";
        file << "-----------------------------------------------------------------------------\n";
        printStackState(pStack, tokStack, file);
        bool error = false;
        while(true) {
            string left = pStack.top(), right = enumToStr[(Token)tokStack.top()];
            if(left == right) {
                pStack.pop();
                tokStack.pop();
            }
            else {
                if(cfg.nonTerminals.find(left) == cfg.nonTerminals.end()) {
                    error = true;
                    break;
                }
                else {
                    int index = pTab.prodIndex(left, right);
                    if(index == -1) {
                        error = true;
                        break;
                    }
                    else {
                        pStack.pop();
                        vector<string> temp = cfg.grammar[index].production;
                        for(int i = temp.size()-1; i >= 0; i--) if(temp[i] != "EPSILON") pStack.push(temp[i]);
                    }
                }
            }

            printStackState(pStack, tokStack, file);
            if(pStack.empty() == true && tokStack.empty() == true) break;
        }

        if(error) cout << "\nSntax Error found. Aborting ...\n";
        else cout << "\nParsing Complete ! Input Code Accepted (Stack opeartions can be found in p.out file ) ...\n";
    }
}

#endif