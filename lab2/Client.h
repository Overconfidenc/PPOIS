#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include "Order.h"
#include "BankCard.h"  // ���������� ����� BankCard
using namespace std;
class Client {
public:
    // ���������� �����������, ������ ��� � �����
    Client(const string& name, const string& cardNumber, double initialBalance)
        : name(name), bankCard(cardNumber, initialBalance) {}

    void createOrder(const vector<Recipe>& orderedDishes) {
        orders.push_back(Order(name, orderedDishes));  // ��������� ����� � ������
    }

    void addOrder(const Order& order) {
        orders.push_back(order);  // ��������� ����� � ������
    }

    string getName() const { return name; }

    // ����� ��� ��������� ���� ������� �������
    const vector<Order>& getOrders() const { return orders; }

    // ������ ��� ������ � ���������� ������ �������
    BankCard& getBankCard() { return bankCard; }
    const BankCard& getBankCard() const { return bankCard; }

private:
    string name;
    vector<Order> orders;  // ������ �������
    BankCard bankCard;  // ����� �������
};

#endif // CLIENT_H
