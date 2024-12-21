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
    cout << "Введите имя клиента: ";
    cin.ignore();
    getline(cin, name);
    cout << "Введите номер карты: ";
    getline(cin, cardNumber);
    cout << "Введите баланс карты: ";
    cin >> balance;

    // Создание клиента с картой
    Client client(name, cardNumber, balance);
    clients.push_back(client);
    cout << "Клиент " << name << " создан.\n";
}

// Функция для ввода данных рецепта
void getRecipeData(string& name, string& description) {
    cout << "Введите название рецепта: ";
    cin.ignore();
    getline(cin, name);
    cout << "Введите описание рецепта: ";
    getline(cin, description);
}

// Функция для отображения доступных ингредиентов
void displayAvailableIngredients(const vector<Product>& availableIngredients, Warehouse& warehouse) {
    cout << "Доступные ингредиенты на складе:\n";
    for (size_t i = 0; i < availableIngredients.size(); ++i) {
        cout << i + 1 << ". " << availableIngredients[i].getName()
            << " | Вес: " << availableIngredients[i].getWeight() << " г"
            << " | Цена: " << availableIngredients[i].getPrice() << " руб."
            << " | Кол-во на складе: " << warehouse.getQuantity(availableIngredients[i].getName()) << "\n";
    }
}

// Функция для добавления ингредиента в рецепт
void addIngredientToRecipe(const Product& selectedIngredient, int quantity, Recipe& newRecipe) {
    // Подсчитываем стоимость и вес для указанного количества
    double totalPriceForIngredient = selectedIngredient.getPrice() * quantity;
    double totalWeightForIngredient = selectedIngredient.getWeight() * quantity;

    // Создаем копию ингредиента с обновленным количеством
    Product ingredientCopy = selectedIngredient;
    ingredientCopy.setWeight(totalWeightForIngredient);
    ingredientCopy.setPrice(totalPriceForIngredient);

    // Добавляем ингредиент в рецепт
    newRecipe.addIngredient(ingredientCopy);
    cout << "Ингредиент " << selectedIngredient.getName() << " добавлен в рецепт.\n";
}

// Функция для обработки выбора ингредиента
void handleIngredientSelection(int ingredientChoice, const vector<Product>& availableIngredients,
    Recipe& newRecipe, Warehouse& warehouse) {
    Product selectedIngredient = availableIngredients[ingredientChoice - 1];
    int quantity;

    // Запрашиваем количество для использования
    cout << "Введите количество для использования: ";
    cin >> quantity;

    // Проверка на достаточность количества на складе
    if (quantity > 0 && quantity <= warehouse.getQuantity(selectedIngredient.getName())) {
        // Уменьшаем количество на складе
        warehouse.deductProduct(selectedIngredient.getName(), quantity);

        // Создаем копию ингредиента с обновленным количеством и добавляем его в рецепт
        addIngredientToRecipe(selectedIngredient, quantity, newRecipe);
    }
    else {
        cout << "Недостаточно " << selectedIngredient.getName() << " на складе.\n";
    }
}


// Основная функция для добавления ингредиентов в рецепт
void addIngredientsToRecipe(Recipe& newRecipe, Warehouse& warehouse) {
    vector<Product> availableIngredients = warehouse.getAvailableIngredients();

    if (availableIngredients.empty()) {
        cout << "На складе нет доступных ингредиентов.\n";
        return;
    }

    int ingredientChoice;
    while (true) {
        // Показать доступные ингредиенты
        displayAvailableIngredients(availableIngredients, warehouse);

        cout << "Выберите ингредиент для добавления в рецепт (или 0 для завершения): ";
        cin >> ingredientChoice;

        if (ingredientChoice == 0) break;

        // Обработать выбор ингредиента
        if (ingredientChoice > 0 && ingredientChoice <= availableIngredients.size()) {
            handleIngredientSelection(ingredientChoice, availableIngredients, newRecipe, warehouse);
        }
        else {
            cout << "Неверный выбор ингредиента.\n";
        }
    }
}


// Функция для разрезания рецепта
void cutRecipe(Menu& menu) {
    int cutChoice = 0;
    cout << "Хотите разрезать рецепт на куски? (1 - Да, 2 - Нет): ";
    cin >> cutChoice;

    Recipe& recipeToCut = menu.getRecipes().back();
    while (cutChoice == 1) {
        if (recipeToCut.getPiecesCount() < recipeToCut.getMaxPieces()) {
            cout << "Хотите разрезать рецепт \"" << recipeToCut.getName() << "\" на куски? (1 - Да, 2 - Нет): ";
            cin >> cutChoice;

            if (cutChoice == 2) break;

            if (cutChoice == 1) {
                Knife defaultKnife; // Используем базовый нож
                recipeToCut.CutNewPiece(defaultKnife); // Выполняем разрезание
            }
        }
        else {
            cout << "Достигнут максимальный предел разрезов. Рецепт не может быть разрезан дальше.\n";
            break;
        }
    }
}

