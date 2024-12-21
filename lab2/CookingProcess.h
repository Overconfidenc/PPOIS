#pragma once
#ifndef COOKING_PROCESS_H
#define COOKING_PROCESS_H

#include <string>
#include <iostream>
using namespace std;
class CookingProcess {
public:
    CookingProcess(const string& processType, int duration)
        : processType(processType), duration(duration) {}

    void startProcess() const {
        cout << "Запуск процесса " << processType << ". Длительность: " << duration << " минут." << endl;
    }

    void checkStatus() const {
        cout << "Процесс " << processType << " находится в состоянии: " << (isCompleted ? "завершено" : "в процессе") << "." << endl;
    }

    void completeProcess() {
        isCompleted = true;
        cout << "Процесс " << processType << " завершен!" << endl;
    }

private:
    string processType;
    int duration;
    bool isCompleted = false;
};

#endif // COOKING_PROCESS_H
