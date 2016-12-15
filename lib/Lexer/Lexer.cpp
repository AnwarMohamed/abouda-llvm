#include <iostream>
#include <cstddef>

#include "abouda/Lexer/Lexer.h"

using namespace std;


Lexer::Lexer(char* filePath) 
{
    this->filePath = filePath;
    this->delimiter= " \t\v\n\r\f";
    this->dfaTree = NULL;

    if (filePath != NULL) {
        fileStream.open(filePath, ifstream::in);

        constructDfaTree();
    }
}

void Lexer::constructDfaTree()
{
    dfaTree = new DfaTree();

    for (auto key: kReserved)
        dfaTree->insertNode((char*) key);        

    dfaTree->traverseNodes();
}

vector<Token*> Lexer::generateTokens() throw()
{
    vector<Token*> tokens;

    fileStream.clear();
    fileStream.seekg(0, ios::beg);    

    DfaNode* node;    

    string tokenStr;
    bool tokenBool = false;

    while (!fileStream.eof()) {
        tokenChar = fileStream.get();
        node = dfaTree->getRoot();

        while (delimiter.find(tokenChar) == string::npos) {
            cout << "'" << (char) tokenChar << "'" << endl;

            cout << "START CHILDREN" << endl;

            for (const auto& kv : node->getChildren()) {
                cout << "key: " << kv.first << " value: " << kv.second << endl;
            }

            cout << "FINISH CHILDREN" << endl;

            cout << "START ALLOWED" << endl;
            cout << node->getAllowed() << endl;
            cout << "FINISH ALLOWED" << endl;

            if (node->isAllowed(tokenChar)) {
                if (node->hasChild(tokenChar)) {
                    cout << "IS CHILD" << endl;

                    tokenStr += tokenChar;
                    tokenBool = node->isReserved();

                    if (!fileStream.eof()) {                        
                        node = node->getChild(tokenChar);
                        tokenChar = fileStream.get();
                    }
                    
                } else {                    
                    cout << "NOT CHILD" << endl;
                    throw new LexerException();
                }
            } else {
                cout << "NOT ALLOWED" << endl;

                if (node == dfaTree->getRoot())
                    throw new LexerException();
                else 
                    break;                
            }
        }

        cout << "token : " << tokenStr << endl;

        tokenStr.clear();

        // while (!fileStream.eof() && 
        //     (delimiter.find(tokenChar) != string::npos))
        //         tokenChar = fileStream.get();

        // if (isalpha(tokenChar)) {

        // }

        // if (isdigit(tokenChar)) {

        // }

        // if (tokenChar == '#') {
        //     while (!fileStream.eof() && 
        //         (tokenChar != '\n'))
        //             tokenChar = fileStream.get();
        // }

        // cout << (char) tokenChar << endl;
    }

    return tokens;
}

bool Lexer::isReady() 
{
    return fileStream.good();
}

Lexer::~Lexer() {
    if (dfaTree != NULL)
        delete dfaTree;
}