void createRecipe(Menu& menu, Warehouse& warehouse) {
    string name, description;
    int cookTime;

    // Получаем данные о рецепте
    getRecipeData(name, description);

    Recipe newRecipe(name, description);

    // Получаем ингредиенты для рецепта
    addIngredientsToRecipe(newRecipe, warehouse);

    // Подсчитываем общую стоимость и вес рецепта
    double totalWeight = newRecipe.calculateTotalWeight();
    double totalPrice = newRecipe.calculateTotalCost();

    cout << "\nРецепт \"" << name << "\" добавлен в меню.\n"
        << "Общий вес ингредиентов: " << totalWeight << " г\n"
        << "Общая стоимость ингредиентов: " << totalPrice << " руб.\n";

    // Добавляем рецепт в меню
    menu.addRecipe(newRecipe);

    // Спрашиваем, хотите ли вы разрезать рецепт на куски
    cutRecipe(menu);
}


// Функция для отображения списка клиентов
void displayClients(const vector<Client>& clients) {
    cout << "\nСписок клиентов:\n";
    for (size_t i = 0; i < clients.size(); ++i) {
        cout << i + 1 << ". " << clients[i].getName()
            << " | Баланс: " << clients[i].getBankCard().getBalance() << " рублей" << endl;
    }
}

// Функция для выбора клиента
Client* selectClientFromList(vector<Client>& clients) {
    cout << "Выберите клиента (введите номер от 1 до " << clients.size() << "): ";
    int clientChoice;
    cin >> clientChoice;

    if (clientChoice < 1 || clientChoice > clients.size()) {
        cout << "Неверный выбор клиента.\n";
        return nullptr;
    }

    return &clients[clientChoice - 1];
}

// Функция для отображения меню клиента
void displayClientMenu(const string& clientName) {
    cout << "\nМеню клиента \"" << clientName << "\":\n";
    cout << "1. Просмотр заказов\n";
    cout << "2. Сделать новый заказ\n";
    cout << "3. Назад\n";
    cout << "Выберите команду: ";
}

// Функция для просмотра заказов клиента
void viewClientOrders(Client& selectedClient) {
    if (selectedClient.getOrders().empty()) {
        cout << "У клиента нет заказов.\n";
    }
    else {
        cout << "\nСписок заказов клиента:\n";
        for (size_t i = 0; i < selectedClient.getOrders().size(); ++i) {
            const Order& order = selectedClient.getOrders()[i];
            cout << i + 1 << ". " << order.getName() << " - Статус: " << order.getStatus() << endl;
        }
    }
}

// Функция для обработки платежа
void processPayment(Order& newOrder, Client& selectedClient, const string& deliveryType) {
    double orderCost = newOrder.getTotalCost();
    PaymentSystem paymentSystem(orderCost, deliveryType);
    paymentSystem.processPayment(selectedClient.getBankCard());

    if (paymentSystem.getPaymentStatus() == "Завершено") {
        newOrder.updateStatus("Выполнен");
        selectedClient.addOrder(newOrder);
        cout << "Новый заказ для клиента \"" << selectedClient.getName() << "\" успешно оформлен и оплачен.\n";
    }
    else {
        newOrder.updateStatus("Отменен");
        selectedClient.addOrder(newOrder);
        cout << "Недостаточно средств на карте для оформления заказа.\n";
    }
}

// Функция для обработки самовывоза
void processPickupDelivery(Order& newOrder, Client& selectedClient) {
    cout << "Стоимость заказа: " << newOrder.getTotalCost() << " рублей\n";
    processPayment(newOrder, selectedClient, "Самовывоз");
}

// Функция для обработки доставки
void processDelivery(Order& newOrder, Client& selectedClient) {
    // Логика для доставки с случайным временем
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(5, 15);  // Время доставки от 5 до 15 секунд
    int deliveryTime = dist(gen);

    cout << "Вы выбрали доставку. Ожидайте в течение " << deliveryTime << " секунд.\n";

    // Эмуляция доставки
    for (int i = 1; i <= deliveryTime; ++i) {
        this_thread::sleep_for(chrono::seconds(1)); // Задержка 1 секунда
        if (i % 2 == 0) {
            cout << "Доставка в процессе... " << i << " секунд прошло.\n";
        }
    }

    cout << "Доставка завершена.\n";

    // Процесс оплаты для доставки
    processPayment(newOrder, selectedClient, "Доставка");
}

