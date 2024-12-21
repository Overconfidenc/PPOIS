#include "MarkovAlgorithm.h"  // Включите заголовочный файл с описанием класса
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

using namespace std;

void MarkovAlgorithm::addRule(const string& rule) {
    auto pos = rule.find("|-");
    if (pos != string::npos) {
        rules.emplace_back(rule.substr(0, pos), rule.substr(pos + 2), true);
    }
    else {
        auto arrowPos = rule.find("->");
        if (arrowPos != string::npos) {
            rules.emplace_back(rule.substr(0, arrowPos), rule.substr(arrowPos + 2), false);
        }
        else {
            throw invalid_argument("Неверный формат правила: " + rule);
        }
    }
}

string MarkovAlgorithm::apply(const string& input) {
    string word = input;

    while (true) {
        bool ruleApplied = false;

        for (const auto& rule : rules) {
            size_t pos = word.find(rule.from);
            if (pos != string::npos) {
                word.replace(pos, rule.from.size(), rule.to);
                ruleApplied = true;

                if (rule.isFinal) {
                    return word;
                }
                break;
            }
        }

        if (!ruleApplied) {
            break;
        }
    }

    return word;
}

bool MarkovAlgorithm::replaceWordInFile(const string& file_path, const string& targetWord, const string& replacementWord) {
    ifstream file(file_path);

    if (!file.is_open()) {
        cerr << "Error: Could not open the file \"" << file_path << "\"." << endl;
        return false;
    }

    ostringstream buffer;
    buffer << file.rdbuf();
    string fileContent = buffer.str();
    file.close();

    size_t pos = 0;
    bool found = false;

    while ((pos = fileContent.find(targetWord, pos)) != string::npos) {
        fileContent.replace(pos, targetWord.length(), replacementWord);
        pos += replacementWord.length();
        found = true;
    }

    if (found) {
        ofstream outFile(file_path);
        if (!outFile.is_open()) {
            cerr << "Error: Could not write to the file \"" << file_path << "\"." << endl;
            return false;
        }
        outFile << fileContent;
        outFile.close();
    }

    return found;
}
