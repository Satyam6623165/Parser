#include <iostream>
#include "../include/LL1_parser/LL1.h"

int main(int argc, char *argv[]) {
	Parser P("../samples/sample1", "../include/LL1_parser/grammar");
	P.parse();

	return 0;
}