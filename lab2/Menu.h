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
        cout << "����: " << menuName << endl;
        for (const auto& recipe : recipes) {
            cout << "������: " << recipe.getName()
                << ", ��������: " << recipe.getDescription()
                << ", ������: " << recipe.getPiecesCount() << "/" << recipe.getMaxPieces() << endl;

            // ����� ������ ���� � ��������� �������
            int totalWeight = recipe.calculateTotalWeight();
            double totalCost = recipe.calculateTotalCost();
            cout << "����� ���: " << totalWeight << " �, ����� ���������: " << totalCost << " ���" << endl;

            cout << endl;
        }
    }


    vector<Recipe>& getRecipes() {
        return recipes;  // ���������� ������������� ������ �� ������ ��������
    }

private:
    string menuName;
    vector<Recipe> recipes;
};

#endif // MENU_H
