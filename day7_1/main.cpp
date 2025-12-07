#include <fstream>
#include <vector>
#include "../include/Utils.hpp"

int main() {
    std::ifstream file("../day7_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint32_t result = 0;
    std::vector<std::string> field;
    std::string line;
    while (std::getline(file, line)) field.push_back(std::move(line));
    for (int i = 0; i < field.size(); ++i) {
        std::string& line = field.at(i);
        for (int j = 0; j < line.size(); ++j) {
            char symbol = line.at(j);
            if (symbol == 'S') {
                field.at(i + 1).at(j) = '|';
                break;
            } else if (symbol == '^') {
                if (field.at(i - 1).at(j) == '|') {
                    ++result;
                    field.at(i).at(j - 1) = '|';
                    field.at(i).at(j + 1) = '|';
                }
            } else if (i > 0 && field.at(i - 1).at(j) == '|') {
                field.at(i).at(j) = '|';
            }
        }
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}