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
        cout << "������ �������� " << processType << ". ������������: " << duration << " �����." << endl;
    }

    void checkStatus() const {
        cout << "������� " << processType << " ��������� � ���������: " << (isCompleted ? "���������" : "� ��������") << "." << endl;
    }

    void completeProcess() {
        isCompleted = true;
        cout << "������� " << processType << " ��������!" << endl;
    }

private:
    string processType;
    int duration;
    bool isCompleted = false;
};

#endif // COOKING_PROCESS_H
