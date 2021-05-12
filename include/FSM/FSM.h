#ifndef __FSM_H_INCLUDED__
#define __FSM_H_INCLUDED__

#include<bits/stdc++.h>

using namespace std;

class FSM {
    vector<string> finalStates;
	unordered_map<string, int> alphabet;
	vector<map<string, string>> transitions;
	vector<string> transitionTokens;
	ifstream file;
	string start;
public:
    FSM(string path);
    bool match(string lexeme);
};

vector<string> stringTokeniser(string line) {
    stringstream ss(line);
    string word;
    vector<string> res;
    while(ss >> word) res.push_back(word);
    return res;
}

FSM::FSM(string path) {
    file.open(path);
    
    if(file.is_open()) {
        string line, alpha, from, to;
        vector<string> temp;

        getline(file, line);
		start = stringTokeniser(line)[0];
        getline(file, line);
        finalStates = stringTokeniser(line);
        getline(file, line);
        temp = stringTokeniser(line);
        for(int i = 0; i < (int)temp.size(); i++) alphabet[temp[i]] = i;
        transitions.resize(alphabet.size());

        while(getline(file, line)) {
            transitionTokens = stringTokeniser(line);
            from = transitionTokens[0], alpha = transitionTokens[1], to = transitionTokens[2];
            transitions[alphabet[alpha]][from] = to;
        }

        file.close();
    }
    else cout << "Error Opening File : " << path << " ...\n";
}

bool FSM::match(string lexeme) {

    bool valid = true;
    string currentState = start;

    for(auto ch : lexeme) {
        auto it = alphabet.find(string(1, ch));
        if(it != alphabet.end()) {
            int index = it->second;
            if(transitions[index].find(currentState) != transitions[index].end()) {
                currentState = transitions[index][currentState];
            }
            else {
                valid = false;
                break;
            }
        }
        else {
            valid = false;
            break;
        }
    }

    if(valid) {
        auto it = find(finalStates.begin(), finalStates.end(), currentState);
        if(it == finalStates.end()) valid = false;
    }

    return valid;
}

#endif