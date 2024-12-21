#pragma once
#ifndef BANK_CARD_H
#define BANK_CARD_H

#include <iostream>
#include <string>
using namespace std;

class BankCard {
public:
    BankCard(const string& cardNumber, double balance)
        : cardNumber(cardNumber), balance(balance) {}

    void debit(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Снято с карты: " << amount << ", Новый баланс: " << balance << endl;
        }
        else {
            cout << "Недостаточно средств для проведения операции!" << endl;
        }
    }

    void credit(double amount) {
        balance += amount;
        cout << "Зачислено на карту: " << amount << ", Новый баланс: " << balance << endl;
    }

    double getBalance() const { return balance; }
    void updateCardInfo(const string& newCardNumber) {
        cardNumber = newCardNumber;
    }

private:
    string cardNumber;
    double balance;
};

#endif // BANK_CARD_H
