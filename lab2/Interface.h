#pragma once
#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <vector>
#include <string>
#include "Client.h"
#include "Order.h"
#include "Recipe.h"
#include "Menu.h"
#include "Product.h"
#include "PaymentSystem.h"
#include "Warehouse.h"
#include <atomic>
#include <random>
#include <chrono>
#include <thread>

using namespace std;

void printSeparator() {
    cout << "\n===============================================\n";
}

void createClient(vector<Client>& clients) {
    string name, cardNumber;
    double balance;
    cout << "������� ��� �������: ";
    cin.ignore();
    getline(cin, name);
    cout << "������� ����� �����: ";
    getline(cin, cardNumber);
    cout << "������� ������ �����: ";
    cin >> balance;

    // �������� ������� � ������
    Client client(name, cardNumber, balance);
    clients.push_back(client);
    cout << "������ " << name << " ������.\n";
}

// ������� ��� ����� ������ �������
void getRecipeData(string& name, string& description) {
    cout << "������� �������� �������: ";
    cin.ignore();
    getline(cin, name);
    cout << "������� �������� �������: ";
    getline(cin, description);
}

// ������� ��� ����������� ��������� ������������
void displayAvailableIngredients(const vector<Product>& availableIngredients, Warehouse& warehouse) {
    cout << "��������� ����������� �� ������:\n";
    for (size_t i = 0; i < availableIngredients.size(); ++i) {
        cout << i + 1 << ". " << availableIngredients[i].getName()
            << " | ���: " << availableIngredients[i].getWeight() << " �"
            << " | ����: " << availableIngredients[i].getPrice() << " ���."
            << " | ���-�� �� ������: " << warehouse.getQuantity(availableIngredients[i].getName()) << "\n";
    }
}

// ������� ��� ���������� ����������� � ������
void addIngredientToRecipe(const Product& selectedIngredient, int quantity, Recipe& newRecipe) {
    // ������������ ��������� � ��� ��� ���������� ����������
    double totalPriceForIngredient = selectedIngredient.getPrice() * quantity;
    double totalWeightForIngredient = selectedIngredient.getWeight() * quantity;

    // ������� ����� ����������� � ����������� �����������
    Product ingredientCopy = selectedIngredient;
    ingredientCopy.setWeight(totalWeightForIngredient);
    ingredientCopy.setPrice(totalPriceForIngredient);

    // ��������� ���������� � ������
    newRecipe.addIngredient(ingredientCopy);
    cout << "���������� " << selectedIngredient.getName() << " �������� � ������.\n";
}

// ������� ��� ��������� ������ �����������
void handleIngredientSelection(int ingredientChoice, const vector<Product>& availableIngredients,
    Recipe& newRecipe, Warehouse& warehouse) {
    Product selectedIngredient = availableIngredients[ingredientChoice - 1];
    int quantity;

    // ����������� ���������� ��� �������������
    cout << "������� ���������� ��� �������������: ";
    cin >> quantity;

    // �������� �� ������������� ���������� �� ������
    if (quantity > 0 && quantity <= warehouse.getQuantity(selectedIngredient.getName())) {
        // ��������� ���������� �� ������
        warehouse.deductProduct(selectedIngredient.getName(), quantity);

        // ������� ����� ����������� � ����������� ����������� � ��������� ��� � ������
        addIngredientToRecipe(selectedIngredient, quantity, newRecipe);
    }
    else {
        cout << "������������ " << selectedIngredient.getName() << " �� ������.\n";
    }
}


// �������� ������� ��� ���������� ������������ � ������
void addIngredientsToRecipe(Recipe& newRecipe, Warehouse& warehouse) {
    vector<Product> availableIngredients = warehouse.getAvailableIngredients();

    if (availableIngredients.empty()) {
        cout << "�� ������ ��� ��������� ������������.\n";
        return;
    }

    int ingredientChoice;
    while (true) {
        // �������� ��������� �����������
        displayAvailableIngredients(availableIngredients, warehouse);

        cout << "�������� ���������� ��� ���������� � ������ (��� 0 ��� ����������): ";
        cin >> ingredientChoice;

        if (ingredientChoice == 0) break;

        // ���������� ����� �����������
        if (ingredientChoice > 0 && ingredientChoice <= availableIngredients.size()) {
            handleIngredientSelection(ingredientChoice, availableIngredients, newRecipe, warehouse);
        }
        else {
            cout << "�������� ����� �����������.\n";
        }
    }
}


