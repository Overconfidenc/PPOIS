#pragma once
#ifndef CHEF_H
#define CHEF_H

#include <iostream>
#include <string>
using namespace std;

class Chef {
public:
    Chef(const string& ���, int ����, const string& ��������������)
        : ���(���), ����(����), ��������������(��������������) {}

    void ��������() {
        cout << ��� << " ������� � " << ���� << " ������ ������." << endl;
    }

    void ����������(const string& ����������) {
        �������������� = ����������;
        cout << ��� << " ������ ����� �����: " << �������������� << endl;
    }

    void ����������������() {
        ���� += 1;
        cout << ��� << " ������� ���� ������! ������ � ���� " << ���� << " ��� �����." << endl;
    }

private:
    string ���;
    int ����;
    string ��������������;
};

#endif // CHEF_H
