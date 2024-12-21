#pragma once
#ifndef TOOL_H
#define TOOL_H

#include <iostream>
using namespace std;

class Knife {
public:
    Knife() : isUsed(false) {}

    // ����� ��� ������������� ����
    void use() {
        isUsed = true;
    }

    // ����� ��� �������� ��������� ����
    void checkState() const {
        if (isUsed) {
            cout << "��� �����������." << endl;
        }
        else {
            cout << "��� �� �����������." << endl;
        }
    }

private:
    bool isUsed;  // ��������� ���� (������������� ��� ���)
};

#endif // TOOL_H
