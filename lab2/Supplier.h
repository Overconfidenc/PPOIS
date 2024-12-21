#ifndef SUPPLIER_H
#define SUPPLIER_H

#include <iostream>
#include <string>
#include <vector>
#include "Product.h"
using namespace std;

class Supplier {
public:
    Supplier(const string& name, const string& contactInfo)
        : name(name), contactInfo(contactInfo) {}

    void deliverProducts(const vector<Product>& products) {
        suppliedProducts.insert(suppliedProducts.end(), products.begin(), products.end());
        cout << "Продукты доставлены " << name << endl;
    }

    void checkQuality(const Product& product) const {
        cout << "Проверка качества " << product.getName() << "..." << endl;
        // Здесь можно добавить логику проверки качества
        cout << "Проверка качества прошла успешно!" << endl;
    }

    string getName() const { return name; }
    string getContactInfo() const { return contactInfo; }

private:
    string name;
    string contactInfo;
    vector<Product> suppliedProducts;
};

#endif // SUPPLIER_H
