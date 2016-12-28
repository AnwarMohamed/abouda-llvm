#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <string>

using namespace std;

namespace Abouda {          
    namespace Parser {

		class Grammar {
		public:
			Grammar();			
			~Grammar();	

			void insertRule(string rule);
			void insertRules(string rules);
			void insertRulesFromFile(char* filePath);

		private:
			
		};

	}
}

#endif