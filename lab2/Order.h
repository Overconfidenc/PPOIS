#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <vector>
#include "Recipe.h"
#include "PaymentSystem.h"  // ���������� PaymentSystem
using namespace std;

class Order {
public:
    // ����������� ��� �������� ������ ������
    Order(const string& orderName, const vector<Recipe>& orderedDishes, const string& status = "�������", bool isPickup = true)
        : orderName(orderName), orderedDishes(orderedDishes), status(status), isPickup(isPickup) {
        if (isPickup) {
            calculateTotalCost(); // ���� ����� �����������, ����� ������� ���������
        }
    }

    // ����� ��� ���������� ������� ������
    void updateStatus(const string& newStatus) {
        status = newStatus;
    }

    // ����� ��� ���������� ����� � �����
    void addDish(const Recipe& dish) {
        orderedDishes.push_back(dish);
    }

    // ����� ��� ��������� ����� ������
    string getName() const {
        return orderName;
    }

    // ����� ��� ��������� ������� ������
    string getStatus() const {
        return status;
    }

    // ����� ��� ��������� ������ ����
    const vector<Recipe>& getOrderedDishes() const {
        return orderedDishes;
    }

    // ����� ��� ����������� ���������� � ������
    void displayOrderInfo() const {
        cout << "�����: " << orderName << " (������: " << status << ")\n";
        for (const auto& dish : orderedDishes) {
            cout << "�����: " << dish.getName() << ", ��������: " << dish.getDescription() << "\n";
        }
    }

    double getTotalCost() const { return totalCost; }  // ��� ������ ������

private:
    string orderName;  // �������� ������
    vector<Recipe> orderedDishes;  // ������ ����, �������� � �����
    string status;  // ������ ������
    bool isPickup;  // �������� �� ����� �����������
    double totalCost;  // ����� ��������� ������

    // ����� ��� ���������� ��������� ������
    void calculateTotalCost() {
        totalCost = 0;
        for (const auto& dish : orderedDishes) {
            totalCost += dish.calculateTotalCost();
        }
    }
};

#endif // ORDER_H
