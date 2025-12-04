#include <fstream>
#include <vector>
#include "../include/Utils.hpp"

int main() {
    std::ifstream file("../day4_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint32_t result = 0;
    const uint32_t limit = 4;
    std::vector<std::pair<int, int>> directions = {{-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}};
    std::vector<std::string> field;
    std::string line;
    while (std::getline(file, line)) field.push_back(std::move(line));
    for (int i = 0; i < field.size(); ++i) {
        std::string& line = field.at(i);
        for (int j = 0; j < line.size(); ++j) {
            char symbol = line.at(j);
            if (symbol == '.') continue;
            uint32_t rolls = 0;
            for (auto& dir : directions) {
                int pos_x = j + dir.first;
                int pos_y = i + dir.second;
                if (!utils::is_valid_pos(pos_x, pos_y, field, line.size())) continue;
                if (field.at(pos_y).at(pos_x) == '@') {
                    ++rolls;
                    if (rolls > limit) break;
                }
            }
            if (rolls < limit) ++result;
        }
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}