#pragma once
#ifndef RECIPE_H
#define RECIPE_H

#include <iostream>
#include <string>
#include <vector>
#include "Product.h"
#include "Knife.h"
using namespace std;

class Recipe {
public:
    Recipe(const string& name, const string& description)
        : name(name), description(description), piecesCount(1) {}

    void addIngredient(const Product& ingredient) {
        ingredients.push_back(ingredient);
    }

    // ����� ��� ������� ������ ���� ���� ������������
    int calculateTotalWeight() const {
        int totalWeight = 0;
        for (const auto& ingredient : ingredients) {
            totalWeight += ingredient.getWeight();  // ���������, ��� ��� � �������
        }
        return totalWeight;
    }

    double calculateTotalCost() const {
        double totalCost = 0;
        for (const auto& ingredient : ingredients) {
            totalCost += ingredient.getPrice();  // ��������� ���� ������� �����������
        }
        return totalCost;
    }

    // ����� ��� ������� ������������� ���������� ������
    int getMaxPieces() const {  // �������� const
        int totalWeight = calculateTotalWeight();
        int maxPieces = 0;

        // ������������� ceil ��� ���������� �����
        maxPieces = static_cast<int>(ceil(totalWeight / 100.0) * 2);

        return maxPieces;
    }

    // ����� ��� ���������� ������� �� �����
    void CutNewPiece(const Knife& knife) {
        int maxPieces = getMaxPieces();
        if (piecesCount < maxPieces) {
            piecesCount += 1;
            cout << "����� ����� �������. ������ ������ �������� �� " << piecesCount << " ������.\n";
        }
        else {
            cout << "������������ ���������� ������ ����������: " << maxPieces << "\n";
        }
    }

    // ����� ��� ��������� ���������� ������
    void setPiecesCount(int count) {
        piecesCount = count;
    }

    int getPiecesCount() const {
        return piecesCount;
    }

    string getName() const { return name; }
    string getDescription() const { return description; }
    const vector<Product>& getIngredients() const { return ingredients; }

private:
    string name;
    string description;
    int piecesCount;  // ���������� ������, �� ��������� 1
    vector<Product> ingredients;
};

#endif // RECIPE_H
