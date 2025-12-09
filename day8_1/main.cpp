#include <fstream>
#include <vector>
#include <algorithm>
#include "../include/Utils.hpp"

struct Box {
    int64_t x = 0;
    int64_t y = 0;
    int64_t z = 0;
    int circuit = 0;
};

struct Distance {
    Box* box1 = nullptr;
    Box* box2 = nullptr;
    int64_t value = 0;
};

int main() {
    std::ifstream file("../day8_1/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint64_t result = 0;
    std::vector<Box> boxes;
    std::string line;
    int total_circuits = 0;
    while (std::getline(file, line)) {
        Box box;
        box.circuit = total_circuits;
        int64_t* digit = &box.x;
        for (int i = 0; i < line.size(); ++i) {
            char symbol = line.at(i);
            if (symbol == ',') {
                if (digit == &box.x) digit = &box.y;
                else digit = &box.z;
                continue;
            }
            utils::accumulate_digit(*digit, symbol);
        }
        boxes.push_back(box);
        ++total_circuits;
    }
    std::vector<int> circuits_sizes(total_circuits, 1);
    std::vector<Distance> distances;
    for (int i = 0; i < boxes.size() - 1; ++i) {
        for (int j = i + 1; j < boxes.size(); ++j) {
            Distance dist;
            dist.box1 = &boxes.at(i);
            dist.box2 = &boxes.at(j);
            int64_t dx = dist.box2->x - dist.box1->x;
            int64_t dy = dist.box2->y - dist.box1->y;
            int64_t dz = dist.box2->z - dist.box1->z;
            dist.value = dx*dx + dy*dy + dz*dz;
            distances.push_back(dist);
        }
    }
    std::sort(distances.begin(), distances.end(), [](const auto& left, const auto& right) {
        return left.value < right.value;
    });
    for (int i = 0; i < 1000; ++i) {
        auto& dist = distances.at(i);
        if (dist.box1->circuit == dist.box2->circuit) continue;
        int circuit = dist.box2->circuit;
        circuits_sizes.at(dist.box1->circuit) += circuits_sizes.at(circuit);
        circuits_sizes.at(circuit) = 0;
        for (auto& box : boxes) if (box.circuit == circuit) box.circuit = dist.box1->circuit;
    }
    std::sort(circuits_sizes.begin(), circuits_sizes.end(), [](const auto& left, const auto& right) {
        return left > right;
    });
    result = circuits_sizes.at(0) * circuits_sizes.at(1) * circuits_sizes.at(2);
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}