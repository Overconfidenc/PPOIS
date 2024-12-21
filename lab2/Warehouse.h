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
        productsMap[product.getName()] = product; // ��������� ������ Product
        cout << "�������� " << quantity << " ������ ������: " << product.getName() << endl;
    }


    void checkProductAvailability() const {
        if (inventory.empty()) {
            cout << "����� ����.\n";
        }
        else {
            cout << "\n����������� �� ������:\n";
            for (const auto& entry : inventory) {
                const string& productName = entry.first;
                int quantity = entry.second;

                // ������� ������ Product � productsMap
                const Product& product = productsMap.at(productName);
                cout << "����������: " << productName
                    << ", ����������: " << quantity
                    << ", ����: " << product.getPrice()  // ������ �������� ���� �� productsMap
                    << " ������\n";
            }
        }
    }


    vector<Product> getAvailableIngredients() const {
        vector<Product> availableProducts;
        for (const auto& entry : inventory) {
            const string& productName = entry.first;

            // ������� ������ Product �� productsMap
            const Product& product = productsMap.at(productName); // ����� ������ Product
            availableProducts.push_back(product); // ��������� � ������ ��������� ���������
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
                    inventory.erase(it); // ������� �������, ���� ��� ������ ���
                }
            }
            else {
                cout << "������������ " << productName << " �� ������. ��������: " << it->second << "\n";
            }
        }
        else {
            cout << "������� " << productName << " ����������� �� ������.\n";
        }
    }


private:
    map<string, int> inventory;  // ��������� �������� ������ � ��� �����������
    map<string, Product> productsMap;
};

#endif // WAREHOUSE_H
