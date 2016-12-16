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

            bool hasChild(int value);
            DfaNode* getChild(int value);
            DfaNode* addChild(int value);

            map<string, DfaNode*> getChildren();
            string getValue();

            bool isAllowed(int value);
            void setAllowed(string value);
            string getAllowed();

            bool isReserved();
            void setReserved(bool reserved);
        private:
            string value;
            string allowed;
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
            DfaNode* identifierNode;
        };

    }
}

#endif