#pragma once
#ifndef DELIVERY_H
#define DELIVERY_H

#include <iostream>
#include <string>
#include <vector>
#include "Order.h"
using namespace std;

class Delivery {
public:
    Delivery(const string& address, const vector<Order>& orders, const string& deliveryDate)
        : address(address), orders(orders), deliveryDate(deliveryDate) {}

    void createDelivery() {
        cout << "Создание доставки по адресу " << address << " для " << orders.size() << " заказов. Дата доставки: " << deliveryDate << endl;
    }

    void trackStatus() const {
        cout << "Статус доставки: В пути к " << address << " на " << deliveryDate << endl;
    }

private:
    string address;
    vector<Order> orders;
    string deliveryDate;
};

#endif // DELIVERY_H
