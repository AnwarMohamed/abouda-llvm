#ifndef PARSER_H
#define PARSER_H

#include "abouda/Parser/Parse.h"

using namespace Abouda::Parser;

namespace Abouda {          
    namespace Parser {

		class Parser {
		public:
			Parser();
			~Parser();
		
			ParseTree* generateTree();
		};

	}
}
#endif