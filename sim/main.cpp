#include <iostream>
#include <string>
#include <cstdio>

#include "run.hpp"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    
    GuiController *cnt = new GuiController;
    cnt->run();
    
    return app.exec();
}

