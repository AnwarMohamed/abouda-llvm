#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using namespace std;

namespace Abouda {
	namespace Lexer {

		class Token {
		public:
			Token();
			~Token();

			virtual string getLexeme();
			virtual string getType();
		private:
			string lexeme;
			string type;
		};

	}
}

#endif