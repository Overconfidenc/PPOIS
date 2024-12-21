#pragma once
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include "Recipe.h"
using namespace std;

class Menu {
public:
    Menu(const string& menuName) : menuName(menuName) {}

    void addRecipe(const Recipe& recipe) {
        recipes.push_back(recipe);
    }

    void removeRecipe(const string& recipeName) {
        for (auto it = recipes.begin(); it != recipes.end(); ++it) {
            if (it->getName() == recipeName) {
                recipes.erase(it);
                break;
            }
        }
    }

    void displayMenu() const {
        cout << "Меню: " << menuName << endl;
        for (const auto& recipe : recipes) {
            cout << "Рецепт: " << recipe.getName()
                << ", Описание: " << recipe.getDescription()
                << ", Кусков: " << recipe.getPiecesCount() << "/" << recipe.getMaxPieces() << endl;

            // Вывод общего веса и стоимости рецепта
            int totalWeight = recipe.calculateTotalWeight();
            double totalCost = recipe.calculateTotalCost();
            cout << "Общий вес: " << totalWeight << " г, Общая стоимость: " << totalCost << " руб" << endl;

            cout << endl;
        }
    }


    vector<Recipe>& getRecipes() {
        return recipes;  // Возвращаем неконстантную ссылку на список рецептов
    }

private:
    string menuName;
    vector<Recipe> recipes;
};

#endif // MENU_H
