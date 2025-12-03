#include <fstream>
#include "../include/Utils.hpp"

int main() {
    std::ifstream file("../day3_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint32_t result = 0;
    std::string line;
    while (std::getline(file, line)) {
        int32_t first = 0;
        int32_t second = 0;
        for (int i = 0; i < line.size(); ++i) {
            int32_t digit = utils::char_to_int(line.at(i));
            if (digit > first && i + 1 < line.size()) {
                second = 0;
                first = digit;
            } else if (digit > second) {
                second = digit;
            }
        }
        result += first * 10 + second;
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}