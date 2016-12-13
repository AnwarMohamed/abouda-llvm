#ifndef DFA_H
#define DFA_H

#include <string>
#include <cstring>
#include <vector>
#include <map>

using namespace std;

namespace Abouda {          
    namespace Lexer {

        class DfaNode
        {
        public:
            DfaNode(string value);
            ~DfaNode();

            bool hasChild(string value);
            DfaNode* getChild(string value);
            DfaNode* addChild(string value);

            map<string, DfaNode*> getChildren();
            string getValue();

            bool isAllowed(string value);
            void setAllowed(string value);

            bool isReserved();
            void setReserved(bool reserved);
        private:
            string value;
            vector<string> allowed;
            map<string, DfaNode*> children;

            bool reserved;
        };

        class DfaTree
        {
        public:
            DfaTree();
            ~DfaTree();

            void insertNode(char* node);
            void traverseNodes();

            DfaNode* getRoot();
        private:
            void traverseNode(DfaNode* node, int x, int y);

            DfaNode* rootNode;          
        };

    }
}

#endif