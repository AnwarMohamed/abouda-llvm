#include "abouda/Lexer/Token.h"

using namespace Abouda::Lexer;


Token::Token() 
{   
}

string Token::getLexeme() 
{
    return lexeme;
}

string Token::getType()
{
    return type;
}

Token::~Token() {
    
}