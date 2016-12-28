#ifndef GRAMMAR_H
#define GRAMMAR_H

namespace Abouda {          
    namespace Parser {

		class Grammar {
		public:
			Grammar();			
			~Grammar();	

			void insertRule(string rule);
			void insertRules(string rules);
			void insertRulesFromFile(char* filePath);
		};

	}
}

#endif