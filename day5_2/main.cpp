#include <fstream>
#include <vector>
#include <algorithm>
#include "../include/Utils.hpp"

int main() {
    std::ifstream file("../day5_2/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint64_t result = 0;
    std::vector<std::pair<uint64_t, uint64_t>> ranges;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) break;
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
    std::sort(ranges.begin(), ranges.end());
    uint64_t max = 0;
    for (auto& range : ranges) {
        if (range.second <= max) continue;
        else if (range.first <= max) range.first = max + 1;
        result += range.second - range.first + 1;
        max = range.second;
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}