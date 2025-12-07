#include <fstream>
#include <vector>
#include "../include/Utils.hpp"

int main() {
    std::ifstream file("../day7_2/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint64_t result = 0;
    std::vector<std::string> field;
    std::string line;
    while (std::getline(file, line)) field.push_back(std::move(line));
    std::string& first_line = field.at(0);
    std::vector<uint64_t> current(first_line.size(), 0);
    for (int i = 0; i < first_line.size(); ++i) {
        if (first_line.at(i) == 'S') {
            current.at(i) = 1;
            break;
        }
    }
    for (int i = 1; i < field.size(); ++i) {
        std::string& line = field.at(i);
        std::vector<uint64_t> after = current;
        for (int j = 0; j < line.size(); ++j) {
            if (line.at(j) != '^') continue;
            uint64_t beam = current.at(j);
            if (beam == 0) continue;
            if (j > 0) after.at(j - 1) += beam;
            if (j + 1 < line.size()) after.at(j + 1) += beam;
            after.at(j) -= beam;
        }
        current.swap(after);
    }
    for (auto& v : current) result += v;
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}