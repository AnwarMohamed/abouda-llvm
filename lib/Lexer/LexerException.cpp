#include <sstream>
#include "abouda/Lexer/LexerException.h"

using namespace Abouda::Lexer;
using namespace std;

LexerException::LexerException(int x, int y, string token)
{
	this->x = x;
	this->y = y;
	this->token = token;
}

const char* LexerException::what() const throw()
{
	stringstream ss;
	
	ss << "Unidentified token at " << (y+1) << ":" << (x+1);
	ss << "\t'" << token << "'" << endl;

	return ss.str().c_str();
}