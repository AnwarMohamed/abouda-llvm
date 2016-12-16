#include "abouda/Lexer/Token.h"

using namespace Abouda::Lexer;

Token::Token(string lexeme, string type, int x, int y) 
{       
    this->lexeme = lexeme;
    this->type = type;
    this->x = x;
    this->y = y;

    if (this->lexeme == "\n")
        this->lexeme = "\\n";
}

string Token::getLexeme() 
{
    return lexeme;
}

string Token::getType()
{
    return type;
}

bool Token::isInteger(string token)
{
    if (token.empty() || 
        ((!isdigit(token[0])) && 
            (token[0] != '-') && 
            (token[0] != '+'))) 
        return false ;

    char* p;
    strtol(token.c_str(), &p, 10) ;

    return (*p == 0) ;
}

int Token::getX() { return x; }
int Token::getY() { return y; }

Token* Token::fromString(string token, bool reserved, int x , int y)
{
    if (kTokens.find(token) != kTokens.end())
        return new Token(token, kTokens.at(token), x, y);
    
    else if (isInteger(token))
        return new Token(token, "TOKEN_INTEGER", x, y);
    else 
        return new Token(token, "", x, y);
}

Token::~Token() {
    
}

