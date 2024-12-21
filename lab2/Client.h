#pragma once
#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <vector>
#include "Order.h"
#include "BankCard.h"  // Подключаем класс BankCard
using namespace std;
class Client {
public:
    // Упрощенный конструктор, только имя и карта
    Client(const string& name, const string& cardNumber, double initialBalance)
        : name(name), bankCard(cardNumber, initialBalance) {}

    void createOrder(const vector<Recipe>& orderedDishes) {
        orders.push_back(Order(name, orderedDishes));  // Добавляем заказ в список
    }

    void addOrder(const Order& order) {
        orders.push_back(order);  // Добавляем заказ в список
    }

    string getName() const { return name; }

    // Метод для получения всех заказов клиента
    const vector<Order>& getOrders() const { return orders; }

    // Методы для работы с банковской картой клиента
    BankCard& getBankCard() { return bankCard; }
    const BankCard& getBankCard() const { return bankCard; }

private:
    string name;
    vector<Order> orders;  // Список заказов
    BankCard bankCard;  // Карта клиента
};

#endif // CLIENT_H
