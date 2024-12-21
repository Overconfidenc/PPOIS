#include "MarkovAlgorithm.h"
#include <iostream>
using namespace std;

int main() {
    system("chcp 1251");
    MarkovAlgorithm algorithm;

    // Пример работы с алгоритмом Маркова
    cout << "Введите входное слово: ";
    string input_word;
    cin >> input_word;

    cout << "Введите правила (введите пустую строку для завершения):\n";
    string rule;
    cin.ignore(); // Очистка буфера после ввода слова
    while (true) {
        getline(cin, rule);
        if (rule.empty()) {
            break;
        }
        try {
            algorithm.addRule(rule);
        }
        catch (const invalid_argument& e) {
            cerr << e.what() << endl;
        }
    }

    cout << "Результат применения правил: " << algorithm.apply(input_word) << endl;

    return 0;
}
