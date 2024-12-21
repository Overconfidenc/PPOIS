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
#include "Interface.h"

using namespace std;

int main() {
    system("chcp 1251");

    vector<Client> clients;
    Menu menu("Меню ресторана");
    Warehouse warehouse;

    int choice = 0;

    while (choice != 6) {
        cout << "\nМеню:\n";
        cout << "1. Создать клиента\n";
        cout << "2. Создать рецепт\n";
        cout << "3. Показать меню ресторана\n";
        cout << "4. Выбрать клиента\n";
        cout << "5. Работа с ингредиентами\n";
        cout << "6. Выход\n";
        cout << "Выберите команду: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createClient(clients);
            break;

        case 2:
            createRecipe(menu, warehouse);
            break;

        case 3:
            menu.displayMenu();
            break;

        case 4:
            selectClient(clients, menu, warehouse);
            break;

        case 5:
            workWithWarehouse(warehouse);
            break;

        case 6:
            cout << "Выход.\n";
            break;

        default:
            cout << "Неверный выбор, попробуйте снова.\n";
        }
    }

    return 0;
}
