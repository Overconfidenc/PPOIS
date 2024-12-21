#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
using namespace std;

class Product {
public:
    // Конструктор по умолчанию
    Product() : name(""), weight(0.0), price(0.0) {}

    // Пользовательский конструктор
    Product(const string& name, double weight, double price = 0.0)
        : name(name), weight(weight), price(price) {}

    void setName(const string& name) { this->name = name; }
    void setWeight(double weight) { this->weight = weight; }
    void setPrice(double price) { this->price = price; }  // Метод для установки цены

    string getName() const { return name; }
    double getWeight() const { return weight; }
    double getPrice() const { return price; }  // Метод для получения цены продукта

private:
    string name;
    double weight;
    double price;  // Цена продукта
};

#endif // PRODUCT_H
