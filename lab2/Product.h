#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
using namespace std;

class Product {
public:
    // ����������� �� ���������
    Product() : name(""), weight(0.0), price(0.0) {}

    // ���������������� �����������
    Product(const string& name, double weight, double price = 0.0)
        : name(name), weight(weight), price(price) {}

    void setName(const string& name) { this->name = name; }
    void setWeight(double weight) { this->weight = weight; }
    void setPrice(double price) { this->price = price; }  // ����� ��� ��������� ����

    string getName() const { return name; }
    double getWeight() const { return weight; }
    double getPrice() const { return price; }  // ����� ��� ��������� ���� ��������

private:
    string name;
    double weight;
    double price;  // ���� ��������
};

#endif // PRODUCT_H
