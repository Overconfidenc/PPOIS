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
        // Используем ctime_s для безопасного получения времени
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &now);
        transactionTime = buffer;
    }

    void performTransaction() const {
        cout << "Тип транзакции: " << type << ", Сумма: " << amount << ", Время: " << transactionTime;
    }

    void checkStatus() const {
        cout << "Транзакция " << type << " на сумму " << amount << " была завершена в " << transactionTime;
    }

private:
    string type;
    double amount;
    string transactionTime;
};

#endif // TRANSACTION_H
