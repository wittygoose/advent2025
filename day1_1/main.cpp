#include <fstream>
#include "../include/Utils.hpp"

int main() {
    std::ifstream file("../day1_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    const int32_t full_dial = 100; 
    int32_t result = 0;
    int32_t dial = 50;
    std::string line;
    while (std::getline(file, line)) {
        int32_t digit = 0;
        int32_t sign = line[0] == 'L' ? -1 : 1;
        for (int i = 1; i < line.size(); ++i) {
            char letter = line[i];
            utils::accumulate_digit(digit, letter);
        }
        int32_t change = (digit % full_dial) * sign;
        dial += change;
        if (dial >=  full_dial) dial -= full_dial;
        else if (dial < 0) dial += full_dial;
        if (dial == 0) ++result;
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}