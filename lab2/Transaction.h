#pragma once
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
#include <chrono>
#include <ctime>
using namespace std;

class Transaction {
public:
    Transaction(const string& type, double amount)
        : type(type), amount(amount) {
        time_t now = time(0);
        // ���������� ctime_s ��� ����������� ��������� �������
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &now);
        transactionTime = buffer;
    }

    void performTransaction() const {
        cout << "��� ����������: " << type << ", �����: " << amount << ", �����: " << transactionTime;
    }

    void checkStatus() const {
        cout << "���������� " << type << " �� ����� " << amount << " ���� ��������� � " << transactionTime;
    }

private:
    string type;
    double amount;
    string transactionTime;
};

#endif // TRANSACTION_H
