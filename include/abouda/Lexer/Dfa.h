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

            void insertRoot(char* node);
            void traverseRoot();

            DfaNode* getRoot();
        private:
            void traverseRootR(DfaNode* node, int x, int y);

            DfaNode* rootNode;
        };

    }
}

#endif