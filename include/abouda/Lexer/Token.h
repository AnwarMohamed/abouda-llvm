#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <map>

using namespace std;

enum kTokensEnum {
    ANWAR
};

static const map<string, string> kTokens = {
    { "fn",     "TOKEN_FUNC_DEF" },
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

    { "continue", "TOKEN_CONTINUE" },

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
    { ".", "TOKEN_DOT" },
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

            static Token* fromString(string token, bool reserved, int x, int y);
            static bool isInteger(string token);

        private:
            string lexeme;
            string type;

            int x, y;
        };

    }
}

#endif
