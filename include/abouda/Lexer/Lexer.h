#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <fstream>
#include <vector>

#include "abouda/Lexer/Token.h"

using namespace Abouda::Lexer;

using namespace std;

namespace Abouda {          
    namespace Lexer {
        class Lexer {
        public:
            Lexer(char* filePath);
            ~Lexer();

            bool isReady();
            vector<Token*> generateTokens();

        private:
            ifstream fileStream;
            char* filePath;

            string delimiter;
            string token;
            int tokenChar;
        };  
    }
}

#endif