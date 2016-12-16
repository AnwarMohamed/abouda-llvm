#include <iostream>
#include <cstddef>

#include "abouda/Lexer/Lexer.h"

using namespace std;


Lexer::Lexer(char* filePath) 
{
    this->filePath = filePath;
    this->delimiter= " \t\v\r\f";
    this->dfaTree = NULL;

    this->tokenX = -1;
    this->tokenY = 0;

    if (filePath != NULL) {
        fileStream.open(filePath, ifstream::in);

        constructDfaTree();
    }
}

void Lexer::constructDfaTree()
{
    dfaTree = new DfaTree();

    for (auto token: kTokens)
        dfaTree->insertNode((char*) token.first.c_str());

    dfaTree->traverseNodes();
}

vector<Token*> Lexer::generateTokens() throw()
{
    vector<Token*> tokens;

    fileStream.clear();
    fileStream.seekg(0, ios::beg);    

    DfaNode* node;    
    
    bool tokenBool = false;

    while (!fileStream.eof()) {        
        node = dfaTree->getRoot();
        getChar();

        while (delimiter.find(tokenChar) == string::npos && tokenChar != -1) {
            cout << tokenY << "\t" << tokenX << "\t'" << (char) tokenChar << "'" << endl;

            cout << "START CHILDREN" << endl;

            for (const auto& kv : node->getChildren()) {
                cout << kv.first;
            }

            cout << endl;

            cout << "FINISH CHILDREN" << endl;

            // cout << "START ALLOWED" << endl;
            // cout << node->getAllowed() << endl;
            // cout << "FINISH ALLOWED" << endl;

            if (node->isAllowed(tokenChar)) {
                if (node->hasChild(tokenChar)) {
                    cout << "IS CHILD" << endl;

                    token += tokenChar;
                    tokenBool = node->isReserved();
                
                    node = node->getChild(tokenChar);
                    getChar();
                                        
                } else {                    
                    cout << "NOT CHILD" << endl;

                    token += tokenChar;
                    tokenBool = false;

                    getChar();
                }
            } else {
                cout << "NOT ALLOWED" << endl;

                if (node == dfaTree->getRoot())
                    throw new LexerException();
                else {
                    ungetChar();
                    break;                
                }
            }
        }

        if (token.size() > 0) {            
            tokens.push_back(Token::fromString(token, tokenBool, tokenX - token.length(), tokenY));
        }

        token.clear();        

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

void Lexer::getChar() 
{
    if (!fileStream.eof()) {

        if (tokenChar == '\n') { 
            tokenX = -1; 
            tokenY++; 
        }         

        tokenChar = fileStream.get();
        tokenX++;
    }
}

void Lexer::ungetChar()
{
    tokenX--;
    fileStream.unget();
}

bool Lexer::isReady() 
{
    return fileStream.good();
}

Lexer::~Lexer() {
    if (dfaTree != NULL)
        delete dfaTree;
}