// ������� ��� ���������� �������
void cutRecipe(Menu& menu) {
    int cutChoice = 0;
    cout << "������ ��������� ������ �� �����? (1 - ��, 2 - ���): ";
    cin >> cutChoice;

    Recipe& recipeToCut = menu.getRecipes().back();
    while (cutChoice == 1) {
        if (recipeToCut.getPiecesCount() < recipeToCut.getMaxPieces()) {
            cout << "������ ��������� ������ \"" << recipeToCut.getName() << "\" �� �����? (1 - ��, 2 - ���): ";
            cin >> cutChoice;

            if (cutChoice == 2) break;

            if (cutChoice == 1) {
                Knife defaultKnife; // ���������� ������� ���
                recipeToCut.CutNewPiece(defaultKnife); // ��������� ����������
            }
        }
        else {
            cout << "��������� ������������ ������ ��������. ������ �� ����� ���� �������� ������.\n";
            break;
        }
    }
}

void createRecipe(Menu& menu, Warehouse& warehouse) {
    string name, description;
    int cookTime;

    // �������� ������ � �������
    getRecipeData(name, description);

    Recipe newRecipe(name, description);

    // �������� ����������� ��� �������
    addIngredientsToRecipe(newRecipe, warehouse);

    // ������������ ����� ��������� � ��� �������
    double totalWeight = newRecipe.calculateTotalWeight();
    double totalPrice = newRecipe.calculateTotalCost();

    cout << "\n������ \"" << name << "\" �������� � ����.\n"
        << "����� ��� ������������: " << totalWeight << " �\n"
        << "����� ��������� ������������: " << totalPrice << " ���.\n";

    // ��������� ������ � ����
    menu.addRecipe(newRecipe);

    // ����������, ������ �� �� ��������� ������ �� �����
    cutRecipe(menu);
}


// ������� ��� ����������� ������ ��������
void displayClients(const vector<Client>& clients) {
    cout << "\n������ ��������:\n";
    for (size_t i = 0; i < clients.size(); ++i) {
        cout << i + 1 << ". " << clients[i].getName()
            << " | ������: " << clients[i].getBankCard().getBalance() << " ������" << endl;
    }
}

// ������� ��� ������ �������
Client* selectClientFromList(vector<Client>& clients) {
    cout << "�������� ������� (������� ����� �� 1 �� " << clients.size() << "): ";
    int clientChoice;
    cin >> clientChoice;

    if (clientChoice < 1 || clientChoice > clients.size()) {
        cout << "�������� ����� �������.\n";
        return nullptr;
    }

    return &clients[clientChoice - 1];
}

// ������� ��� ����������� ���� �������
void displayClientMenu(const string& clientName) {
    cout << "\n���� ������� \"" << clientName << "\":\n";
    cout << "1. �������� �������\n";
    cout << "2. ������� ����� �����\n";
    cout << "3. �����\n";
    cout << "�������� �������: ";
}

// ������� ��� ��������� ������� �������
void viewClientOrders(Client& selectedClient) {
    if (selectedClient.getOrders().empty()) {
        cout << "� ������� ��� �������.\n";
    }
    else {
        cout << "\n������ ������� �������:\n";
        for (size_t i = 0; i < selectedClient.getOrders().size(); ++i) {
            const Order& order = selectedClient.getOrders()[i];
            cout << i + 1 << ". " << order.getName() << " - ������: " << order.getStatus() << endl;
        }
    }
}

// ������� ��� ��������� �������
void processPayment(Order& newOrder, Client& selectedClient, const string& deliveryType) {
    double orderCost = newOrder.getTotalCost();
    PaymentSystem paymentSystem(orderCost, deliveryType);
    paymentSystem.processPayment(selectedClient.getBankCard());

    if (paymentSystem.getPaymentStatus() == "���������") {
        newOrder.updateStatus("��������");
        selectedClient.addOrder(newOrder);
        cout << "����� ����� ��� ������� \"" << selectedClient.getName() << "\" ������� �������� � �������.\n";
    }
    else {
        newOrder.updateStatus("�������");
        selectedClient.addOrder(newOrder);
        cout << "������������ ������� �� ����� ��� ���������� ������.\n";
    }
}

// ������� ��� ��������� ����������
void processPickupDelivery(Order& newOrder, Client& selectedClient) {
    cout << "��������� ������: " << newOrder.getTotalCost() << " ������\n";
    processPayment(newOrder, selectedClient, "���������");
}

// ������� ��� ��������� ��������
void processDelivery(Order& newOrder, Client& selectedClient) {
    // ������ ��� �������� � ��������� ��������
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(5, 15);  // ����� �������� �� 5 �� 15 ������
    int deliveryTime = dist(gen);

    cout << "�� ������� ��������. �������� � ������� " << deliveryTime << " ������.\n";

    // �������� ��������
    for (int i = 1; i <= deliveryTime; ++i) {
        this_thread::sleep_for(chrono::seconds(1)); // �������� 1 �������
        if (i % 2 == 0) {
            cout << "�������� � ��������... " << i << " ������ ������.\n";
        }
    }

    cout << "�������� ���������.\n";

    // ������� ������ ��� ��������
    processPayment(newOrder, selectedClient, "��������");
}

