#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <fstream>
#include <vector>

#include "abouda/Lexer/Token.h"
#include "abouda/Lexer/Dfa.h"
#include "abouda/Lexer/LexerException.h"

using namespace Abouda::Lexer;
using namespace std;

static const char kAllowed[] = {
    '~', '!', '%', '^', '&', '*', '(', ')', '-', '_', '=', '+', '[', ']', 
    '{', '}', ';', '\'', '"', '?', ':', '|', '<', '>', '.', '/', 'a', 'A', 
    'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F', 'g', 'G', 'h', 'H',
    'i', 'I', 'j', 'J', 'k', 'K', 'l', 'L', 'm', 'M', 'n', 'N', 'o', 'O', 
    'p', 'P', 'q', 'Q', 'r', 'R', 's', 'S', 't', 'T', 'u', 'U', 'v', 'V', 
    'w', 'W', 'x', 'X', 'y', 'Y', 'z', 'Z', '0', '1', '2', '3', '4', '5',
    '6', '7', '8', '9'
};

static const char* kAlpha = {
    "abcdefghijklmnopqrstuvwxyz" 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
};

static const char* kAlphaNum = { 
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789"
};

static const char* kAlphaNumUnder = { 
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789_"
};

static const char* kAllChars = {     
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "!@#$^&*()_+=-][{}'\";:~.,><?%%"
    "0123456789"
};

static const char* kReserved[] = {
    "fn", "type", "return",
    "for", "in", "break", "continue", "if", "else",
    "match", "_", "true", "false",
    "{", "}", "(", ")", "[", "]",
    ">=", "<=", "==", "!=", "&&", "||", ">", "<",
    "=", "!", "&", "^", "|", 
    "\"", "'"
};

namespace Abouda {          
    namespace Lexer {

        class Lexer {
        public:
            Lexer(char* filePath);
            ~Lexer();

            bool isReady();
            vector<Token*> generateTokens() throw();

        private:
            ifstream fileStream;
            char* filePath;

            string delimiter;
            string token;
            int tokenChar;

            DfaTree* dfaTree;
            void constructDfaTree();
        };  

    }
}

#endif