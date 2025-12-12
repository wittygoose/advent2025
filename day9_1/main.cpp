#include <fstream>
#include <vector>
#include "../include/Utils.hpp"

struct Pt {
    int64_t x = 0;
    int64_t y = 0;
};

int main() {
    std::ifstream file("../day9_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint64_t result = 0;
    std::vector<Pt> points;
    std::string line;
    while (std::getline(file, line)) {
        Pt point;
        int64_t* digit = &point.x;
        for (int i = 0; i < line.size(); ++i) {
            char symbol = line.at(i);
            if (symbol == ',') {
                digit = &point.y;
                continue;
            }
            utils::accumulate_digit(*digit, symbol);
        }
        points.push_back(std::move(point));
    }
    for (int i = 0; i < points.size(); ++i) {
        auto& p1 = points.at(i);
        for (int j = i + 1; j < points.size(); ++j) {
            auto& p2 = points.at(j);
            int64_t width = std::abs(p1.x - p2.x) + 1;
            int64_t height = std::abs(p1.y - p2.y) + 1;
            uint64_t area = width * height;
            if (area > result) result = area;
        }
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}