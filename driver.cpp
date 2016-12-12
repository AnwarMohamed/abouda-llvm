#include "abouda/Lexer/Lexer.h"

#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	if (argc != 2)
		return -1;

	auto lexer = new Abouda::Lexer(argv[1]);

	if (!lexer->isReady())
		return -1;
			
	auto tokens = lexer->generateTokens();

	for (auto token: tokens) {
		cout << "token: " << token->getLexeme() << " ";
		cout << "type: " << token->getType() << endl;
	}

	return 0;
}