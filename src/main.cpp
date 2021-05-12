#include <iostream>
#include "../include/Lexer/lexer.h"

int main(int argc, char *argv[]) {
	// Todo: How to handle structs and unions? 
	// Todo: Write the grammar file and grammar parsing
	// Todo: Symbol table
	// Todo: First and Follow
	// Todo(Optional): Json Parse Tree

	vector<int> tokens;
	bool error;
	
	Lexer lexer("../samples/sample1");
	auto p = lexer.tokenise();
	tokens = p.first, error = p.second;

	if(!error) {
		//Todo: Proceed with Parsing
	}

	return 0;
}