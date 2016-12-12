#ifndef BASE_PARSER_H
#define BASE_PARSER_H

#include <string>

using namespace std;

namespace Abouda {
	namespace Tokens {

		class BaseToken {
		public:
			BaseToken();
			~BaseToken();

			virtual string getName();
			virtual string getType();
		private:
			string name;
			string type;
		};

	}
}

#endif