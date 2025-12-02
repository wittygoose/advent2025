#include <fstream>
#include "../include/Utils.hpp"

uint64_t process(uint64_t from, uint64_t to) {
    uint64_t result = 0;
    while (from <= to) {
        std::string str = std::to_string(from);
        if (str.size() > 1) {
            uint32_t step = 1;
            while (step * 2 <= str.size()) {
                bool add = false;
                if (str.size() % step == 0) {
                    add = true;
                    for (int i = 0; i < step; ++i) {
                        char symbol = str.at(i);
                        for (int j = i + step; j < str.size(); j += step) {
                            if (str.at(j) != symbol) {
                                add = false;
                                break;
                            }
                        }
                        if (!add) break;
                    }
                }
                if (add) {
                    result += from;
                    break;
                }
                ++step;
            }
        }
        ++from;
    }
    return result;
}

int main() {
    std::ifstream file("../day2_2/input.txt");
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