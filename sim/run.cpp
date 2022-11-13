#include "run.hpp"

void CpuController::run() {
    // Create RAM and load a program to it
    RAM *ram = new RAM(5632);
    ram->loadProgram("./boot.bin");
    
    Bus *bus = new Bus;
    Hdd *hd0 = new Hdd("./sata0.bin");
    bus->attachDevice(2, hd0);
    
    StdDisplay *dsp = new StdDisplay(this);
    bus->attachDevice(0, dsp);

    // RUN the CPU
    CPU *cpu0 = new CPU(ram, bus);
    cpu0->run();
    
    // Debug
    cpu0->printRegisters();
    ram->flushMemory("./memory.bin");
    
    hd0->close();
    
    emit resultReady("Done!");
}

GuiController::GuiController() {
    edit = new QTextEdit;
    edit->show();
}

void GuiController::run() {
    thread = new CpuController();
    connect(thread, SIGNAL(resultReady(QString)), this, SLOT(handleResults(QString)));
    connect(thread, &CpuController::finished, thread, &QObject::deleteLater);
    thread->start();
}

void GuiController::handleResults(QString text) {
    QString text2 = edit->toPlainText();
    text2 += text;
    edit->setText(text2);
}
