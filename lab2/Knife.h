#pragma once
#ifndef TOOL_H
#define TOOL_H

#include <iostream>
using namespace std;

class Knife {
public:
    Knife() : isUsed(false) {}

    // Метод для использования ножа
    void use() {
        isUsed = true;
    }

    // Метод для проверки состояния ножа
    void checkState() const {
        if (isUsed) {
            cout << "Нож использован." << endl;
        }
        else {
            cout << "Нож не использован." << endl;
        }
    }

private:
    bool isUsed;  // Состояние ножа (использовался или нет)
};

#endif // TOOL_H
