#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>

class MarkovAlgorithm {
public:
    std::string file_path;
    std::string input_word;

    struct Rule {
        std::string from;  // Левая часть правила
        std::string to;    // Правая часть правила
        bool isFinal;      // Признак заключительного правила

        Rule(const std::string& from, const std::string& to, bool isFinal)
            : from(from), to(to), isFinal(isFinal) {}
    };

    std::vector<Rule> rules;

    void addRule(const std::string& rule);

    static std::string open_file_dialog();

    void open_and_read_file(const std::string& file_path);

    std::string apply(const std::string& input);

    bool replaceWordInFile(const std::string& file_path, const std::string& targetWord, const std::string& replacementWord);
};
