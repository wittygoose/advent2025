#include <fstream>
#include <vector>
#include "../include/Utils.hpp"

struct Pt {
    int64_t x = 0;
    int64_t y = 0;
};

struct Side {
    Pt p1;
    Pt p2;

    inline int64_t min_x() { return std::min(p1.x, p2.x); }
    inline int64_t max_x() { return std::max(p1.x, p2.x); }
    inline int64_t min_y() { return std::min(p1.y, p2.y); }
    inline int64_t max_y() { return std::max(p1.y, p2.y); }

    bool on_side(Pt& p3) {
        if (p1.y == p2.y && p1.y == p3.y && p3.x >= min_x() && p3.x <= max_x()) return true;
        else if (p1.x == p2.x && p3.x == p1.x && p3.y >= min_y() && p3.y <= max_y()) return true;
        return false;
    }
};

bool is_inside(Pt p3, std::vector<Side>& sides) {
    bool inside = false;
    for (auto& side : sides) {
        if (side.on_side(p3)) return true;
        if (side.p1.x != side.p2.x || p3.x > side.p1.x) continue;
        if (p3.y > side.min_y() && p3.y < side.max_y()) inside = !inside;
    }
    return inside;
}

bool has_intersections(Pt& p1, Pt& p2, std::vector<Side>& sides) {
    int64_t min_x = std::min(p1.x, p2.x);
    int64_t max_x = std::max(p1.x, p2.x);
    int64_t min_y = std::min(p1.y, p2.y);
    int64_t max_y = std::max(p1.y, p2.y);
    for (auto& side : sides) {
        if (side.p1.x == side.p2.x) {
            if (side.p1.x >= max_x || side.p1.x <= min_x) continue;
            if (side.max_y() <= min_y || side.min_y() >= max_y) continue;
            return true;
        } else if (side.p1.y == side.p2.y) {
            if (side.p1.y >= max_y || side.p1.y <= min_y) continue;
            if (side.max_x() <= min_x || side.min_x() >= max_x) continue;
            return true;
        }
    }
    return false;
}

int main() {
    std::ifstream file("../day9_2/input.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open input.txt" << std::endl;
        return 1;
    }
    Performance perf;
    uint64_t result = 0;
    std::vector<Side> sides;
    std::vector<Pt> points;
    std::string line;
    int counter = 0;
    while (std::getline(file, line)) {
        Pt pt;
        int64_t* digit = &pt.x;
        for (int i = 0; i < line.size(); ++i) {
            char symbol = line.at(i);
            if (symbol == ',') {
                digit = &pt.y;
                continue;
            }
            utils::accumulate_digit(*digit, symbol);
        }
        points.push_back(pt);
        if (counter++ > 0) sides.push_back({points.at(counter - 2), pt});
    }
    sides.push_back({points.at(points.size() - 1), points.at(0)});
    for (int i = 0; i < points.size(); ++i) {
        auto& p1 = points.at(i);
        for (int j = i + 1; j < points.size(); ++j) {
            auto& p2 = points.at(j);
            int64_t width = std::abs(p1.x - p2.x) + 1;
            int64_t height = std::abs(p1.y - p2.y) + 1;
            uint64_t area = width * height;
            if (width != 1 && height != 1) {
                if (!is_inside({p1.x, p2.y}, sides)) continue;
                if (!is_inside({p2.x, p1.y}, sides)) continue;
                if (has_intersections(p1, p2, sides)) continue;
            }
            if (area > result) result = area;
        }
    }
    file.close();
    std::cout << "result equals to: " << result << std::endl;
    return 0;
}