#include <iostream>
#include <string>
#include <map>

#include "pass1.hpp"
#include "pass2.hpp"

int main(int argc, char **argv) {
    if (argc == 1) {
        std::cerr << "Error: No input file." << std::endl;
        return 1;
    }
    
    std::string input = argv[1];
    std::string output = "out";
    if (argc == 3) {
        output = argv[2];
    }
    
    Pass1 *pass1 = new Pass1(input);
    std::map<std::string, int> labels = pass1->run();
    
    Pass2 *pass2 = new Pass2(input, output);
    pass2->setMap(labels);
    pass2->run();
    delete pass2;

    return 0;
}

