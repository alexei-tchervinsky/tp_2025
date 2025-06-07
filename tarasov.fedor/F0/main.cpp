#include "graph_TP.hpp"
#include <iostream>

void runKruskalTest1_Empty() {
    std::cout << "  --- Тест Крускала 1: Пустой граф ---" << std::endl;
    Graph g;
    std::cout << "  Исходный граф:" << std::endl;
    g.printGraph();
    Graph mst = algorithmKruscala(g);
    std::cout << "  MST (пустой граф):" << std::endl;
    mst.printGraph();
    std::cout << "  Ожидаемый результат: MST пуст." << std::endl << std::endl;
}

void runKruskalTest2_SingleNode() {
    std::cout << "  --- Тест Крускала 2: Граф из одной вершины (без рёбер) ---" << std::endl;
    Graph g;
    g.addNode(1);
    std::cout << "  Исходный граф:" << std::endl;
    g.printGraph();
    Graph mst = algorithmKruscala(g);
    std::cout << "  MST (одна вершина):" << std::endl;
    mst.printGraph();
    std::cout << "  Ожидаемый результат: MST содержит узел 1, рёбер нет." << std::endl << std::endl;
}

void runKruskalTest3_SimpleConnected() {
    std::cout << "  --- Тест Крускала 3: Простой связный граф (3 вершины) ---" << std::endl;
    Graph g;
    g.addNode(0); g.addNode(1); g.addNode(2);
    g.addEdge(0, 1, 1); g.addEdge(1, 2, 2); g.addEdge(0, 2, 3);
    std::cout << "  Исходный граф:" << std::endl;
    g.printGraph();
    Graph mst = algorithmKruscala(g);
    std::cout << "  MST (простой связный граф):" << std::endl;
    mst.printGraph();
    std::cout << "  Ожидаемый результат: MST содержит рёбра (0,1,1) и (1,2,2)." << std::endl << std::endl;
}

void runKruskalTest4_Disconnected() {
    std::cout << "  --- Тест Крускала 4: Несвязный граф (2 компоненты) ---" << std::endl;
    Graph g;
    g.addNode(0); g.addNode(1); g.addNode(2); g.addNode(3);
    g.addEdge(0, 1, 1); g.addEdge(2, 3, 2);
    std::cout << "  Исходный граф:" << std::endl;
    g.printGraph();
    Graph mst = algorithmKruscala(g);
    std::cout << "  MST (несвязный граф, лес):" << std::endl;
    mst.printGraph();
    std::cout << "  Ожидаемый результат: MST (лес) содержит рёбра (0,1,1) и (2,3,2)." << std::endl << std::endl;
}

void runKruskalTest5_MultiplePaths() {
    std::cout << "  --- Тест Крускала 5: Граф с несколькими путями ---" << std::endl;
    Graph g;
    g.addNode(0); g.addNode(1); g.addNode(2); g.addNode(3);
    g.addEdge(0, 1, 1); g.addEdge(0, 2, 2);
    g.addEdge(1, 3, 3); g.addEdge(2, 3, 1);
    std::cout << "  Исходный граф:" << std::endl;
    g.printGraph();
    Graph mst = algorithmKruscala(g);
    std::cout << "  MST (граф с несколькими путями):" << std::endl;
    mst.printGraph();
    std::cout << "  Ожидаемый результат: MST содержит рёбра (0,1,1), (2,3,1), (0,2,2). Общий вес = 4." << std::endl << std::endl;
}

void runPrimTest1_Empty() {
    std::cout << "  --- Тест Прима 1: Пустой граф ---" << std::endl;
    Graph g;
    std::cout << "  Исходный граф:" << std::endl;
    g.printGraph();
    Graph mst = algorithmPrima(g);
    std::cout << "  MST (пустой граф):" << std::endl;
    mst.printGraph();
    std::cout << "  Ожидаемый результат: MST пуст." << std::endl << std::endl;
}

void runPrimTest2_SingleNode() {
    std::cout << "  --- Тест Прима 2: Граф из одной вершины (без рёбер) ---" << std::endl;
    Graph g;
    g.addNode(1);
    std::cout << "  Исходный граф:" << std::endl;
    g.printGraph();
    Graph mst = algorithmPrima(g);
    std::cout << "  MST (одна вершина):" << std::endl;
    mst.printGraph();
    std::cout << "  Ожидаемый результат: MST содержит узел 1, рёбер нет." << std::endl << std::endl;
}

void runPrimTest3_SimpleConnected() {
    std::cout << "  --- Тест Прима 3: Простой связный граф (3 вершины) ---" << std::endl;
    Graph g;
    g.addNode(0); g.addNode(1); g.addNode(2);
    g.addEdge(0, 1, 1); g.addEdge(1, 2, 2); g.addEdge(0, 2, 3);
    std::cout << "  Исходный граф:" << std::endl;
    g.printGraph();
    Graph mst = algorithmPrima(g);
    std::cout << "  MST (простой связный граф):" << std::endl;
    mst.printGraph();
    std::cout << "  Ожидаемый результат: MST содержит рёбра (0,1,1) и (1,2,2). Общий вес = 3." << std::endl << std::endl;
}

void runPrimTest4_Disconnected() {
    std::cout << "  --- Тест Прима 4: Несвязный граф (2 компоненты) ---" << std::endl;
    Graph g;
    g.addNode(0); g.addNode(1); g.addNode(2); g.addNode(3);
    g.addEdge(0, 1, 1);
    g.addEdge(2, 3, 2);
    std::cout << "  Исходный граф:" << std::endl;
    g.printGraph();
    Graph mst = algorithmPrima(g);
    std::cout << "  MST ( несвязный граф, Прим):" << std::endl;
    mst.printGraph();
    std::cout << "  Ожидаемый результат: MST содержит ребро (0,1,1). Узлы 2,3 будут в MST, но без ребер к ним." << std::endl << std::endl;
}

