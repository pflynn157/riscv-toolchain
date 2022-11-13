#pragma once

#include <iostream>
#include <string>
#include <cstdio>

#include "cpu.hpp"
#include "bus.hpp"
#include "hdd.hpp"
#include "display.hpp"

#include <QApplication>
#include <QMainWindow>
#include <QTextEdit>
#include <QThread>

class CpuController : public QThread {
    Q_OBJECT
    void run() override;
signals:
    void resultReady(QString text);
};

class GuiController : public QObject {
    Q_OBJECT
public:
    GuiController();
    void run();
private:
    QTextEdit *edit;
    CpuController *thread;
public slots:
    void handleResults(QString text);
};

