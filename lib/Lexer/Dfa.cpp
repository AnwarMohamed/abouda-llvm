#include <iostream>
#include "abouda/Lexer/Dfa.h"
#include "abouda/Lexer/Lexer.h"

using namespace Abouda::Lexer;
using namespace std;

DfaTree::DfaTree() 
{
    rootNode = new DfaNode("root");
    rootNode->setAllowed(kAllowed);
}

DfaNode* DfaTree::getRoot()
{
    return rootNode;
}

void DfaTree::insertNode(char* value)
{
    DfaNode* node = rootNode;
    
    int valueLen = strlen(value), valuePtr = 0;
    int valueChar = *(value + valuePtr);    

    while (valuePtr < valueLen) {
        if (node->hasChild(valueChar)) {
            node = node->getChild(valueChar);
        } else {
            node = node->addChild(valueChar);
        }        

        if (isalnum(valueChar))
            node->setAllowed(kAlphaNum);
        else if (valueLen - valuePtr  == 2)
            node->setAllowed(string(1, *(value + valuePtr + 1)));

        if (valuePtr + 1 == valueLen)
            node->setReserved(true);

        // cout << (valueLen-valuePtr+1) << ": " << value << "\t";
        // cout <<  (char) valueChar << "\t" << node->getAllowed() << endl;

        valueChar = *(value + ++valuePtr);        
    }
}

void DfaTree::traverseNodes()
{
    traverseNode(rootNode, 0, 0);
}

void DfaTree::traverseNode(DfaNode* node, int x, int y)
{
    // cout << x << ":" << y << " " << node->getValue();

    // if (node->isReserved())
    //     cout << "\t*" << endl;
    // else
    //     cout << endl;

    int offset = 0;
    for (auto child: node->getChildren())
        traverseNode(child.second, x+ offset++, y+1);
}

DfaTree::~DfaTree() 
{
    delete rootNode;    
}



DfaNode::DfaNode(string value)
{
    this->value = value;
    this->reserved = false;
}

map<string, DfaNode*> DfaNode::getChildren()
{
    return children;
}

string DfaNode::getValue()
{
    return value;
}

bool DfaNode::hasChild(int value)
{
    return children.find(string(1, value)) != children.end();
}

DfaNode* DfaNode::getChild(int value)
{
    return children.find(string(1, value))->second;
}

DfaNode* DfaNode::addChild(int value)
{
    DfaNode* node = new DfaNode(string(1, value));
    children[string(1, value)] = node;

    return node;
}

string DfaNode::getAllowed() 
{
    return allowed;
}

bool DfaNode::isAllowed(int value)
{
    return allowed.find(value) != string::npos;
}

void DfaNode::setAllowed(string allowed)
{
    this->allowed = allowed;    
}

bool DfaNode::isReserved()
{
    return reserved;
}

void DfaNode::setReserved(bool reserved)
{
    this->reserved = reserved;
}

DfaNode::~DfaNode()
{    
}