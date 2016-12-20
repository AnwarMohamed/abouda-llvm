#include <iostream>
#include <iomanip>

#include "abouda/Lexer/Token.h"
#include "abouda/Lexer/LexerException.h"

using namespace Abouda::Lexer;
using namespace std;

Token::Token(string lexeme, string type, int x, int y) 
{       
    this->lexeme = lexeme;
    this->type = type;
    this->x = x;
    this->y = y;

    if (this->lexeme == "\n")
        this->lexeme = "\\n";
}

string Token::getLexeme() { return lexeme; }
string Token::getType() { return type; }

int Token::getX() { return x; }
int Token::getY() { return y; }

Token* Token::fromString(string token, int x , int y)
{
    Token* tokenObj;

    if (kTokens.find(token) != kTokens.end())
        tokenObj = new Token(token, kTokens.at(token), x, y);
    
    else if (regex_match(token, kIntegerRegex))
        tokenObj = new Token(token, "TOKEN_INTEGER", x, y);

    else if (regex_match(token, kFloatRegex))
        tokenObj = new Token(token, "TOKEN_FLOAT", x, y);   

    else if (regex_match(token, kStringRegex))
        tokenObj = new Token(token, "TOKEN_IDENT", x, y);  

    else if (regex_match(token, kRawRegex))
        tokenObj = new Token(token, "TOKEN_STRING", x, y); 

    else 
        throw LexerException(x, y, token);

    return tokenObj;   
}

Token::~Token() {
    
}

