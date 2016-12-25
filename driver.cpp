#include <iostream>
#include <iomanip>
#include "abouda/Lexer/Lexer.h"
#include "abouda/Parser/Parser.h"

using namespace Abouda::Lexer;
using namespace Abouda::Parser;
using namespace std;


int main(int argc, char** argv) {
    if (argc != 2)
        return -1;

    auto lexer = new Lexer(argv[1]);

    if (!lexer->isReady())
        return -1;
            
    try {
        auto tokens = lexer->generateTokens();

        // for (auto token: tokens) {
        //     cout << left << setw(10) << to_string(token->getY()+1) + ":" + to_string(token->getX()+1);
        //     cout << left << setw(20) << token->getType();
        //     cout << left << setw(20) << "'" + token->getLexeme() + "'";        
        //     cout << endl;
        // }        

        auto parser = new Parser();
        auto parseTree = parser->generateTree();

    } catch (const LexerException& e) {
        cerr << "Exception caught " << e.what() << endl;

    } catch (...) {
        cerr << "Unknown exception caught\n";
    }
    
    delete lexer;

    return 0;
}