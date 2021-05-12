#ifndef __LEXER_H_INCLUDED__
#define __LEXER_H_INCLUDED__

#include "../FSM/FSM.h"
#include "../Token/token.h"

class Lexer {
    string sourcePath;
    FSM *identifierFA;
    FSM *floatFA;
    FSM *stringFA;
    FSM *integerFA;
    unordered_set<string> keyWords;

    bool isOperator(char);
    bool isSymbol(char);
    bool isWhiteSpace(char);
    bool isKeyWord(string);
    bool isIdentifier(string);
    bool isInteger(string);
    bool isFloat(string);
    bool isString(string);
    void analyse(string &, vector<int> &, bool &);

public:
    Lexer(string fileName);
    ~Lexer();
    pair<vector<int>, bool> tokenise();
};

bool Lexer::isOperator(char ch) {
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || ch == '<' || ch == '=') return true;
    return false;
}

bool Lexer::isSymbol(char ch) {
    if(ch == '{' || ch == '}' || ch == '(' || ch == ')' || ch == ';') return true;
    return false;
}

bool Lexer::isWhiteSpace(char ch) {
    if(ch == ' ' || ch == '\n' || ch == '\t') return true;
    return false;
}

bool Lexer::isKeyWord(string lexeme) {
    if(keyWords.find(lexeme) != keyWords.end()) return true;
    return false;
}

bool Lexer::isIdentifier(string lexeme) {
    if(identifierFA->match(lexeme)) return true;
    return false;
}

bool Lexer::isInteger(string lexeme) {
    if(lexeme.size() > 0 && integerFA->match(lexeme)) return true;
    return false;
}

bool Lexer::isFloat(string lexeme) {
    if(floatFA->match(lexeme)) return true;
    return false;
}

bool Lexer::isString(string lexeme) {
    if(lexeme.size() > 0 && stringFA->match(lexeme)) return true;
    return false;
}

Lexer::Lexer(string path) {
    sourcePath = path;
    
    identifierFA = new FSM("../include/FSM/FSM_files/identifier.txt");
    integerFA = new FSM("../include/FSM/FSM_files/integer.txt");
    floatFA = new FSM("../include/FSM/FSM_files/float.txt");
    stringFA = new FSM("../include/FSM/FSM_files/string.txt");

    keyWords = {"void", "main", "int", "float", "string", "struct", "union", "for", "return"};
}

Lexer::~Lexer() {
    delete(identifierFA);
    delete(integerFA);
    delete(floatFA);
    delete(stringFA);
}

pair<vector<int>, bool> Lexer::tokenise() {
    cout << "Lexer Output : \n";
    cout << setw(35) << left << "Lexeme" << right << "Token" << "\n\n";

    ifstream sourceFile(sourcePath);

    stringstream buffer;
    buffer << sourceFile.rdbuf();
    string source = buffer.str();

    vector<int> tokens;
    bool error = false;
    string lexeme = "";
    for(int i = 0; i < source.length(); i++) {
        char lookahead = source[i];

        if(isWhiteSpace(lookahead)) {
            analyse(lexeme, tokens, error);
        }
        else if(isOperator(lookahead)) {
            analyse(lexeme, tokens, error);
            if(lookahead == '+') {
                cout << setw(35) << left << "+" << right << "ADD\n";
                tokens.push_back(strToEnum["ADD"]);
            }
            else if(lookahead == '-') {
                cout << setw(35) << left << "-" << right << "SUB\n";
                tokens.push_back(strToEnum["SUB"]);
            }
            else if(lookahead == '*') {
                cout << setw(35) << left << "*" << right << "MUL\n";
                tokens.push_back(strToEnum["MUL"]);
            }
            else if(lookahead == '/') {
                cout << setw(35) << left << "/" << right << "DIV\n";
                tokens.push_back(strToEnum["DIV"]);
            }
            else if(lookahead == '<') {
                cout << setw(35) << left << "<" << right << "LT\n";
                tokens.push_back(strToEnum["LT"]);
            }
            else if(lookahead == '>') {
                cout << setw(35) << left << ">"  << right << "GT\n";
                tokens.push_back(strToEnum["GT"]);
            }
            else if(lookahead == '=') {
                cout << setw(35) << left << "=" << right << "EQUALS\n";
                tokens.push_back(strToEnum["EQUALS"]);
            }
        }
        else if(isSymbol(lookahead)) {
            analyse(lexeme, tokens, error);
            if(lookahead == '{') {
                // Todo : new scope (symbol table)
                cout << setw(35) << left << "{" << right << "BRACE_OPEN\n";
                tokens.push_back(strToEnum["BRACE_OPEN"]);
            }
            else if(lookahead == '}') {
                cout << setw(35) << left << "}" << right << "BRACE_CLOSE\n";
                tokens.push_back(strToEnum["BRACE_CLOSE"]);
            }
            else if(lookahead == '(') {
                cout << setw(35) << left << "(" << right << "PARAN_OPEN\n";
                tokens.push_back(strToEnum["PARAN_OPEN"]);
            }
            else if(lookahead == ')') {
                cout << setw(35) << left << ")" << right << "PARAN_CLOSE\n";
                tokens.push_back(strToEnum["PARAN_CLOSE"]);
            }
            else if(lookahead == ';') {
                cout << setw(35) << left << ";" << right << "SEMICOLON\n";
                tokens.push_back(strToEnum["SEMICOLON"]);
            }
        }
        else if(lookahead == '"') {
            lexeme += '"';
            i++;
            lookahead = source[i];

            while(i < source.length() && lookahead != '"') {
                lexeme += lookahead;
                i++;
                lookahead = source[i];
            }

            if(lookahead == '"') lexeme += '"';
        }
        else lexeme += lookahead;
    }

    if(lexeme.size() > 0) {
        analyse(lexeme, tokens, error);
    }

    return {tokens, error};
}

void Lexer::analyse(string &lexeme, vector<int> &tokens, bool &error) {
    if(isKeyWord(lexeme)) {
        cout << setw(35) << left <<  lexeme;
        transform(lexeme.begin(), lexeme.end(), lexeme.begin(), ::toupper);
        cout << right << lexeme << "\n";
        tokens.push_back(strToEnum[lexeme]);
    }
    else if(isIdentifier(lexeme)) {
        //Todo : symbol table handling
        cout << setw(35) << left << lexeme << right << "IDENTIFIER\n";
        tokens.push_back(strToEnum["IDENTIFIER"]);
    }
    else if(isString(lexeme)) {
        cout << setw(35) << left << lexeme << right << "LITERAL\n";
        tokens.push_back(strToEnum["LITERAL"]);
    }
    else if(isInteger(lexeme)) {
        cout << setw(35) << left << lexeme << right << "INTEGER_CONST\n";
        tokens.push_back(strToEnum["INTEGER_CONST"]);
    }
    else if(isFloat(lexeme)) {
        cout << setw(35) << left << lexeme << right << "FLOAT_CONST\n";
        tokens.push_back(strToEnum["FLOAT_CONST"]);
    }
    else if(lexeme.size() > 0) {
        cout << setw(35) << left << lexeme << right << "Error: Unidentified Token\n";
        error = true;
    }

    lexeme = "";
}

#endif