// �������� ������� ��� ��������� ������ �������� � ������
void processDeliveryAndPayment(Order& newOrder, Client& selectedClient, int deliveryChoice) {
    if (deliveryChoice == 1) {
        processPickupDelivery(newOrder, selectedClient);
    }
    else if (deliveryChoice == 2) {
        processDelivery(newOrder, selectedClient);
    }
    else {
        cout << "�������� �����.\n";
    }
}

// ������� ��� ����������� ������
void displayOrderSummary(const vector<Recipe>& selectedRecipes) {
    printSeparator();
    cout << "��� ����������� �����:\n";
    double totalCost = 0;
    for (size_t i = 0; i < selectedRecipes.size(); ++i) {
        cout << selectedRecipes[i].getName() << " - ����: " << selectedRecipes[i].calculateTotalCost() << " ������\n";
        totalCost += selectedRecipes[i].calculateTotalCost();
    }
    cout << "����� ��������� ������: " << totalCost << " ������\n";
    printSeparator();
}

// ������� ��� ������ ������� ��������
int selectDeliveryMethod() {
    int deliveryChoice = 0;
    cout << "\n�������� ������ ��������:\n";
    cout << "1. ���������\n";
    cout << "2. ��������\n";
    cout << "�������� �������: ";
    cin >> deliveryChoice;

    return deliveryChoice;
}

// ������� ��� ���������� �������� � �����
void addRecipesToOrder(Menu& menu, vector<Recipe>& selectedRecipes) {
    int recipeChoice = 0;
    while (recipeChoice != -1) {
        menu.displayMenu();
        cout << "������� ����� ������� ��� ���������� � ����� (��� -1 ��� ����������): ";
        cin >> recipeChoice;

        if (recipeChoice == -1) break;

        if (recipeChoice > 0 && recipeChoice <= menu.getRecipes().size()) {
            selectedRecipes.push_back(menu.getRecipes()[recipeChoice - 1]);

            // �������� ���� ����� ����� ���������� �������
            displayOrderSummary(selectedRecipes);
        }
        else {
            cout << "�������� ����� �������.\n";
        }
    }
}

// ������� ��� �������� ������ ������
void createNewOrder(Menu& menu, Client& selectedClient) {
    vector<Recipe> selectedRecipes;

    // ��������� ������� � �����
    addRecipesToOrder(menu, selectedRecipes);

    // ��������, ������ �� ���� �� ���� ������
    if (selectedRecipes.empty()) {
        cout << "�� ������ �� ���� ������. ����� �� ����� ���� ��������.\n";
        return;
    }

    Order newOrder("����� �������", selectedRecipes, "�������");

    // �������� ������ ��������
    int deliveryChoice = selectDeliveryMethod();

    // ������������ �������� � ������
    processDeliveryAndPayment(newOrder, selectedClient, deliveryChoice);
}


// �������� ������� ��� ������ ������� � ������ � ����
void selectClient(vector<Client>& clients, Menu& menu, Warehouse& warehouse) {
    if (clients.empty()) {
        cout << "��� �������� ��� ������.\n";
        return;
    }

    // ���������� ������ ��������
    displayClients(clients);

    // �������� �������
    Client* selectedClient = selectClientFromList(clients);
    if (!selectedClient) return;

    int clientMenuChoice = 0;
    while (clientMenuChoice != 3) {
        displayClientMenu(selectedClient->getName());

        cin >> clientMenuChoice;
        switch (clientMenuChoice) {
        case 1:
            viewClientOrders(*selectedClient);
            break;

        case 2:
            createNewOrder(menu, *selectedClient);
            break;

        case 3:
            cout << "������������ � ������� ����.\n";
            break;

        default:
            cout << "�������� �����, ���������� �����.\n";
        }
    }
}


void workWithWarehouse(Warehouse& warehouse) {
    int warehouseChoice = 0;
    while (warehouseChoice != 3) {
        cout << "\n���� ������ � �������������:\n";
        cout << "1. ����������� ����������� �� ������\n";
        cout << "2. �������� ����� ����������\n";
        cout << "3. �����\n";
        cout << "�������� �������: ";
        cin >> warehouseChoice;

        switch (warehouseChoice) {
        case 1:
            warehouse.checkProductAvailability();
            break;

        case 2: {
            string ingredientName;
            double ingredientWeight, ingredientPrice;
            int ingredientQuantity;

            cout << "������� �������� �����������: ";
            cin.ignore();
            getline(cin, ingredientName);
            cout << "������� ��� ����������� (� �������): ";
            cin >> ingredientWeight;
            cout << "������� ���� �����������: ";
            cin >> ingredientPrice;
            cout << "������� ���������� �����������: ";
            cin >> ingredientQuantity;

            Product ingredient(ingredientName, ingredientWeight, ingredientPrice);
            warehouse.receiveProducts(ingredient, ingredientQuantity);
            break;
        }

        case 3:
            cout << "������������ � ������� ����.\n";
            break;

        default:
            cout << "�������� �����, ���������� �����.\n";
        }
    }
}

#endif  // INTERFACE_H
