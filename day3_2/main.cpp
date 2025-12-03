#include <fstream>
#include "../include/Utils.hpp"

int32_t get_highest(int from, int max, int& index, std::string& line) {
    int32_t result = 0;
    for (int i = from; i <= max; ++i) {
        int32_t digit = utils::char_to_int(line.at(i));
        if (digit > result) {
            result = digit;
            index = i;
            if (digit == 9) break;
        }
    }
    return result;
}

int main() {
    std::ifstream file("../day3_2/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint64_t result = 0;
    const uint32_t size = 12;
    std::string line;
    while (std::getline(file, line)) {
        uint64_t full_digit = 0;
        int index = 0;
        for (int i = 0; i < size; ++i) {
            int digits_left = size - i;
            int max_index = index + (line.size() - index - digits_left);
            full_digit = full_digit * 10ULL + static_cast<uint64_t>(get_highest(index, max_index, index, line));
            ++index;
        }
        result += full_digit;
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}