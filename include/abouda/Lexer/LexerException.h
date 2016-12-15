#ifndef LEXER_EXCEPTION_H
#define LEXER_EXCEPTION_H

#include <exception>

using namespace std;

namespace Abouda {          
    namespace Lexer {

		class LexerException: public exception {
		  virtual const char* what() const throw();		  
		};

	}
}

#endif