#include <iostream>
#include <cstddef>

#include "abouda/Lexer/Lexer.h"

using namespace std;


Lexer::Lexer(char* filePath) 
{
    this->filePath = filePath;
    this->delimiter= " \t\v\r\f";
    this->dfaTree = new DfaTree();

    if (filePath != NULL) {
        fileStream.open(filePath, ifstream::in);

        for (auto token: kTokens)
            dfaTree->insertRoot((char*) token.first.c_str());        
    }
}

vector<Token*> Lexer::generateTokens() throw()
{
    vector<Token*> tokens;

    fileStream.clear();
    fileStream.seekg(0, ios::beg);    
    
    this->tokenX = 0;
    this->tokenY = 0;    

    while (getline(fileStream, tokenLine)) {
        tokenNode = dfaTree->getRoot();        

        for (int i=0; i<tokenLine.length(); i++) {
            tokenChar = tokenLine[i];           

            if (delimiter.find(tokenChar) != string::npos) {
                if (token.size() > 0) {                                        
                    tokens.push_back(Token::fromString(
                        token, tokenX + 1 - token.length(), tokenY));                
                    token.clear();
                }

                continue;
            }                

            if (tokenNode == dfaTree->getRoot()) {                
                if (tokenChar == '#')
                    break;

                else if (tokenChar == '"' || tokenChar == '\'') {

                    if (token.length() > 0) {
                        tokens.push_back(Token::fromString(
                            token, tokenX + 1 - token.length(), tokenY));                
                        token.clear();
                    }

                    token += tokenChar;

                    for (int j=i+1; j<tokenLine.length(); j++) {
                        token += tokenLine[j];                        

                        if (tokenLine[j] == tokenChar) {
                            break;
                        
                        } else if (j + 1 == tokenLine.length()) {                            
                            throw LexerException(tokenX, tokenY, token);
                        }
                    }

                    i += token.length();

                    tokens.push_back(Token::fromString(
                        token, tokenX + 1 - token.length(), tokenY));                
                    token.clear();

                    continue;                         
                }

            }

            if (tokenNode->isAllowed(tokenChar)) {
                if (tokenNode->hasChild(tokenChar)) {                    

                    if (tokenNode == dfaTree->getRoot()) {
                        if (token.length() > 0) {
                            tokens.push_back(Token::fromString(
                                token, tokenX + 1 - token.length(), tokenY));                
                            token.clear();

                            i--; 
                            continue;
                        }
                    }

                    token += tokenChar;
                    tokenX = i;
                    tokenNode = tokenNode->getChild(tokenChar);                                                            

                } else {                                                            
                    token += tokenChar;
                    tokenX = i;
                }
            } else {                

                if (tokenNode == dfaTree->getRoot())
                    throw LexerException(tokenX, tokenY, string(1, tokenChar));

                else {

                    if (token.size() > 0) {
                        tokens.push_back(Token::fromString(
                            token, tokenX + 1 - token.length(), tokenY));                
                        token.clear();
                    } 

                    tokenNode = dfaTree->getRoot();                
                    i--;                             
                }
            }    

            if (i + 1 == tokenLine.length()) {
                if (token.length() > 0) {
                    tokens.push_back(Token::fromString(
                        token, tokenX + 1 - token.length(), tokenY));                
                    token.clear();
                }                
            }    
        }

        tokenY++;
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