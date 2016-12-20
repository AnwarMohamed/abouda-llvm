#ifndef LEXER_EXCEPTION_H
#define LEXER_EXCEPTION_H

#include <exception>
#include <string>

using namespace std;

namespace Abouda {          
    namespace Lexer {

        class LexerException: public exception {
        public:
            LexerException(int x, int y, string token);
            virtual const char* what() const throw();

          private:
            int x, y;
            string token;
        };

    }
}

#endif