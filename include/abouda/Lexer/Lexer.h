#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <fstream>
#include <vector>

#include "abouda/Tokens/BaseToken.h"

using namespace Abouda;
using namespace Abouda::Tokens;

using namespace std;

namespace Abouda {		

	class Lexer {
	public:
		Lexer(char* filePath);
		~Lexer();

		bool isReady();
		vector<BaseToken> generateTokens();

	private:
		ifstream fileStream;
		char* filePath;

   		string delimiter;
    	string token;
    	int tokenChar;
	};

}

#endif