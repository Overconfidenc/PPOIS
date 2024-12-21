// Warehouse.h
#pragma once
#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Product.h"
using namespace std;

class Warehouse {
public:
    void receiveProducts(const Product& product, int quantity) {
        inventory[product.getName()] += quantity;
        productsMap[product.getName()] = product; // Сохраняем объект Product
        cout << "Получено " << quantity << " единиц товара: " << product.getName() << endl;
    }


    void checkProductAvailability() const {
        if (inventory.empty()) {
            cout << "Склад пуст.\n";
        }
        else {
            cout << "\nИнгредиенты на складе:\n";
            for (const auto& entry : inventory) {
                const string& productName = entry.first;
                int quantity = entry.second;

                // Находим объект Product в productsMap
                const Product& product = productsMap.at(productName);
                cout << "Ингредиент: " << productName
                    << ", Количество: " << quantity
                    << ", Цена: " << product.getPrice()  // Теперь получаем цену из productsMap
                    << " рублей\n";
            }
        }
    }


    vector<Product> getAvailableIngredients() const {
        vector<Product> availableProducts;
        for (const auto& entry : inventory) {
            const string& productName = entry.first;

            // Достаем объект Product из productsMap
            const Product& product = productsMap.at(productName); // Найти объект Product
            availableProducts.push_back(product); // Добавляем в список доступных продуктов
        }
        return availableProducts;
    }

    int getQuantity(const string& productName) const {
        auto it = inventory.find(productName);
        return (it != inventory.end()) ? it->second : 0;
    }

    void deductProduct(const string& productName, int quantity) {
        auto it = inventory.find(productName);
        if (it != inventory.end()) {
            if (it->second >= quantity) {
                it->second -= quantity;
                if (it->second == 0) {
                    inventory.erase(it); // Удаляем продукт, если его больше нет
                }
            }
            else {
                cout << "Недостаточно " << productName << " на складе. Доступно: " << it->second << "\n";
            }
        }
        else {
            cout << "Продукт " << productName << " отсутствует на складе.\n";
        }
    }


private:
    map<string, int> inventory;  // Связывает название товара с его количеством
    map<string, Product> productsMap;
};

#endif // WAREHOUSE_H
