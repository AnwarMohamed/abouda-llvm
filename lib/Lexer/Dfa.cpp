#include <iostream>
#include "abouda/Lexer/Dfa.h"

using namespace Abouda::Lexer;
using namespace std;

DfaTree::DfaTree() 
{
    rootNode = new DfaNode("root");
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

    // cout << valueLen << ": " << value << endl;

    while (valuePtr < valueLen) {
        if (node->hasChild(string(1, valueChar))) {
            node = node->getChild(string(1, valueChar));
        } else {
            node = node->addChild(string(1, valueChar));
        }

        if (valuePtr + 1 == valueLen)
            node->setReserved(true);

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

bool DfaNode::hasChild(string value)
{
    return children.find(value) != children.end();
}

DfaNode* DfaNode::getChild(string value)
{
    return children.find(value)->second;
}

DfaNode* DfaNode::addChild(string value)
{
    DfaNode* node = new DfaNode(value);
    children[value] = node;

    return node;
}

bool DfaNode::isAllowed(string value)
{
    return false;
}

void DfaNode::setAllowed(string value)
{

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