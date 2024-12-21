#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <vector>
#include "Recipe.h"
#include "PaymentSystem.h"  // Подключаем PaymentSystem
using namespace std;

class Order {
public:
    // Конструктор для создания нового заказа
    Order(const string& orderName, const vector<Recipe>& orderedDishes, const string& status = "Ожидает", bool isPickup = true)
        : orderName(orderName), orderedDishes(orderedDishes), status(status), isPickup(isPickup) {
        if (isPickup) {
            calculateTotalCost(); // Если заказ самовывозом, сразу считаем стоимость
        }
    }

    // Метод для обновления статуса заказа
    void updateStatus(const string& newStatus) {
        status = newStatus;
    }

    // Метод для добавления блюда в заказ
    void addDish(const Recipe& dish) {
        orderedDishes.push_back(dish);
    }

    // Метод для получения имени заказа
    string getName() const {
        return orderName;
    }

    // Метод для получения статуса заказа
    string getStatus() const {
        return status;
    }

    // Метод для получения списка блюд
    const vector<Recipe>& getOrderedDishes() const {
        return orderedDishes;
    }

    // Метод для отображения информации о заказе
    void displayOrderInfo() const {
        cout << "Заказ: " << orderName << " (Статус: " << status << ")\n";
        for (const auto& dish : orderedDishes) {
            cout << "Блюдо: " << dish.getName() << ", Описание: " << dish.getDescription() << "\n";
        }
    }

    double getTotalCost() const { return totalCost; }  // Для оплаты заказа

private:
    string orderName;  // Название заказа
    vector<Recipe> orderedDishes;  // Список блюд, входящих в заказ
    string status;  // Статус заказа
    bool isPickup;  // Является ли заказ самовывозом
    double totalCost;  // Общая стоимость заказа

    // Метод для вычисления стоимости заказа
    void calculateTotalCost() {
        totalCost = 0;
        for (const auto& dish : orderedDishes) {
            totalCost += dish.calculateTotalCost();
        }
    }
};

#endif // ORDER_H
