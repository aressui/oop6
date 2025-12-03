#include "factory.h"
#include <iostream>
#include <random>

std::ostream &operator<<(std::ostream &os, const set_t &array) {
    for (auto &n : array) {
        n->print();
    }
    return os;
}

int main() {
    set_t array;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> coord_dis(0, 500);
    std::uniform_int_distribution<> type_dis(1, 3);
    
    std::cout << "\nGenerating 100 NPCs..." << std::endl;
    for (size_t i = 0; i < 100; ++i) {
        array.insert(factory(
            static_cast<NpcType>(type_dis(gen)),
            coord_dis(gen),
            coord_dis(gen),
            generate_name()
        ));
    }

    save(array, "npcs.txt");
    std::cout << "Saved to npcs.txt" << std::endl;
    
    array = load("npcs.txt");
    std::cout << "Loaded " << array.size() << " NPCs" << std::endl;
    
    std::cout << "\n=== Current NPCs ===" << std::endl;
    std::cout << array;

    std::cout << "\n=== Battle Mode ===" << std::endl;
    for (size_t distance = 20; (distance <= 100) && !array.empty(); distance += 20) {
        auto dead_list = fight(array, distance);
        for (auto &d : dead_list) {
            array.erase(d);
        }
        
        std::cout << "\nBattle stats ----------" << std::endl;
        std::cout << "Distance: " << distance << "m" << std::endl;
        std::cout << "Killed: " << dead_list.size() << std::endl;
        std::cout << "Survivors: " << array.size() << std::endl;
    }

    std::cout << "\n=== Final Survivors ===" << std::endl;
    if (array.empty()) {
        std::cout << "No survivors left" << std::endl;
    } else {
        std::cout << array;
        std::cout << "Total survivors: " << array.size() << std::endl;
    }
    
    return 0;
}