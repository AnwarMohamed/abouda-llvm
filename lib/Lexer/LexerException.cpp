#include "abouda/Lexer/LexerException.h"

using namespace Abouda::Lexer;

const char* LexerException::what() const throw()
{
	return "Lexer Exception";
}