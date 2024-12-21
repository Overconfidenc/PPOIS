#pragma once
#ifndef PAYMENT_SYSTEM_H
#define PAYMENT_SYSTEM_H

#include <iostream>
#include <string>
#include "BankCard.h"
using namespace std;

class PaymentSystem {
public:
    PaymentSystem(double amount, const string& paymentType)
        : amount(amount), paymentType(paymentType), paymentStatus("�������") {}

    void processPayment(BankCard& card) {
        if (card.getBalance() >= amount) {
            card.debit(amount);
            paymentStatus = "���������";
        }
        else {
            paymentStatus = "������������ �������";
        }
    }

    void refund(double amount, BankCard& card) {
        card.credit(amount);
        paymentStatus = "����������";
    }

    void displayPaymentInfo() const {
        cout << "������ �������: " << paymentStatus << ", �����: " << amount << ", ���: " << paymentType << endl;
    }

    string getPaymentStatus() const {
        return paymentStatus;
    }


private:
    double amount;
    string paymentType;
    string paymentStatus;
};

#endif // PAYMENT_SYSTEM_H
