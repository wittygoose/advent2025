#include <fstream>
#include <vector>
#include "../include/Utils.hpp"

int main() {
    std::ifstream file("../day5_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint64_t result = 0;
    std::vector<std::pair<uint64_t, uint64_t>> ranges;
    std::string line;
    bool products_mode = false;
    while (std::getline(file, line)) {
        if (!products_mode && line.empty()) products_mode = true;
        if (products_mode) {
            uint64_t digit = 0;
            for (int i = 0; i < line.size(); ++i) utils::accumulate_digit(digit, line.at(i));
            for (std::pair<uint64_t, uint64_t>& range : ranges) {
                if (digit >= range.first && digit <= range.second) {
                    ++result;
                    break;
                }
            }
        } else {
            std::pair<uint64_t, uint64_t> range;
            bool swap = false;
            for (int i = 0; i < line.size(); ++i) {
                char symbol = line.at(i);
                if (symbol == '-') {
                    swap = true;
                    continue;
                }
                utils::accumulate_digit(swap ? range.second : range.first, symbol);
            }
            ranges.push_back(std::move(range));
        }
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}