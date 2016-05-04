

#ifndef MTPROJECT_SCANNER_H
#define MTPROJECT_SCANNER_H

#include "Tokens.h"
#include <fstream>
#include <string>

class Scanner {

    std::ifstream *sourceFile;
    int lines;
public:
    Scanner(std::string);
    virtual ~Scanner();
    Token Next();
};


#endif //MTPROJECT_SCANNER_H
