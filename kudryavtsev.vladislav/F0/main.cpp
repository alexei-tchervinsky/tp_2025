#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits.h>
#include "Graph.hpp"

int main() {
{
    Graph g;
    std::cout << "Test №1 - graph empty?\n";

    if(!g.empty()){
        std::cout << "NO!\n";
    }
    else{
        std::cout << "YES!\n";
    }

    std::cout << "Test №2 - adding and checking on nodes\n";
    g.add_node(1);
    g.add_node(2);
    g.add_node(3);

    std::cout << "Added nodes 1 2 3, are they okay?\n";

    if(g.has_node(1) and g.has_node(2) and g.has_node(3)){
        std::cout << "YES!\n";
    }
    else{
        std::cout << "NO!\n";
    }

    std::cout << "Test №3 - adding and checking on edges\n";
    g.add_edge(1, 2, 5.0);
    g.add_edge(2, 3, 2.0);

    std::cout << "Added edges 1-2 and 2-3, witch weights are 5.0 and 2.0, are they okay?\n";

    if(g.has_edge(1, 2) and g.has_edge(2, 3)){
        std::cout << "YES!\n";
    }
    else{
        std::cout << "NO!\n";
    }

    std::cout << "Test №4 - deleted node 2, did it work?\n";
    g.remove_node(2);

    if(!g.has_node(2)){
        std::cout << "YES!\n";
    }
    else{
        std::cout << "NO!\n";
    }

    std::cout << "Test №5 - deleted node 2 again, did it work?\n";

    try {
        g.remove_node(2);
        std::cout << "NO, than was unexpected...\n" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "NO, as expected\n" << std::endl;
    }

    std::cout << "Test №6 - added edge between empty nodes, did it work?\n";

    try{
        g.add_edge(42, 99, 1.0);
        std::cout << "NO, than was unexpected...\n" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "NO, as expected\n" << std::endl;
    }

    std::cout << "Test №7 - deleted empty edge, did it work?\n";

    try {
        g.remove_edge(1, 3);
        std::cout << "FAIL" << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "OK" << std::endl;
    }
}
    std::cout << "===============MAIN TESTS===============\n";
    std::cout << "Test №8 - testing Bellman-Ford (no negative cycles)\n";
    Graph g;

    g.add_node(1); //Polytech
    g.add_node(2); //Electro
    g.add_node(3); //Center
    g.add_node(4); //Avia
    g.add_node(5); //Culture
    g.add_node(6); //Ship
    g.add_node(7); //Comm

    g.add_edge(1, 2, 6.0); //Poly->Electro
    g.add_edge(1, 3, 11.0); //Poly->Center
    g.add_edge(1, 4, 12.0); //Poly->Avia
    g.add_edge(1, 5, 10.0); //Poly->Culture
    g.add_edge(1, 6, 33.0); //Poly->Ship
    g.add_edge(1, 7, 26.0); //Poly->Comm
    g.add_edge(2, 3, 5.0); //Electro->Center
    g.add_edge(2, 4, 8.0); //Electro->Avia
    g.add_edge(2, 5, 5.0); //Electro->Culture
    g.add_edge(2, 6, 28.0); //Electro->Ship
    g.add_edge(2, 7, 18.0); //Electro->Comm
    g.add_edge(3, 4, 3.0); //Center->Avia
    g.add_edge(3, 5, 4.0); //Center->Culture
    g.add_edge(3, 6, 26.0); //Center->Ship
    g.add_edge(3, 7, 19.0); //Center->Comm
    g.add_edge(4, 5, 3.0); //Avia->Culture
    g.add_edge(4, 6, 11.0); //Avia->Ship
    g.add_edge(4, 7, 14.0); //Avia->Comm
    g.add_edge(5, 6, 15.0); //Culture->Ship
    g.add_edge(5, 7, 14.0); //Culture->Comm
    g.add_edge(6, 7, 30.0); //Ship->Comm

    std::unordered_map<Graph::Node, Graph::Weight> dist;
    std::unordered_map<Graph::Node, Graph::Node> prev;
    bool res = g.bellman_ford(1, dist, prev);

    if(res){
        std::cout << "It works!\n";
    }
    else{
        std::cout << "Unexpected exception...\n";
    }

    if (res) {
        std::cout << "Paths from 1:" << std::endl;
        for (auto node : g.nodes()) {
            std::cout << " to " << node << ": ";
            if (dist.at(node) < ULONG_MAX){
                std::cout << dist.at(node) << std::endl;
            }
            else{
                std::cout << "No way to " << node << std::endl;
            }
        }
        std::cout << std::endl;
    }

    /*std::cout << "Test №9 - testing Bellman-Ford (with negative cycles)\n";
    g.add_edge(3, 1, -100.0);
    bool res2 = g.bellman_ford(1, dist, prev);
    if(!res2){
        std::cout << "It didn't work, as expected\n";
    }
    else{
        std::cout << "Somehow, it works...\n";
    }*/
}

