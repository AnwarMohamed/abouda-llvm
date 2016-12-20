#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <map>
#include <regex>

using namespace std;

static const char kRawPattern[] = "^(\".*\")|(\'.*\')$";
static const char kStringPattern[] = "[a-zA-Z_][a-zA-Z0-9]*";
static const char kIntegerPattern[] = "(\\+|-)?[[:digit:]]+";
static const char kFloatPattern[] = 
    "(([1-9][0-9]*.?[0-9]*)|(.[0-9]+))([Ee][+-]?[0-9]+)?";

static const regex kRawRegex(kRawPattern);
static const regex kStringRegex(kStringPattern);
static const regex kIntegerRegex(kIntegerPattern);
static const regex kFloatRegex(kFloatPattern);

static const map<string, string> kTokens = {
    { "fn",     "TOKEN_FUNC" },
    { "type",   "TOKEN_TYPE" },
    { "return", "TOKEN_RETURN" },
    { "for",    "TOKEN_FOR" },
    { "in",     "TOKEN_IN" },
    { "break",  "TOKEN_BREAK" },    
    { "if",     "TOKEN_IF" },
    { "else",   "TOKEN_ELSE" },
    { "match",  "TOKEN_MATCH" },
    { "true",   "TOKEN_TRUE" },
    { "false",  "TOKEN_FALSE" },    

    { "continue", "TOKEN_CONT" },

    { "{", "TOKEN_LBRACE" },
    { "}", "TOKEN_RBRACE" },
    { "(", "TOKEN_LBRACKET" },
    { ")", "TOKEN_RBRACKET" },
    { "[", "TOKEN_LSQUARE" },
    { "]", "TOKEN_RSQUARE" },

    { ">=", "TOKEN_GEQU" },
    { "<=", "TOKEN_SEQU" },
    { "==", "TOKEN_EQU" },
    { "!=", "TOKEN_NEQU" },
    { "&&", "TOKEN_AND" },
    { "||", "TOKEN_OR" },

    { ">", "TOKEN_GREATER" },
    { "<", "TOKEN_SMALLER" },
    { "=", "TOKEN_ASSIGN" },
    { "+", "TOKEN_PLUS" },
    { "-", "TOKEN_MINUS" },
    { "*", "TOKEN_ASTERISK" },
    { "/", "TOKEN_SLASH" },
    { "!", "TOKEN_NOT" },
    { "&", "TOKEN_BAND" },
    { "^", "TOKEN_BXOR" },
    { "|", "TOKEN_BOR" },

    { "=>", "TOKEN_THEN" },
    { "_", "TOKEN_UNDERSCORE" },

    { "\"", "TOKEN_DQUOTES" },
    { "'", "TOKEN_QUOTE" },    
    { ",", "TOKEN_COMMA" },    
    { "\n", "TOKEN_NEWLINE" },
};

namespace Abouda {
    namespace Lexer {

        class Token {
        public:
            Token(string lexeme, string type, int x, int y);
            ~Token();

            string getLexeme();
            string getType();
            
            int getX();
            int getY();

            static Token* fromString(string token, int x, int y);
            static bool isInteger(string token);

        private:
            string lexeme;
            string type;

            int x, y;            
        };

    }
}

#endif
