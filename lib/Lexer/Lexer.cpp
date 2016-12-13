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

vector<Token*> Lexer::generateTokens() 
{
    vector<Token*> tokens;

    fileStream.clear();
    fileStream.seekg(0, ios::beg);

    while (!fileStream.eof()) {
        tokenChar = fileStream.get();

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