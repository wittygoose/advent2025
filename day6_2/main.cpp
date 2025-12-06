#include <fstream>
#include <vector>
#include "../include/Utils.hpp"

int main() {
    std::ifstream file("../day6_2/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint64_t result = 0;
    std::vector<std::string> field;
    std::vector<std::vector<std::string>> columns;
    std::vector<int> highest_length_by_column;
    std::string line;
    while (std::getline(file, line)) field.push_back(std::move(line));
    for (int i = 0; i < field.size() - 1; ++i) {
        std::string& line = field.at(i);
        int column = 0;
        for (int j = 0; j < line.size(); ++j) {
            if (line.at(j) == ' ') continue;
            int start = j;
            ++j;
            while (j < line.size()) {
                if (line.at(j) == ' ') break;
                ++j;
            }
            if (column + 1 > columns.size()) {
                columns.emplace_back();
                highest_length_by_column.emplace_back();
            }
            int length = j - start;
            if (highest_length_by_column.at(column) < length) highest_length_by_column.at(column) = length;
            ++column;
        }
    }
    for (int i = 0; i < field.size() - 1; ++i) {
        std::string& line = field.at(i);
        int start = 0;
        for (int j = 0; j < highest_length_by_column.size(); ++j) {
            int length = highest_length_by_column.at(j);
            columns.at(j).emplace_back(line, start, length);
            start += length + 1;
        }
    }
    std::string& last = field.at(field.size() - 1);
    std::vector<char> operators;
    for (int i = 0; i < last.size(); ++i) {
        char symbol = last.at(i);
        if (symbol == ' ') continue;
        operators.push_back(symbol);
    }
    for (int i = 0; i < columns.size(); ++i) {
        bool multiply = operators.at(i) == '*';
        std::vector<std::string>& column = columns.at(i);
        int index = highest_length_by_column.at(i);
        uint64_t value = 0;
        bool first = true;
        while (--index >= 0) {
            uint64_t digit = 0;
            for (int j = 0; j < column.size(); ++j) {
                char symbol = column.at(j).at(index);
                if (symbol == ' ') continue;
                utils::accumulate_digit(digit, symbol);
            }
            if (first) {
                value = digit;
                first = false;
            } else {
                if (multiply) value *= digit;
                else value += digit;
            }
        }
        result += value;
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}