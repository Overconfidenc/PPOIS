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

    // Метод для расчета общего веса всех ингредиентов
    int calculateTotalWeight() const {
        int totalWeight = 0;
        for (const auto& ingredient : ingredients) {
            totalWeight += ingredient.getWeight();  // Убедитесь, что вес в граммах
        }
        return totalWeight;
    }

    double calculateTotalCost() const {
        double totalCost = 0;
        for (const auto& ingredient : ingredients) {
            totalCost += ingredient.getPrice();  // Суммируем цену каждого ингредиента
        }
        return totalCost;
    }

    // Метод для расчета максимального количества кусков
    int getMaxPieces() const {  // добавьте const
        int totalWeight = calculateTotalWeight();
        int maxPieces = 0;

        // Использование ceil для округления вверх
        maxPieces = static_cast<int>(ceil(totalWeight / 100.0) * 2);

        return maxPieces;
    }

    // Метод для разрезания рецепта на куски
    void CutNewPiece(const Knife& knife) {
        int maxPieces = getMaxPieces();
        if (piecesCount < maxPieces) {
            piecesCount += 1;
            cout << "Новый кусок отрезан. Сейчас рецепт разделен на " << piecesCount << " кусков.\n";
        }
        else {
            cout << "Максимальное количество кусков достигнуто: " << maxPieces << "\n";
        }
    }

    // Метод для изменения количества кусков
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
    int piecesCount;  // Количество кусков, по умолчанию 1
    vector<Product> ingredients;
};

#endif // RECIPE_H
