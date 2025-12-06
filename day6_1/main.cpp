#include <fstream>
#include <vector>
#include "../include/Utils.hpp"

int main() {
    std::ifstream file("../day6_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint64_t result = 0;
    std::vector<std::string> field;
    std::vector<std::vector<uint64_t>> input;
    std::string line;
    while (std::getline(file, line)) field.push_back(std::move(line));
    for (int i = 0; i < field.size() - 1; ++i) {
        std::string& line = field.at(i);
        std::vector<uint64_t> digits;
        uint64_t digit = 0;
        bool accumulate = false;
        for (int j = 0; j < line.size(); ++j) {
            char symbol = line.at(j);
            if (symbol == ' ') {
                if (accumulate) {
                    digits.push_back(digit);
                    digit = 0;
                    accumulate = false;
                }
                continue;
            } else {
                accumulate = true;
                utils::accumulate_digit(digit, symbol);
                if (j + 1 == line.size()) digits.push_back(digit);
            }
        }
        input.push_back(std::move(digits));
    }
    std::string& last = field.at(field.size() - 1);
    std::vector<char> operators;
    for (int i = 0; i < last.size(); ++i) {
        char symbol = last.at(i);
        if (symbol == ' ') continue;
        operators.push_back(symbol);
    }
    int width = input.at(0).size();
    int height = input.size();
    for (int i = 0; i < width; ++i) {
        bool multiply = operators.at(i) == '*';
        uint64_t digit = input.at(0).at(i);
        for (int j = 1; j < height; ++j) {
            if (multiply) digit *= input.at(j).at(i);
            else digit += input.at(j).at(i);
        }
        result += digit;
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}