void runPrimTest5_MultiplePaths() {
    std::cout << "  --- Тест Прима 5: Граф с несколькими путями ---" << std::endl;
    Graph g;
    g.addNode(0); g.addNode(1); g.addNode(2); g.addNode(3);
    g.addEdge(0, 1, 1); g.addEdge(0, 2, 2);
    g.addEdge(1, 3, 3); g.addEdge(2, 3, 1);
    std::cout << "  Исходный граф:" << std::endl;
    g.printGraph();
    Graph mst = algorithmPrima(g);
    std::cout << "  MST (граф с несколькими путями, Прим):" << std::endl;
    mst.printGraph();
    std::cout << "  Ожидаемый результат: MST содержит рёбра (0,1,1), (2,3,1), (0,2,2). Общий вес = 4." << std::endl << std::endl;
}

void runGraphMethodsTests() {
    std::cout << "  --- Тесты методов класса Graph ---" << std::endl;
    Graph myGraph;

    std::cout << "\n  1. Исходное состояние (пустой граф):" << std::endl;
    myGraph.printGraph();
    std::cout << "  Граф пуст? " << (myGraph.isEmpty() ? "Да" : "Нет") << std::endl;

    std::cout << "\n  2. Добавление узлов:" << std::endl;
    myGraph.addNode(10); myGraph.addNode(20); myGraph.addNode(5);
    myGraph.addNode(20);
    myGraph.printGraph();
    std::cout << "  Граф пуст? " << (myGraph.isEmpty() ? "Да" : "Нет") << std::endl;
    std::cout << "  Узел 10 существует? " << (myGraph.hasNode(10) ? "Да" : "Нет") << std::endl;
    std::cout << "  Узел 15 существует? " << (myGraph.hasNode(15) ? "Да" : "Нет") << std::endl;

    std::cout << "\n  3. Добавление рёбер:" << std::endl;
    myGraph.addEdge(10, 20, 15);
    myGraph.addEdge(5, 10, 7);
    myGraph.addEdge(5, 20, 10);
    myGraph.addEdge(1, 2, 5);
    myGraph.addEdge(10, 20, 15);
    myGraph.printGraph();
    std::cout << "  Ребро (10, 20) существует? " << (myGraph.hasEdge(10, 20) ? "Да" : "Нет") << std::endl;
    std::cout << "  Ребро (20, 10) существует? " << (myGraph.hasEdge(20, 10) ? "Да" : "Нет") << " (проверка неориентированности)"<< std::endl;
    std::cout << "  Ребро (10, 50) существует? " << (myGraph.hasEdge(10, 50) ? "Да" : "Нет") << std::endl;

    std::cout << "\n  4. Удаление узла:" << std::endl;
    std::cout << "  Удаление узла 10:" << std::endl;
    myGraph.removeNode(10);
    myGraph.printGraph();
    std::cout << "  Узел 10 существует? " << (myGraph.hasNode(10) ? "Да" : "Нет") << std::endl;
    std::cout << "  Ребро (5, 10) существует? " << (myGraph.hasEdge(5, 10) ? "Да" : "Нет") << std::endl;
    std::cout << "  Ребро (5, 20) существует? " << (myGraph.hasEdge(5, 20) ? "Да" : "Нет") << " (это ребро должно было остаться)"<< std::endl;

    std::cout << "  Попытка удалить несуществующий узел 100:" << std::endl;
    myGraph.removeNode(100);
    myGraph.printGraph();
    std::cout << std::endl;
}

void runTests(const std::string& testType) {
    std::cout << "==============================================" << std::endl;
    std::cout << "ЗАПУСК ТЕСТОВ ДЛЯ: \"" << testType << "\"" << std::endl;
    std::cout << "==============================================" << std::endl;

    if (testType == "Граф") {
        runGraphMethodsTests();
    } else if (testType == "Крускала") {
        runKruskalTest1_Empty();
        runKruskalTest2_SingleNode();
        runKruskalTest3_SimpleConnected();
        runKruskalTest4_Disconnected();
        runKruskalTest5_MultiplePaths();
    } else if (testType == "Прима") {
        runPrimTest1_Empty();
        runPrimTest2_SingleNode();
        runPrimTest3_SimpleConnected();
        runPrimTest4_Disconnected();
        runPrimTest5_MultiplePaths();
    } else {
        std::cout << "Неизвестный тип теста: \"" << testType << "\"" << std::endl;
        std::cout << "Допустимые значения: \"Граф\", \"Крускала\", \"Прима\"" << std::endl;
    }
    std::cout << "--- Тестирование для \"" << testType << "\" завершено ---" << std::endl << std::endl;
}
int main() {
    std::string c;

    std::cout << "Введите команду ('Граф', 'Прима', 'Курскала')." << std::endl;

    while (std::cin >> c) {
        if (c != "Граф" && c != "Прима" && c != "Крускала") {
            std::cout << "Неверная команда: " << c << ". Пожалуйста, введите 'Граф', 'Прима' или 'Курскала'." << std::endl;
        } else {
            runTests(c);
        }
        std::cout << "Введите следующую команду:" << std::endl;
    }

    if (std::cin.eof()) {
        std::cout << "Ввод завершен (достигнут конец файла)." << std::endl;
    } else if (std::cin.fail()) {
        std::cerr << "Ошибка ввода. Возможно, был введен некорректный тип данных." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}
