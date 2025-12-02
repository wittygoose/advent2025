#include <fstream>
#include "../include/Utils.hpp"

uint64_t process(uint64_t from, uint64_t to) {
    uint64_t result = 0;
    while (from <= to) {
        std::string str = std::to_string(from);
        if (str.size() % 2 == 0) {
            uint32_t half = str.size() / 2;
            bool add = true;
            for (int i = 0; i < half; ++i) {
                if (str.at(i) != str.at(i + half)) {
                    add = false;
                    break;
                }
            }
            if (add) result += from;
        }
        ++from;
    }
    return result;
}

int main() {
    std::ifstream file("../day2_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint64_t result = 0;
    uint64_t from = 0;
    uint64_t to = 0;
    std::string line;
    std::getline(file, line);
    bool swap = false;
    for (int i = 0; i < line.size(); ++i) {
        char symbol = line[i];
        if (symbol == '-') {
            swap = true;
        } else if (symbol == ',') {
            result += process(from, to);
            swap = false;
            from = to = 0;
        } else {
            utils::accumulate_digit(swap ? to : from, symbol);
        }
    }
    result += process(from, to);
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}