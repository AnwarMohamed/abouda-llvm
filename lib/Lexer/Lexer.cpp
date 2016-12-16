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
    
    bool tokenBool = false;

    while (std::getline(fileStream, tokenLine)) {
        tokenNode = dfaTree->getRoot();
        tokenY = tokenY + 1;

        for (int i=0, tokenX=0; i<tokenLine.length(); i++, tokenX++) {
            tokenChar = tokenLine[i];

            if (delimiter.find(tokenChar) != string::npos) {
                if (token.size() > 0) {
                    tokens.push_back(Token::fromString(
                        token, tokenBool, tokenX - token.length(), tokenY));                
                    token.clear();
                }

                continue;
            }    

            // cout << tokenY << "\t" << tokenX << "\t'" << (char) tokenChar << "'" << endl;

            if (tokenNode->isAllowed(tokenChar)) {
                if (tokenNode->hasChild(tokenChar)) {
                    cout << "IS CHILD" << endl;

                    token += tokenChar;
                    tokenBool = tokenNode->isReserved();
                
                    tokenNode = tokenNode->getChild(tokenChar);                                                            
                } else {                    
                    cout << "NOT CHILD" << endl;

                    token += tokenChar;
                    tokenBool = false;                    
                }
            } else {
                cout << "NOT ALLOWED" << endl;

                if (tokenNode == dfaTree->getRoot())
                    throw new LexerException();
                else {

                    if (token.size() > 0) {
                        tokens.push_back(Token::fromString(
                            token, tokenBool, tokenX - token.length(), tokenY));                
                        token.clear();
                    } 

                    tokenNode = dfaTree->getRoot();
                    tokenX--;
                    i--;                             
                }
        }        
        }
    }

    // while (!fileStream.eof()) {        
    //     tokenNode = dfaTree->getRoot();
    //     getChar();

    //     while (delimiter.find(tokenChar) == string::npos && tokenChar != -1) {
    //         cout << tokenY << "\t" << tokenX << "\t'" << (char) tokenChar << "'" << endl;

    //         cout << "START CHILDREN" << endl;

    //         for (const auto& kv : tokenNode->getChildren()) {
    //             cout << kv.first;
    //         }

    //         cout << endl;

    //         cout << "FINISH CHILDREN" << endl;

    //         // cout << "START ALLOWED" << endl;
    //         // cout << tokenNode->getAllowed() << endl;
    //         // cout << "FINISH ALLOWED" << endl;

    //         if (tokenNode->isAllowed(tokenChar)) {
    //             if (tokenNode->hasChild(tokenChar)) {
    //                 cout << "IS CHILD" << endl;

    //                 token += tokenChar;
    //                 tokenBool = tokenNode->isReserved();
                
    //                 tokenNode = tokenNode->getChild(tokenChar);
    //                 getChar();
                                        
    //             } else {                    
    //                 cout << "NOT CHILD" << endl;

    //                 token += tokenChar;
    //                 tokenBool = false;

    //                 getChar();
    //             }
    //         } else {
    //             cout << "NOT ALLOWED" << endl;

    //             if (tokenNode == dfaTree->getRoot())
    //                 throw new LexerException();
    //             else {
    //                 ungetChar();
    //                 break;                
    //             }
    //         }
    //     }

    //     if (token.size() > 0) {            
    //         tokens.push_back(Token::fromString(token, tokenBool, tokenX - token.length(), tokenY));
    //     }

    //     token.clear();
    // }

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