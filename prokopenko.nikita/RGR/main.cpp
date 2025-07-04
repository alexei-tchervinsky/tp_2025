#include "Graph.hpp"

int main() {
    Graph Russia;

    Russia.add_vertex("Saint_petersburg");
    Russia.add_vertex("Moscow");
    Russia.add_vertex("Novgorod");
    Russia.add_vertex("Belgorod");
    Russia.add_vertex("Vorkuta");

    Russia.add_edge("Saint_petersburg", "Moscow");

    try {
        Russia.add_edge("Saint_petersburg", "Moscow");
    } catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
    }

    Russia.add_edge("Moscow", "Novgorod");
    Russia.add_edge("Moscow", "Belgorod");
    Russia.add_edge("Belgorod", "Vorkuta");
    // Russia.add_edge("Vorkuta", "Saint_petersburg"); // Uncomment to test cycle

    try {
        Russia.Topsort();
    } catch (const std::exception& e) {
        std::cerr << "Error during topological sort: " << e.what() << "\n";
    }

    return 0;
}