// Основная функция для обработки выбора доставки и оплаты
void processDeliveryAndPayment(Order& newOrder, Client& selectedClient, int deliveryChoice) {
    if (deliveryChoice == 1) {
        processPickupDelivery(newOrder, selectedClient);
    }
    else if (deliveryChoice == 2) {
        processDelivery(newOrder, selectedClient);
    }
    else {
        cout << "Неверный выбор.\n";
    }
}

// Функция для отображения заказа
void displayOrderSummary(const vector<Recipe>& selectedRecipes) {
    printSeparator();
    cout << "Ваш обновленный заказ:\n";
    double totalCost = 0;
    for (size_t i = 0; i < selectedRecipes.size(); ++i) {
        cout << selectedRecipes[i].getName() << " - Цена: " << selectedRecipes[i].calculateTotalCost() << " рублей\n";
        totalCost += selectedRecipes[i].calculateTotalCost();
    }
    cout << "Общая стоимость заказа: " << totalCost << " рублей\n";
    printSeparator();
}

// Функция для выбора способа доставки
int selectDeliveryMethod() {
    int deliveryChoice = 0;
    cout << "\nВыберите способ доставки:\n";
    cout << "1. Самовывоз\n";
    cout << "2. Доставка\n";
    cout << "Выберите команду: ";
    cin >> deliveryChoice;

    return deliveryChoice;
}

// Функция для добавления рецептов в заказ
void addRecipesToOrder(Menu& menu, vector<Recipe>& selectedRecipes) {
    int recipeChoice = 0;
    while (recipeChoice != -1) {
        menu.displayMenu();
        cout << "Введите номер рецепта для добавления в заказ (или -1 для завершения): ";
        cin >> recipeChoice;

        if (recipeChoice == -1) break;

        if (recipeChoice > 0 && recipeChoice <= menu.getRecipes().size()) {
            selectedRecipes.push_back(menu.getRecipes()[recipeChoice - 1]);

            // Показать весь заказ после добавления рецепта
            displayOrderSummary(selectedRecipes);
        }
        else {
            cout << "Неверный выбор рецепта.\n";
        }
    }
}

// Функция для создания нового заказа
void createNewOrder(Menu& menu, Client& selectedClient) {
    vector<Recipe> selectedRecipes;

    // Добавляем рецепты в заказ
    addRecipesToOrder(menu, selectedRecipes);

    // Проверка, выбран ли хотя бы один рецепт
    if (selectedRecipes.empty()) {
        cout << "Не выбран ни один рецепт. Заказ не может быть оформлен.\n";
        return;
    }

    Order newOrder("Заказ клиента", selectedRecipes, "Ожидает");

    // Выбираем способ доставки
    int deliveryChoice = selectDeliveryMethod();

    // Обрабатываем доставку и оплату
    processDeliveryAndPayment(newOrder, selectedClient, deliveryChoice);
}


// Основная функция для выбора клиента и работы с меню
void selectClient(vector<Client>& clients, Menu& menu, Warehouse& warehouse) {
    if (clients.empty()) {
        cout << "Нет клиентов для выбора.\n";
        return;
    }

    // Отображаем список клиентов
    displayClients(clients);

    // Выбираем клиента
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
            cout << "Возвращаемся в главное меню.\n";
            break;

        default:
            cout << "Неверный выбор, попробуйте снова.\n";
        }
    }
}


void workWithWarehouse(Warehouse& warehouse) {
    int warehouseChoice = 0;
    while (warehouseChoice != 3) {
        cout << "\nМеню работы с ингредиентами:\n";
        cout << "1. Просмотреть ингредиенты на складе\n";
        cout << "2. Добавить новый ингредиент\n";
        cout << "3. Назад\n";
        cout << "Выберите команду: ";
        cin >> warehouseChoice;

        switch (warehouseChoice) {
        case 1:
            warehouse.checkProductAvailability();
            break;

        case 2: {
            string ingredientName;
            double ingredientWeight, ingredientPrice;
            int ingredientQuantity;

            cout << "Введите название ингредиента: ";
            cin.ignore();
            getline(cin, ingredientName);
            cout << "Введите вес ингредиента (в граммах): ";
            cin >> ingredientWeight;
            cout << "Введите цену ингредиента: ";
            cin >> ingredientPrice;
            cout << "Введите количество ингредиента: ";
            cin >> ingredientQuantity;

            Product ingredient(ingredientName, ingredientWeight, ingredientPrice);
            warehouse.receiveProducts(ingredient, ingredientQuantity);
            break;
        }

        case 3:
            cout << "Возвращаемся в главное меню.\n";
            break;

        default:
            cout << "Неверный выбор, попробуйте снова.\n";
        }
    }
}

#endif  // INTERFACE_H
